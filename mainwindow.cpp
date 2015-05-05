#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>
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
    controller = new Controller;

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

void MainWindow::on_actionCurrent_Setting_triggered()
{
    controller->restartGame();
}

void MainWindow::on_actionNew_Setting_triggered()
{

}

void MainWindow::on_actionDefault_Setting_triggered()
{
    controller->loadSettings(6, 7, Controller::HUMAN, Controller::HUMAN, NULL, NULL, Game::BLACK_PLAYER);
    board->setController(controller);
    board->update();
}
