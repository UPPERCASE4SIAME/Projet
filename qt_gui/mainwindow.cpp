#include "mainwindow.h"
#include "ui_mainwindow.h"

#define EXEC_MODE_INDEX 0
#define TRACE_MODE_INDEX 1
#define WCET_MODE_INDEX 2

#define STEP_DELAY_SECONDS 1000.0 / stepDelay

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    runTimer = new QTimer(this);

    rpmTimer = new QTimer(this);

    connect(runTimer, SIGNAL(timeout()), this, SLOT(updateRPMChart()));

    rpmTimer->start(1000);

    stepDelay = 0.5;
    execution_counter = 0;

    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        ignitionData[i] = new QLineSeries();
    }

    rpmData = new QLineSeries();

    ui->setupUi(this);

	int curr_index = ui->tabWidget->currentIndex();

    engineDisplayTimer = new QTimer();
    engineDisplayTimer->setTimerType(Qt::TimerType::PreciseTimer);

    connect(engineDisplayTimer, SIGNAL(timeout()), this, SLOT(nextState()));

    initDisplays(curr_index);
    changeTimerCalls(curr_index);
    setupEngineCycleDisplay();

    //setupIgnitionChart(ignitionChart_exec);
    //setupRPMChart(rpm);
}

MainWindow::~MainWindow()
{
    delete traceFile;
    delete traceFileIn;
    delete device;

    delete runTimer;
    delete rpmTimer;
    delete engineDisplayTimer;

    delete rpmData;

    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        delete ignitionData[i];
    }

    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        delete ignitionLabels[i];
    }

    for(int i = 0; i < NUM_ENGINE_ANIMATION_IMAGES; i++)
    {
        delete cycle[i];
    }

    delete ui;

    delete ignitionChart_exec;
    delete ignitionChart_trace;

    delete rpmChart_exec;
    delete rpmChart_trace;

    delete engineCycleScene;
}

void MainWindow::initDisplays(int index)
{
    /* depending on which tab we are on, our line reading function is going to write to different labels
       our file will also be different those names can be changed in the form editor */
    if(index == EXEC_MODE_INDEX)
    {
        browseEdit = (QLineEdit*)ui->browseEdit_exec;

        //display the values in 1,5,3,6,2,4 order
        ignitionLabels[0] = (QLabel*)ui->ignition1_value_label_exec;
        ignitionLabels[4] = (QLabel*)ui->ignition2_value_label_exec;
        ignitionLabels[2] = (QLabel*)ui->ignition3_value_label_exec;
        ignitionLabels[5] = (QLabel*)ui->ignition4_value_label_exec;
        ignitionLabels[1] = (QLabel*)ui->ignition5_value_label_exec;
        ignitionLabels[3] = (QLabel*)ui->ignition6_value_label_exec;

        ignitionChartView   = (QChartView*)ui->ignition_chart_exec;
        engineChartView     = (QChartView*)ui->engine_chart_exec;

        setupIgnitionChart(ignitionChart_exec);
        setupRPMChart(rpmChart_exec);
    }
    else if (index == TRACE_MODE_INDEX)
    {
        browseEdit = (QLineEdit*)ui->browseEdit;

        //display the values in 1,5,3,6,2,4 order
        ignitionLabels[0] = (QLabel*)ui->ignition1_value_label;
        ignitionLabels[4] = (QLabel*)ui->ignition2_value_label;
        ignitionLabels[2] = (QLabel*)ui->ignition3_value_label;
        ignitionLabels[5] = (QLabel*)ui->ignition4_value_label;
        ignitionLabels[1] = (QLabel*)ui->ignition5_value_label;
        ignitionLabels[3] = (QLabel*)ui->ignition6_value_label;

        ignitionChartView   = (QChartView*)ui->ignition_chart_trace;
        engineChartView     = (QChartView*)ui->engine_chart_trace;

        setupIgnitionChart(ignitionChart_trace);
        setupRPMChart(rpmChart_trace);
    }
}

