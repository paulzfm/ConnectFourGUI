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
    void on_actionReplay_triggered();
    void on_actionQuit_triggered();
    void on_actionStrategyFile_triggered();
    void on_actionCompete_triggered();
    void on_actionOthers_triggered();

    void on_actionHelp_triggered();

    void on_actionAbout_triggered();

    void on_actionCompeteTool_triggered();

private:
    Ui::MainWindow *ui;
    Controller *controller;
    Board *board;
    QLabel *status;
    QLabel *info;
};

#endif // MAINWINDOW_H
