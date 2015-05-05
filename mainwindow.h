#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "board.h"
#include "controller.h"

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
    void on_actionCurrent_Setting_triggered();

    void on_actionNew_Setting_triggered();

    void on_actionDefault_Setting_triggered();

private:
    Ui::MainWindow *ui;
    Controller *controller;
    Board *board;
    QLabel *status;
};

#endif // MAINWINDOW_H
