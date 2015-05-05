#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>
#include <stdlib.h>
#include <QGridLayout>
#include <QDebug>

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
}

void MainWindow::on_actionRandomSetting_triggered()
{
    SettingDialog *dlg = new SettingDialog(this, true);
    if (dlg->exec() == QDialog::Accepted) {
        Params params;
        dlg->getParams(params);
        loadParams(params);
    }
}

void MainWindow::on_actionSpecifiedSetting_triggered()
{
    SettingDialog *dlg = new SettingDialog(this, false);
    if (dlg->exec() == QDialog::Accepted) {
        Params params;
        dlg->getParams(params);
        loadParams(params);
    }
}

void MainWindow::loadParams(Params& param)
{
    std::cout << "params" << std::endl;
    std::cout << "first: " << param.firstPlayer << std::endl
              << "black: " << param.blackStrategy << std::endl
              << "white: " << param.whiteStrategy << std::endl;

    if (param.isRandom) {
        param.boardM = 7 + rand() % 6;
        param.boardN = 7 + rand() % 6;
        param.firstPlayer = rand() % 2 == 0 ?
                    Game::BLACK_PLAYER : Game::WHITE_PLAYER;
    }

    controller->loadSettings(param.boardM, param.boardN, param.blackPlayer, param.whitePlayer,
                             param.blackStrategy, param.whiteStrategy, param.firstPlayer, board);
}

void MainWindow::on_actionReplay_triggered()
{
    controller->restartGame();
}
