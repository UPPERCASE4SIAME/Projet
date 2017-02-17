#include "mainwindow.h"
#include "ui_mainwindow.h"

#define EXEC_MODE_INDEX 0
#define TRACE_MODE_INDEX 1
#define WCET_MODE_INDEX 2

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    runTimer = new QTimer(this);

    stepDelay = 0.5;
    execution_counter = 0;

    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        ignitionData[i] = new QLineSeries();
    }

    ui->setupUi(this);

	int curr_index = ui->tabWidget->currentIndex();


    initDisplays(curr_index);
    changeTimerCalls(curr_index);

    setupEngineCycleDisplay();

    setupIgnitionChart(ignitionChart_exec);
}

MainWindow::~MainWindow()
{
    delete traceFile;
    delete traceFileIn;
    delete device;

    delete runTimer;

    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        delete ignitionData[i];
    }


    delete browseEdit;
    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        delete ignitionLabels[i];
    }

    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        for(int j = 0; j < NUM_ENGINE_ANIMATION_IMAGES; j++)
        {
            delete cycle[i][j];
        }
    }

    delete ignitionChart_exec;
    delete ignitionChart_trace;
    delete engineCycleScene;

    delete ui;
}

void MainWindow::initDisplays(int index)
{
    /* depending on which tab we are on, our line reading function is going to write to different labels
       our file will also be different those names can be changed in the form editor */
    if(index == EXEC_MODE_INDEX)
    {
        browseEdit = (QLineEdit*)ui->browseEdit_exec;

        ignitionLabels[0] = (QLabel*)ui->ignition1_value_label_exec;
        ignitionLabels[1] = (QLabel*)ui->ignition2_value_label_exec;
        ignitionLabels[2] = (QLabel*)ui->ignition3_value_label_exec;
        ignitionLabels[3] = (QLabel*)ui->ignition4_value_label_exec;
        ignitionLabels[4] = (QLabel*)ui->ignition5_value_label_exec;
        ignitionLabels[5] = (QLabel*)ui->ignition6_value_label_exec;

        ignitionChartView   = (QChartView*)ui->ignition_chart_exec;
        engineChartView     = (QChartView*)ui->engine_chart_exec;

        setupIgnitionChart(ignitionChart_exec);
    }
    else if (index == TRACE_MODE_INDEX)
    {
        browseEdit = (QLineEdit*)ui->browseEdit;

        ignitionLabels[0] = (QLabel*)ui->ignition1_value_label;
        ignitionLabels[1] = (QLabel*)ui->ignition2_value_label;
        ignitionLabels[2] = (QLabel*)ui->ignition3_value_label;
        ignitionLabels[3] = (QLabel*)ui->ignition4_value_label;
        ignitionLabels[4] = (QLabel*)ui->ignition5_value_label;
        ignitionLabels[5] = (QLabel*)ui->ignition6_value_label;

        ignitionChartView   = (QChartView*)ui->ignition_chart_trace;
        engineChartView     = (QChartView*)ui->engine_chart_trace;

        setupIgnitionChart(ignitionChart_trace);
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

    startRunning(1000/stepDelay);
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
        startRunning(1000/stepDelay);
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
        startRunning(1000/stepDelay);
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

        qDebug() << "reading line";

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

        ui->engine_rpm_trace->setText(QString::number((int)(60/(currentRotationDuration/2000000))));

        for(int i = 0; i < NUM_CYLINDERS; i++)
        {
            ignitionLabels[i]->setText(values[i+1]);

            //this calls the function that starts the animation for this ignition
            //after a time proportional to when the ignition happened during the engine cycle
            QTimer::singleShot(1000.0 / stepDelay * (values[i+1].toFloat() / currentRotationDuration) , Qt::TimerType::PreciseTimer, this, SLOT(drawCycle()));

            qDebug() << (values[i+1].toFloat() / currentRotationDuration);
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

    ui->engine_rpm_exec->setText(QString::number((int)(60/(currentRotationDuration/2000000))));

    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        ignitionLabels[i]->setText(values[i+1]);
    }

    changeIgnition(values);
}

void MainWindow::stopRunning()
{
    runTimer->stop();

    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        engineDisplayTimers[i]->stop();
    }

    QThread::sleep(0.1);

    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        engineDisplayTimers[i]->stop();
    }
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
    axisY->append("Ignition 2", 2);
    axisY->append("Ignition 3", 3);
    axisY->append("Ignition 4", 4);
    axisY->append("Ignition 5", 5);
    axisY->append("Ignition 6", 6);

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
    static QString imageNames[NUM_ENGINE_ANIMATION_IMAGES] = {"haut_det.jpg","milieu_det.jpg","bas_det.jpg",
                                     "bas_ech.jpg","milieu_ech.jpg","haut_ech.jpg",
                                     "haut_adm.jpg","milieu_adm.jpg","bas_adm.jpg",
                                     "bas_comp.jpg","milieu_comp.jpg","haut_comp.jpg"};

    //setting up the gui
    QSize sceneSize = ui->engineCycle_display->size();

    //ugly fix to remove the scrollbars qt puts in if you give the exact width and height
    int sceneWidth = sceneSize.width() * 0.9;
    int sceneHeight = sceneSize.height() * 0.9;

    engineCycleScene = new QGraphicsScene(0, 0, sceneWidth, sceneHeight);
    ui->engineCycle_display->setScene(engineCycleScene);
    ui->engineCycle_display->show();

    //each cylinder has a 12 frames animation
    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        for(int j = 0; j < NUM_ENGINE_ANIMATION_IMAGES; j++)
        {
            //we load the image, rescale it and it to the graphics scene at the position where it's going to be displayed
            QImage image(IMAGE_DIRECTORY + imageNames[j]);

            QImage scaledImage = image.scaled(sceneWidth/NUM_CYLINDERS, sceneHeight);

            cycle[i][j] = new QGraphicsPixmapItem(QPixmap::fromImage(scaledImage));
            engineCycleScene->addItem(cycle[i][j]);

            cycle[i][j]->setPos(i * sceneWidth / NUM_CYLINDERS, 0);
        }
    }

    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        engineDisplayTimers[i] = new QBasicTimer();
    }
}


