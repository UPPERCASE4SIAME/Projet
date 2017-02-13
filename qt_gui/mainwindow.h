#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QLineEdit>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtCharts>
#include <QTextCodec>
#include <QMutex>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_browse_button_clicked();

    void on_rotation_freq_counter_valueChanged(int newValue);

    void on_execution_button_clicked();

    void on_browseEdit_editingFinished();

    void readLineFromTrace();
    
    void readLineFromDevice();

    void on_pause_button_clicked();

    void on_browseEdit_exec_editingFinished();

    void on_browse_button_exec_clicked();

    void on_browseEdit_save_exec_editingFinished();

    void on_browse_button_save_exec_clicked();

    void on_save_button_exec_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_readDevice_button_clicked();

private:

    bool readyToRead = false;    
    QFile *traceFile;
    QSerialPort *device;
    QTextStream *traceFileIn;

    QTimer *runTimer;

    int stepDelay;
    int execution_counter;

    QLineEdit* browseEdit;

    QLabel* ignition1;
    QLabel* ignition2;
    QLabel* ignition3;
    QLabel* ignition4;
    QLabel* ignition5;
    QLabel* ignition6;

    QLineSeries* ignition1Data;
    QLineSeries* ignition2Data;
    QLineSeries* ignition3Data;
    QLineSeries* ignition4Data;
    QLineSeries* ignition5Data;
    QLineSeries* ignition6Data;

    QChartView* ignitionChartView;
    
    QMutex* drawMutex;

    Ui::MainWindow *ui;

    void openTrace();
    void stopRunning();
    void initDisplays(int index);
    void startRunning(float delay);
    void openDevice();
    void changeTimerCalls(int index);
    void drawGraph(QStringList values);
    void addIgnitionData(QLineSeries *series, int peak, int seriesNumber, int interval);
};

#endif // MAINWINDOW_H
