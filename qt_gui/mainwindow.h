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

private:

    bool readyToRead = false;
    QFile *traceFile;
    QTextStream *traceFileIn;
    QTimer *runTimer;
    int stepDelay;

    int execution_counter;

    Ui::MainWindow *ui;

    void openTrace();
    void stopRunning();
};

#endif // MAINWINDOW_H