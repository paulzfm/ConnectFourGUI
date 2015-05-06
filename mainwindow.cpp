#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <time.h>
#include <stdlib.h>

#include <QGridLayout>

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
    status = new QLabel("Please launch a new game.");
    status->setMinimumSize(status->sizeHint());
    status->setAlignment(Qt::AlignHCenter);
    ui->statusBar->addWidget(status);
    controller->setStatus(status);

    // disable actions
    ui->actionReplay->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionDefaultSetting_triggered()
{
    controller->loadSettings(8, 8, Controller::HUMAN, Controller::HUMAN, "", "",
                             Game::BLACK_PLAYER, board);
    ui->actionReplay->setEnabled(true);
}

void MainWindow::on_actionRandomSetting_triggered()
{
    SettingDialog *dlg = new SettingDialog(this, true);
    if (dlg->exec() == QDialog::Accepted) {
        Params params;
        dlg->getParams(params);
        controller->loadSettings(params.boardM, params.boardN,
                                 params.blackPlayer, params.whitePlayer,
                                 params.blackStrategy, params.whiteStrategy,
                                 params.firstPlayer, board, params.isRandom);
    }
    ui->actionReplay->setEnabled(true);
}

void MainWindow::on_actionSpecifiedSetting_triggered()
{
    SettingDialog *dlg = new SettingDialog(this, false);
    if (dlg->exec() == QDialog::Accepted) {
        Params params;
        dlg->getParams(params);
        controller->loadSettings(params.boardM, params.boardN,
                                 params.blackPlayer, params.whitePlayer,
                                 params.blackStrategy, params.whiteStrategy,
                                 params.firstPlayer, board, params.isRandom);
    }
    ui->actionReplay->setEnabled(true);
}

void MainWindow::on_actionReplay_triggered()
{
    controller->restartGame();
}

void MainWindow::on_actionIntervalReset_triggered()
{
    controller->setSpeed(1);
}

void MainWindow::on_actionIntervalPlus_triggered()
{
    controller->setSpeed(controller->getSpeed() + 1);
}

void MainWindow::on_actionIntervalMinus_triggered()
{
    controller->setSpeed(controller->getSpeed() - 1);
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}