/* When called, initiates the animation for the cylinder ignitionNum
 * If a timer is already running, we'll wait for the end of the animation
 */
void MainWindow::drawCycle()
{
    //1 5 3 6 2 4
    static int firingOrder[NUM_CYLINDERS] = {0,4,2,5,1,3};
    static int currentCylinderNum = 0;

    int activeCylinder = firingOrder[currentCylinderNum];

//    float rotationDurationMs = currentRotationDuration / 1000;

//    engineDisplayAvailableToDraw[activeCylinder] = 0;

    engineDisplayTimers[activeCylinder]->start((1000.0/stepDelay/6), Qt::TimerType::PreciseTimer, this);
    nextState(activeCylinder);

    currentCylinderNum = (currentCylinderNum + 1) % NUM_CYLINDERS;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == runTimer->timerId())
    {
        readLineFromTrace();
    }

    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        if(event->timerId() == engineDisplayTimers[i]->timerId())
        {
            nextState(i);
            return;
        }
    }
}

/* This function is called regularly to update the state of each cylinder
 * it sets the image corresponding to the state the cylinder given as an argument
 * as visible and puts that image where the cylinder is in the graphical scene
 */
void MainWindow::nextState(int ignition)
{
    static int cycle_number[NUM_CYLINDERS] = {0, 0, 0, 0, 0, 0};

    //qDebug() << ignition << cycle_number[ignition];

    cycle[ignition][cycle_number[ignition]]->setZValue(0);

    cycle_number[ignition] = (cycle_number[ignition] + 1) % NUM_ENGINE_ANIMATION_IMAGES;

    cycle[ignition][cycle_number[ignition]]->setZValue(1);

//    //if we've done a full cycle we stop
//    if(cycle_number[ignition] == 0)
//    {
//        //engineDisplayTimers[ignition]->stop();
//        engineDisplayAvailableToDraw[ignition] = 1;
//    }
}

