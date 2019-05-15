#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QPixmap>
#include <QLabel>
#include <QMessageBox>

secondWindow::secondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondWindow)
{
    //QPixmap pix(":/resources/img/card3.png");
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("Card Number");
    ui->lineEdit_2->setPlaceholderText("MM");
    ui->lineEdit_3->setPlaceholderText("YY");
    ui->lineEdit_4->setPlaceholderText("CARD HOLDER");
    ui->lineEdit_5->setPlaceholderText("CVC");
    //int w = ui->photo->width();
    //int h = ui->photo->height();
    //ui->photo->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

}
secondWindow::~secondWindow()
{
    delete ui;
}

void secondWindow::on_pushButton_2_clicked()
{
    this->close();
}


void secondWindow::on_pushButton_clicked()
{
        QJsonObject myPay;
        myPay["type"] = "pay";
        myPay["cardnumber"] = ui->lineEdit->text();
        myPay["cardholder"] = ui->lineEdit_4->text();
        myPay["MMYY"] = ui->lineEdit_2->text()+"/"+ui->lineEdit_3->text();
        myPay["CVC"]=ui->lineEdit_5->text();
        myPay["paybalance"]= MountOfPay;

        if (all->getPayAll(myPay)){
            QMessageBox::information(this,"INFORMATION","Pay on!");
            this->close();
        }else {
            QMessageBox::warning(this,"WARNING","Pay it's broke");
        }

}
