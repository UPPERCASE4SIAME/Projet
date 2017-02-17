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

    stepDelay = 1;
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

    delete ui;

    delete ignitionChart_exec;
    delete ignitionChart_trace;
    delete engineCycleScene;
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
    stepDelay = newValue;
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

        currentRotationDuration = values[0].toInt();

        for(int i = 0; i < NUM_CYLINDERS; i++)
        {
            ignitionLabels[i]->setText(values[i+1]);

            //???
            QTimer::singleShot(1000.0 / stepDelay * (values[i+1].toFloat() / values[0].toFloat()) , this, SLOT(drawCycle()));
        }


        changeIgnition(values);
    }
    else
    {
        runTimer->stop();
        readyToRead = false;
    }

}

void MainWindow::readLineFromDevice()
{
    static QByteArray data;
    static QStringList values;

    static QRegExp lineFormatExp("\\d+;\\d+;\\d+;\\d+;\\d+;\\d+;\\d+");


    data = device->readLine();

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
        ignitionData[i]->append(0, i + 1);
        ignitionData[i]->append(i * 2 + 1, i + 1);
        ignitionData[i]->append(i * 2 + 1, i + 1.3);
        ignitionData[i]->append(i * 2 + 2, i + 1.3);
        ignitionData[i]->append(i * 2 + 2, i + 1);
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

    QSize sceneSize = ui->engineCycle_display->size();

    sceneWidth = sceneSize.width() * 0.9;
    int sceneHeight = sceneSize.height() * 0.9;

    engineCycleScene = new QGraphicsScene(0, 0, sceneWidth, sceneHeight);
    ui->engineCycle_display->setScene(engineCycleScene);
    ui->engineCycle_display->show();

    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        for(int j = 0; j < NUM_ENGINE_ANIMATION_IMAGES; j++)
        {
            QImage image(IMAGE_DIRECTORY + imageNames[j]);

            QImage scaledImage = image.scaled(sceneWidth/NUM_CYLINDERS, sceneHeight);

            cycle[i][j] = new QGraphicsPixmapItem(QPixmap::fromImage(scaledImage));
            engineCycleScene->addItem(cycle[i][j]);

            cycle[i][j]->setPos(i * sceneWidth / NUM_CYLINDERS, 0);

           // cycle[i][j]->hide();
        }
    }

    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        engineDisplayTimers[i] = new QBasicTimer();
//        engineDisplayTimers[i]->connect(engineDisplayTimers[i], SIGNAL(&MainWindow::engineDisplayNextStateSignal(i)), this, SLOT(MainWindow::nextState(i)));
    }
}


/* When called, initiates the animation for the cylinder ignitionNum
 * If a timer is already running, we'll wait for the end of the animation
 */
void MainWindow::drawCycle()
{
    //1 5 3 6 2 4
    static int currentCylinder[6] = {0,4,2,5,1,3};
    static int currentCylinderNum = 0;

    float rotationDurationMs = currentRotationDuration / 1000;

//    while(engineDisplayAvailableToDraw[currentCylinder] == 0)
//    {
//        //that's super dirty but I don't really know what to do there because of timer limitations
//        QThread::sleep(1/10000000);
//    }

    engineDisplayAvailableToDraw[currentCylinder[currentCylinderNum]] = 0;
    engineDisplayTimers[currentCylinder[currentCylinderNum]]->start((1000.0/stepDelay/12), this);

    currentCylinder[currentCylinderNum] = (currentCylinder[currentCylinderNum] + 1) % NUM_CYLINDERS;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    for(int i = 0; i < NUM_CYLINDERS; i++)
    {
        if(event->timerId() == engineDisplayTimers[i]->timerId())
        {
            //qDebug() << "timer event " + i;
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

    //if we've done a full cycle we stop
    if(cycle_number[ignition] == 0)
    {
//        engineDisplayTimers[ignition]->stop();
        engineDisplayAvailableToDraw[ignition] = 1;
    }
}

