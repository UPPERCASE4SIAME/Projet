#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QLineEdit>
#include <QDebug>
#include <QTimer>
#include <QLabel>

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

    void on_pause_button_clicked();

    void on_browseEdit_exec_editingFinished();

    void on_browse_button_exec_clicked();

    void on_browseEdit_save_exec_editingFinished();

    void on_browse_button_save_exec_clicked();

    void on_save_button_exec_clicked();

    void on_tabWidget_currentChanged(int index);

private:

    bool readyToRead = false;    
    QFile *traceFile;
    QTextStream *traceFileIn;
    QLineEdit* browseEdit;


    QTimer *runTimer;
    int stepDelay;
    int execution_counter;

    QLabel* ignition1;
    QLabel* ignition2;
    QLabel* ignition3;
    QLabel* ignition4;
    QLabel* ignition5;
    QLabel* ignition6;

    Ui::MainWindow *ui;

    void openTrace();
    void stopRunning();
    void init_displays();
};

#endif // MAINWINDOW_H
