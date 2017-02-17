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
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsScene>
#include <QImage>
#include <QGraphicsPixmapItem>

#define NUM_CYLINDERS 6
#define NUM_ENGINE_ANIMATION_IMAGES 12
#define IMAGE_DIRECTORY "./img/"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

    void engineDisplayNextStateSignal(int ignition);
    void engineDisplayDrawCycleSignal(int ignitionNum, int rotationDuration);

protected:
    void timerEvent(QTimerEvent *event) override;

private slots:
    void on_browse_button_clicked();

    void on_rotation_freq_counter_valueChanged(double newValue);

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


    void drawCycle();

private:

    bool readyToRead = false;    
    QFile *traceFile;
    QSerialPort *device;
    QTextStream *traceFileIn;

    QTimer *runTimer;

    float stepDelay;
    int execution_counter;
    float currentRotationDuration;

    QLineEdit* browseEdit;

    QLabel* ignitionLabels[NUM_CYLINDERS];

    QLineSeries* ignitionData[NUM_CYLINDERS];

    QChart* ignitionChart_trace;
    QChart* ignitionChart_exec;

    QChartView* ignitionChartView;
    QChartView* engineChartView;

    QGraphicsPixmapItem* cycle[NUM_CYLINDERS][NUM_ENGINE_ANIMATION_IMAGES];
    QGraphicsScene* engineCycleScene;
    QBasicTimer* engineDisplayTimers[NUM_CYLINDERS];
    int engineDisplayAvailableToDraw[NUM_CYLINDERS];

    Ui::MainWindow *ui;

    void openTrace();
    void stopRunning();
    void initDisplays(int index);
    void startRunning(float delay);
    void openDevice();
    void changeTimerCalls(int index);
    void setupIgnitionChart(QChart* chart);
    void changeIgnition(QStringList values);
    void setupEngineCycleDisplay();
    void nextState(int ignition);
};

#endif // MAINWINDOW_H
