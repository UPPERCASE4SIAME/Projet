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

    ignition1Data = new QLineSeries();
    ignition2Data = new QLineSeries();
    ignition3Data = new QLineSeries();
    ignition4Data = new QLineSeries();
    ignition5Data = new QLineSeries();
    ignition6Data = new QLineSeries();

    ui->setupUi(this);

	int curr_index = ui->tabWidget->currentIndex();

    initDisplays(curr_index);
    changeTimerCalls(curr_index);
}

MainWindow::~MainWindow()
{
    delete traceFile;
    delete traceFileIn;
    delete device;

    delete runTimer;

    delete ignition1;
    delete ignition2;
    delete ignition3;
    delete ignition4;
    delete ignition5;
    delete ignition6;

    delete browseEdit;

    delete ui;
}

void MainWindow::initDisplays(int index)
{
    /* depending on which tab we are on, our line reading function is going to write to different labels
       our file will also be different
        those names can be changed in the form editor */
    if(index == EXEC_MODE_INDEX)
    {
        browseEdit = (QLineEdit*)ui->browseEdit_exec;

        ignition1 = (QLabel*)ui->ignition1_value_label_exec;
        ignition2 = (QLabel*)ui->ignition2_value_label_exec;
        ignition3 = (QLabel*)ui->ignition3_value_label_exec;
        ignition4 = (QLabel*)ui->ignition4_value_label_exec;
        ignition5 = (QLabel*)ui->ignition5_value_label_exec;
        ignition6 = (QLabel*)ui->ignition6_value_label_exec;

        ignitionChartView = (QChartView*)ui->ignition_chart_exec;
    }
    else if (index == TRACE_MODE_INDEX)
    {
        browseEdit = (QLineEdit*)ui->browseEdit;

        ignition1 = (QLabel*)ui->ignition1_value_label;
        ignition2 = (QLabel*)ui->ignition2_value_label;
        ignition3 = (QLabel*)ui->ignition3_value_label;
        ignition4 = (QLabel*)ui->ignition4_value_label;
        ignition5 = (QLabel*)ui->ignition5_value_label;
        ignition6 = (QLabel*)ui->ignition6_value_label;

        ignitionChartView = (QChartView*)ui->ignition_chart_trace;
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

void MainWindow::on_rotation_freq_counter_valueChanged(int newValue)
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
    
    //QSerialPortInfo check_device(fileName);

    //if our device doesn't exist or it's not a valid file then we'll just wait for the user to give us another file
    //if(check_device.isNull() || check_device.isBusy())
    //{
        //readyToRead = false;

        //qDebug() << "device doesn't exist or is unreadable";
        //return;
    //}


    device = new QSerialPort(this);
    
    qDebug() << "blah";
    
    device->setPortName(fileName);
    
    qDebug() << "meh";
    

    if (!device->open(QIODevice::ReadWrite))
    {

        qDebug() << "couldn't open device";
        readyToRead = false;
        return;
    }

    readyToRead = true;
    
    qDebug() << "device opened";
    
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

        ignition1->setText(values[1]);
        ignition2->setText(values[2]);
        ignition3->setText(values[3]);
        ignition4->setText(values[4]);
        ignition5->setText(values[5]);
        ignition6->setText(values[6]);

        drawGraph(values);
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
    
    qDebug() << line;
    
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

    ignition1->setText(values[1]);
    ignition2->setText(values[2]);
    ignition3->setText(values[3]);
    ignition4->setText(values[4]);
    ignition5->setText(values[5]);
    ignition6->setText(values[6]);

    drawGraph(values);
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

void MainWindow::drawGraph(QStringList values)
{
    //http://www.advsofteng.com/doc/cdcppdoc/realtimedemoqt.htm

    //extract all the values as integers and not strings
    int interval = ((QString)values[0]).toInt();

    int ignition1Value = ((QString)values[1]).toInt();
    int ignition2Value = ((QString)values[2]).toInt();
    int ignition3Value = ((QString)values[3]).toInt();
    int ignition4Value = ((QString)values[4]).toInt();
    int ignition5Value = ((QString)values[5]).toInt();
    int ignition6Value = ((QString)values[6]).toInt();

    //create the new chart with axes
    QChart* newChart = new QChart();

    //when the setup is done we can add all of our data to the chart
    addIgnitionData(ignition1Data, ignition1Value, 1, interval);
    addIgnitionData(ignition2Data, ignition2Value, 2, interval);
    addIgnitionData(ignition3Data, ignition3Value, 3, interval);
    addIgnitionData(ignition4Data, ignition4Value, 4, interval);
    addIgnitionData(ignition5Data, ignition5Value, 5, interval);
    addIgnitionData(ignition6Data, ignition6Value, 6, interval);

    newChart->addSeries(ignition1Data);
    newChart->addSeries(ignition2Data);
    newChart->addSeries(ignition3Data);
    newChart->addSeries(ignition4Data);
    newChart->addSeries(ignition5Data);
    newChart->addSeries(ignition6Data);

    QCategoryAxis *axisX = new QCategoryAxis();
    QCategoryAxis *axisY = new QCategoryAxis();

    //we don't care about the legend because it's next to the axes anyway
    newChart->legend()->hide();

    //we want to make it so even if the ignition got off at the last moment we can still see the peak
    axisX->setRange(0, interval * 1.1);
    axisY->setRange(0, 7);

    //put labels on the axes
    axisY->append("Ignition 1", 1);
    axisY->append("Ignition 2", 2);
    axisY->append("Ignition 3", 3);
    axisY->append("Ignition 4", 4);
    axisY->append("Ignition 5", 5);
    axisY->append("Ignition 6", 6);

    axisY->setLabelsPosition(QCategoryAxis::AxisLabelsPosition::AxisLabelsPositionOnValue);

    newChart->setAxisX(axisX);
    newChart->setAxisY(axisY);

    //ignition1Data->attachAxis(newChart->axisX());
    ignition1Data->attachAxis(newChart->axisY());

    //ignition2Data->attachAxis(newChart->axisX());
    ignition2Data->attachAxis(newChart->axisY());

    //ignition3Data->attachAxis(newChart->axisX());
    ignition3Data->attachAxis(newChart->axisY());

    //ignition4Data->attachAxis(newChart->axisX());
    ignition4Data->attachAxis(newChart->axisY());

    //ignition5Data->attachAxis(newChart->axisX());
    ignition5Data->attachAxis(newChart->axisY());

    //ignition6Data->attachAxis(newChart->axisX());
    ignition6Data->attachAxis(newChart->axisY());

    //and display it in our view
    ignitionChartView->setChart(newChart);
}

void MainWindow::addIgnitionData(QLineSeries* series, int peak, int seriesNumber, int interval)
{
    float step = float(interval)/12;

    series->clear();

    series->append(0, seriesNumber);
    series->append(peak, seriesNumber);
    series->append(peak, seriesNumber + 0.3);
    series->append(peak + step, seriesNumber + 0.3);
    series->append(peak + step, seriesNumber);
    series->append(interval, seriesNumber);
}

