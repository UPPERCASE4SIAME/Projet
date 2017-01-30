#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>

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

    void on_pushButton_clicked();

    void on_step_number_valueChanged(int num);

    void on_steps_freq_valueChanged(int freq);

    void on_exec_button_clicked();

private:
    Ui::MainWindow *ui;
    QFile *trace;
};

#endif // MAINWINDOW_H
