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

    //qDebug() << fileName;

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
    static QStringList values;

    static QLabel* ignition1 = (QLabel*)ui->ignition1_value_label;
    static QLabel* ignition2 = (QLabel*)ui->ignition2_value_label;
    static QLabel* ignition3 = (QLabel*)ui->ignition3_value_label;
    static QLabel* ignition4 = (QLabel*)ui->ignition4_value_label;
    static QLabel* ignition5 = (QLabel*)ui->ignition5_value_label;
    static QLabel* ignition6 = (QLabel*)ui->ignition6_value_label;

    static QSpinBox* rotation_counter = (QSpinBox*)ui->current_rotation_counter;

    if(!traceFileIn->atEnd())
    {
        line = traceFileIn->readLine();

        //qDebug() << line;

        values = line.split(";");

        ignition1->setText(values[1]);
        ignition2->setText(values[2]);
        ignition3->setText(values[3]);
        ignition4->setText(values[4]);
        ignition5->setText(values[5]);
        ignition6->setText(values[6]);

        rotation_counter->setValue(rotation_counter->value() + 1);
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

