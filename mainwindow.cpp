#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    traceFile = new QFile();
    traceFileIn = new QTextStream();

    runTimer = new QTimer(this);
    connect(runTimer, SIGNAL(timeout()), this, SLOT(readLineFromTrace()));

    stepDelay = 1;

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete traceFile;
    delete traceFileIn;
    delete runTimer;

    delete ui;
}

void MainWindow::on_browse_button_clicked()
{
    QString fileName = QFileDialog::getOpenFileName();

    qDebug() << fileName;

    QLineEdit* browseEdit = ui->browseEdit;

    browseEdit->setText(fileName);

    openTrace();
}

void MainWindow::on_current_rotation_counter_valueChanged(int arg1)
{

}

void MainWindow::on_rotation_freq_counter_valueChanged(int newValue)
{
    stepDelay = newValue;
}

void MainWindow::on_execution_button_clicked()
{
    if(readyToRead)
    {
        traceFileIn = new QTextStream(traceFile);

        runTimer->start(1000/stepDelay);
    }
}

void MainWindow::on_pause_button_clicked()
{
    stopRunning();
}

void MainWindow::on_browseEdit_editingFinished()
{
    openTrace();
}

void MainWindow::openTrace()
{
    QLineEdit* browseEdit = ui->browseEdit;

    QString fileName = browseEdit->text();

    QFileInfo check_traceFile(fileName);

    //if our trace file doesn't exist or it's not a valid file then we'll just wait for the user to give us another file
    if(!check_traceFile.exists() || !check_traceFile.isFile())
    {
        readyToRead = false;
        return;
    }

    traceFile = new QFile(fileName);

    if (!traceFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        readyToRead = false;
        return;
    }

    readyToRead = true;
}

void MainWindow::readLineFromTrace()
{
    static QString line;

    if(!traceFileIn->atEnd())
    {
        line = traceFileIn->readLine();

//        (QLabel*)ui->ignition1_value_label->setText();
//        (QLabel*)ui->ignition2_value_label->setText();
//        (QLabel*)ui->ignition3_value_label->setText();
//        (QLabel*)ui->ignition4_value_label->setText();
//        (QLabel*)ui->ignition5_value_label->setText();
//        (QLabel*)ui->ignition6_value_label->setText();
    }
    else
    {
        stopRunning();
    }
}

void MainWindow::stopRunning()
{
    runTimer->stop();
}

