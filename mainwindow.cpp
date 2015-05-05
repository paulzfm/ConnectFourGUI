#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>
#include <QGridLayout>
#include <QDebug>

#include "setting_dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand(time(NULL));
    ui->setupUi(this);

    board = new Board(this);
        QGridLayout *layout = new QGridLayout(ui->centralWidget);
        layout->setMargin(0);
        layout->addWidget(board);
    controller = new Controller(this);

    // status bar
    status = new QLabel("Please load a sample.");
    status->setMinimumSize(status->sizeHint());
    status->setAlignment(Qt::AlignHCenter);
    ui->statusBar->addWidget(status);

    // disable actions
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionDefaultSetting_triggered()
{
    controller->loadSettings(6, 7, Controller::HUMAN, Controller::HUMAN, NULL, NULL,
                             Game::BLACK_PLAYER, board);
}

void MainWindow::on_actionRandomSetting_triggered()
{

}

void MainWindow::on_actionSpecifiedSetting_triggered()
{
    SettingDialog *dlg = new SettingDialog(this);
    dlg->show();
}

void MainWindow::on_actionReplay_triggered()
{
    controller->restartGame();
}