void MainWindow::changeTimerCalls(int index)
{
	runTimer->stop();
	if(index == EXEC_MODE_INDEX)
	{
		connect(runTimer, SIGNAL(timeout()), this, SLOT(readLineFromDevice()));
		disconnect(runTimer, SIGNAL(timeout()), this, SLOT(readLineFromTrace()));
	}
	if(index == TRACE_MODE_INDEX)
	{
		connect(runTimer, SIGNAL(timeout()), this, SLOT(readLineFromTrace()));
		disconnect(runTimer, SIGNAL(timeout()), this, SLOT(readLineFromDevice()));
	}
}

void MainWindow::on_browse_button_clicked()
{
    QString fileName = QFileDialog::getOpenFileName();

    browseEdit->setText(fileName);

    openTrace();
}

void MainWindow::on_browse_button_exec_clicked()
{
    QString fileName = QFileDialog::getOpenFileName();

    browseEdit->setText(fileName);

    openDevice();
}

void MainWindow::startRunning(float delay)
{
    runTimer->start(delay);
}

void MainWindow::on_rotation_freq_counter_valueChanged(double newValue)
{
    //step delay is in engine cycles and not in rps
    stepDelay = newValue/2;

    startRunning(STEP_DELAY_SECONDS);
}

void MainWindow::on_execution_button_clicked()
{
    if(!readyToRead)
    {
        openTrace();
    }

    if(readyToRead)
    {
        ((QPushButton*)ui->pause_button)->setText("Pause");
        startRunning(STEP_DELAY_SECONDS);
    }
}

void MainWindow::on_readDevice_button_clicked()
{
    openDevice();
}

void MainWindow::on_pause_button_clicked()
{
    static bool paused = false;

    if(paused)
    {
        startRunning(STEP_DELAY_SECONDS);
        ((QPushButton*)ui->pause_button)->setText("Pause");

        paused = false;
    }
    else
    {
        stopRunning();
        ((QPushButton*)ui->pause_button)->setText("Resume");

        paused = true;
    }
}

void MainWindow::on_browseEdit_editingFinished()
{
    openTrace();
}

void MainWindow::on_browseEdit_exec_editingFinished()
{
    openDevice();
}

void MainWindow::openTrace()
{
    QString fileName = browseEdit->text();

    QFileInfo check_traceFile(fileName);

    //we've opened a new trace, so we're on play mode now
    ((QPushButton*)ui->pause_button)->setText("Pause");

    //if our trace file doesn't exist or it's not a valid file then we'll just wait for the user to give us another file
    if(!check_traceFile.exists() || !check_traceFile.isReadable())
    {
        readyToRead = false;

        qDebug() << "file doesn't exist or is unreadable";
        return;
    }

    traceFile = new QFile(fileName);

    if (!traceFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {

        qDebug() << "couldn't open file";
        readyToRead = false;
        return;
    }

    readyToRead = true;

    stopRunning();

    traceFileIn = new QTextStream(traceFile);
}

void MainWindow::openDevice()
{
    QString fileName = browseEdit->text();

    device = new QSerialPort(this);
        
    device->setPortName(fileName);    

    if (!device->open(QIODevice::ReadWrite))
    {

        qDebug() << "couldn't open device";
        readyToRead = false;
        return;
    }

    readyToRead = true;
        
    connect(device, &QSerialPort::readyRead, this, &MainWindow::readLineFromDevice);
}

void MainWindow::readLineFromTrace()
{
    static QString line;
    static QStringList values;

    static QRegExp lineFormatExp("\\d+;\\d+;\\d+;\\d+;\\d+;\\d+;\\d+");

    if(!traceFileIn->atEnd())
    {
        line = traceFileIn->readLine();

        if(line.isEmpty())
        {
            return;
        }

        if(!line.contains(lineFormatExp))
        {
            qDebug() << "Line format is wrong";

            return;
        }

        values = line.split(";");

        currentRotationDuration = values[0].toFloat();

        ui->engine_rpm_value_trace->setText(QString::number((int)(60/(currentRotationDuration/2000000))));

        for(int i = 0; i < NUM_CYLINDERS; i++)
        {
            ignitionLabels[i]->setText(values[i+1]);

            drawCycle(values);
        }

        changeIgnition(values);
    }
    else
    {
        stopRunning();

        readyToRead = false;
    }

}

void MainWindow::readLineFromDevice()
{
    static QByteArray data;
    static QStringList values;

    static QRegExp lineFormatExp("\\d+;\\d+;\\d+;\\d+;\\d+;\\d+;\\d+");


    data = device->readLine();
    device->readAll();

    //transforms the byte array into a string
    QString line(data);
        
    if(line.isEmpty())
    {
        return;
    }

    if(!line.contains(lineFormatExp))
    {
        qDebug() << "Line format is wrong";

        return;
    }

    values = line.split(";");

    currentRotationDuration = values[0].toFloat();

    ui->engine_rpm_value_exec->setText(QString::number((int)(60/(currentRotationDuration/2000000))));

    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        ignitionLabels[i]->setText(values[i+1]);
    }

    changeIgnition(values);
}

