#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secondwindow.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    EcoSystemOf sus;
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    secondWindow *window;
};

#endif // MAINWINDOW_H
