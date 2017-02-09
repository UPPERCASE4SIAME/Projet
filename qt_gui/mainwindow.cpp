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
    connect(runTimer, SIGNAL(timeout()), this, SLOT(readLineFromTrace()));

    stopTimer = new QTimer(this);
    connect(stopTimer, SIGNAL(timeout()), this, SLOT(stopRunning()));

    stepDelay = 1;
    execution_counter = 0;

    ui->setupUi(this);

    init_displays();
}

MainWindow::~MainWindow()
{
    delete traceFile;
    delete traceFileIn;
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

void MainWindow::init_displays()
{
    int index = ui->tabWidget->currentIndex();

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

    openTrace();

    if(readyToRead)
    {
        startRunning(0);
    }
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
    if(!readyToRead)
    {
        openTrace();
    }

    if(readyToRead)
    {
        startRunning(0);
    }
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
        runTimer->stop();
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
    openTrace();

    if(readyToRead)
    {
        runTimer->start(0);
    }
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

void MainWindow::readLineFromTrace()
{
    static QString line;
    static QStringList values;

    static QRegExp lineFormatExp("\\d+;\\d+;\\d+;\\d+;\\d+;\\d+;\\d+");

    qDebug() << "reading line";


    if(!traceFileIn->atEnd())
    {
        line = traceFileIn->readLine();

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

    }
    else
    {
        if(!stopTimer->isActive())
        {
            stopTimer->start(5000);
        }
    }
}

void MainWindow::stopRunning()
{
    runTimer->stop();
    stopTimer->stop();
    readyToRead = false;
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
    init_displays();
}

//void MainWindow::drawGraph()
//{
//    http://www.advsofteng.com/doc/cdcppdoc/realtimedemoqt.htm
//}