void MainWindow::stopRunning()
{
    runTimer->stop();
}

void MainWindow::on_browseEdit_save_exec_editingFinished()
{

}

void MainWindow::on_browse_button_save_exec_clicked()
{

}

void MainWindow::on_save_button_exec_clicked()
{

}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    stopRunning();

    initDisplays(index);
    changeTimerCalls(index);

}

void MainWindow::setupIgnitionChart(QChart* chart)
{
    //make a new chart that we're going to add to the view
    chart = new QChart();

    //we feed initial data to each series, we have those 4 dummy points in the middle
    //because we replace them later with updated values and that calls for a repaint
    //it's easier than inserting them on the spot and faster
    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        ignitionData[i]->clear();

        ignitionData[i]->append(0, i + 1);
        ignitionData[i]->append(1, i + 1);
        ignitionData[i]->append(2, i + 1);
        ignitionData[i]->append(3, i + 1);
        ignitionData[i]->append(4, i + 1);
        ignitionData[i]->append(25, i + 1);

        chart->addSeries(ignitionData[i]);
    }

    QCategoryAxis *axisX = new QCategoryAxis();
    QCategoryAxis *axisY = new QCategoryAxis();

    //we don't care about the legend because it's next to the axes anyway
    chart->legend()->hide();

    //we want to make it so even if the ignition got off at the last moment we can still see the peak
    axisX->setRange(0, 25);
    axisY->setRange(0, 7);

    //put labels on the axes
    axisY->append("Ignition 1", 1);
    axisY->append("Ignition 5", 2);
    axisY->append("Ignition 3", 3);
    axisY->append("Ignition 6", 4);
    axisY->append("Ignition 2", 5);
    axisY->append("Ignition 4", 6);

    axisY->setLabelsPosition(QCategoryAxis::AxisLabelsPosition::AxisLabelsPositionOnValue);

    chart->setAxisX(axisX);
    chart->setAxisY(axisY);

    //we need to attach the data series to the axes so it scales correctly
    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        ignitionData[i]->attachAxis(chart->axisY());
    }

    //and display it in our view
    ignitionChartView->setChart(chart);
}

void MainWindow::setupRPMChart(QChart *chart)
{
    //make a new chart that we're going to add to the view
    chart = new QChart();

    rpmData->clear();
    rpmData->append(0, 0);

    QValueAxis* axisX = new QValueAxis();
    QValueAxis* axisY = new QValueAxis();

    chart->addSeries(rpmData);

    chart->createDefaultAxes();

    axisX->setRange(0, 200);
    axisY->setRange(0, 10000);


    chart->setAxisX(axisX);
    chart->setAxisY(axisY);

    rpmData->attachAxis(axisX);
    rpmData->attachAxis(axisY);

    chart->legend()->hide();

    engineChartView->setChart(chart);
}

void MainWindow::changeIgnition(QStringList values)
{
    float ignitionValues[NUM_CYLINDERS];

    //we need this to position the ignition correctly
    float interval = ((QString)values[0]).toFloat();

    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        ignitionValues[i] = ((QString)values[i + 1]).toFloat() / interval * 24;

        ignitionData[i]->replace(1, ignitionValues[i], i + 1);
        ignitionData[i]->replace(2, ignitionValues[i], i + 1.3);
        ignitionData[i]->replace(3, ignitionValues[i] + 1, i + 1.3);
        ignitionData[i]->replace(4, ignitionValues[i] + 1, i + 1);
    }
}

