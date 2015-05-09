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
    void on_actionDefaultSetting_triggered();
    void on_actionRandomSetting_triggered();
    void on_actionSpecifiedSetting_triggered();
    void on_actionReplay_triggered();
    void on_actionQuit_triggered();

    void on_actionCompete_Setting_triggered();

    void on_actionStrategyFile_triggered();

private:
    Ui::MainWindow *ui;
    Controller *controller;
    Board *board;
    QLabel *status;
};

#endif // MAINWINDOW_H
