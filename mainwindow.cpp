#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>
#include <QGridLayout>
#include "point.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand(time(NULL));
    game = new Game;
    game->init(6, 7, Game::BLACK_PLAYER);
    qDebug() << game->applyMove(Point(6, 4));
    ui->setupUi(this);

    board = new Board(this);
    board->setGame(game);
        QGridLayout *layout = new QGridLayout(ui->centralWidget);
        layout->setMargin(0);
        layout->addWidget(board);
    board->update();

    // status bar
//    status = new QLabel("Please load a sample.");
//    status->setMinimumSize(status->sizeHint());
//    status->setAlignment(Qt::AlignHCenter);
//    ui->statusBar->addWidget(status);
}

MainWindow::~MainWindow()
{
    delete ui;
}