void MainWindow::setupEngineCycleDisplay()
{
    //setting up the gui
    QSize sceneSize = ui->engineCycle_display->size();

    //ugly fix to remove the scrollbars qt puts in if you give the exact width and height
    int sceneWidth = sceneSize.width() * 0.9;
    int sceneHeight = sceneSize.height() * 0.9;

    engineCycleScene = new QGraphicsScene(0, 0, sceneWidth, sceneHeight);
    ui->engineCycle_display->setScene(engineCycleScene);
    ui->engineCycle_display->show();

    //each cylinder has a 12 frames animation
    for(int i = 0; i < NUM_ENGINE_ANIMATION_IMAGES; i++)
    {
        //we load the image, rescale it and add it to the graphics scene at the position where it's going to be displayed
        QString imagePath = QString(IMAGE_DIRECTORY) + QString("ignition_") + imageNames[i] + QString(".png");

        QImage image(imagePath);

        QImage scaledImage = image.scaled(sceneWidth, sceneHeight);

        cycle[i] = new QGraphicsPixmapItem(QPixmap::fromImage(scaledImage));
        engineCycleScene->addItem(cycle[i]);
        cycle[i]->setPos(0,0);
    }
}


/* When called, initiates the animation for the cylinder ignitionNum
 * If a timer is already running, we'll wait for the end of the animation
 */
void MainWindow::drawCycle(QStringList values)
{
    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        ignitionDelays[i] = values[i + 1].toInt();
    }

    engineDisplay_ignitionIndex = 0;
    engineDisplay_animationIndex = 0;

    engineDisplayTimer->start(0);
}

/* This function is called regularly to update the state of each cylinder
 * it sets the image corresponding to the state the cylinder given as an argument
 * as visible and puts that image where the cylinder is in the graphical scene
 */
void MainWindow::nextState()
{
    //hide the frame we were just displaying
    cycle[engineDisplay_animationIndex]->setZValue(0);

    //get to the next step of the animation
    engineDisplay_animationIndex = (engineDisplay_animationIndex + 1) % NUM_ENGINE_ANIMATION_IMAGES;
    engineDisplay_ignitionIndex = (int)(engineDisplay_animationIndex / NUM_FRAMES_PER_IGNITION);

    //display the next frame
    cycle[engineDisplay_animationIndex]->setZValue(1);

    //if we're back to the beginning of the animation we can stop the animation
    if(engineDisplay_animationIndex == 0)
    {
        engineDisplayTimer->stop();
    }

    //this is the time between this ignition and the next one
    int delta = 0;
    float timerDelay = 0;

    //animation for edge cases is done as if the engine cycles were coherent from one cycle to the other
    if(engineDisplay_ignitionIndex == NUM_CYLINDERS - 1 || engineDisplay_animationIndex <= 1)
    {
        delta = currentRotationDuration - ignitionDelays[NUM_CYLINDERS - 1] + ignitionDelays[0];
        timerDelay = (STEP_DELAY_SECONDS * (delta / currentRotationDuration));
    }
    //otherwise delta is the time between this ignition and the next one
    else
    {
        delta = ignitionDelays[engineDisplay_ignitionIndex + 1] - ignitionDelays[engineDisplay_ignitionIndex];
        timerDelay = (STEP_DELAY_SECONDS * (delta / currentRotationDuration));
    }


//    qDebug() << STEP_DELAY_SECONDS << delta << ignitionDelays[engineDisplay_ignitionIndex] << currentRotationDuration << timerDelay << engineDisplay_ignitionIndex << engineDisplay_animationIndex;

    engineDisplayTimer->setInterval(timerDelay);

}

void MainWindow::updateRPMChart()
{
    static int index = 0;
    if(runTimer->isActive())
    {
        rpmData->append(index++, ((int)(60/(currentRotationDuration/2000000))));

        if(((QValueAxis*)engineChartView->chart()->axisX())->max() < index + 100)
        {
            ((QValueAxis*)engineChartView->chart()->axisX())->setMax(index + 200);
        }

        if(((QValueAxis*)engineChartView->chart()->axisY())->max() < ((int)(60/(currentRotationDuration/2000000))))
        {
            ((QValueAxis*)engineChartView->chart()->axisY())->setMax(((int)(60/(currentRotationDuration/2000000))) + 1000);
        }
    }
}

