#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_browse_button_clicked()
{
    QString fileName = QFileDialog::getOpenFileName();
}

void MainWindow::on_step_number_valueChanged(int num)
{

}

void MainWindow::on_steps_freq_valueChanged(int freq)
{

}

void MainWindow::on_exec_button_clicked()
{

}
