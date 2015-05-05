#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "board.h"
#include "controller.h"
#include "setting_dialog.h"

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

private:
    Ui::MainWindow *ui;
    Controller *controller;
    Board *board;
    QLabel *status;

    void loadParams(Params& param);
};

#endif // MAINWINDOW_H
