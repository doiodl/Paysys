#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include "QMessageBox"
#include <QPixmap>
#include <QCheckBox>
#include <QLabel>
#include <QtCore>
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



void MainWindow::on_pushButton_clicked()
{
    int num = (ui->textBrowser->toPlainText()).toInt();
    if (num != 0) {
        secondWindow window;
        window.all = &this->sus;
        window.MountOfPay = ui->textBrowser->toPlainText();
        window.exec();
}
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (!(ui->checkBox->checkState() == Qt::CheckState())){
        int num = (ui->textBrowser->toPlainText()).toInt();
        ui->textBrowser->setText(QString::number(num+1000));
        ui->textBrowser->setAlignment(Qt::AlignRight);
    }
    if (ui->checkBox->checkState() == Qt::CheckState()){
        int num = (ui->textBrowser->toPlainText()).toInt();
        ui->textBrowser->setText(QString::number(num-1000));
        ui->textBrowser->setAlignment(Qt::AlignRight);

    }

}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if (!(ui->checkBox_2->checkState() == Qt::CheckState())){
        int num = (ui->textBrowser->toPlainText()).toInt();
        ui->textBrowser->setText(QString::number(num+100));
        ui->textBrowser->setAlignment(Qt::AlignRight);

    }
    if (ui->checkBox_2->checkState() == Qt::CheckState()){
        int num = (ui->textBrowser->toPlainText()).toInt();
        ui->textBrowser->setText(QString::number(num-100));
        ui->textBrowser->setAlignment(Qt::AlignRight);

    }
}
