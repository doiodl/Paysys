#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include "database.h"

namespace Ui {
class secondWindow;
}

class secondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit secondWindow(QWidget *parent = nullptr);
    EcoSystemOf *all; // перенести на основное окно
    QString MountOfPay;
    ~secondWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::secondWindow *ui;
};

#endif // SECONDWINDOW_H
