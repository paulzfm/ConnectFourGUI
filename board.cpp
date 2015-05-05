#include "board.h"
#include "ui_board.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>

Board::Board(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Board)
{
    ui->setupUi(this);
    game = NULL;
}

Board::~Board()
{
    delete ui;
}

void Board::setController(Controller *controller)
{
    this->controller = controller;
    game = controller->getGame();
    setMouseTracking(true);
}

void Board::paintEvent(QPaintEvent *)
{
    if (!game) {
        return;
    }

    QPainter painter(this);
    // draw grids
    for (int i = 0; i < game->boardM() + 2; i++) {
        painter.drawLine(0, i * SPAN, (game->boardN() + 1) * SPAN, i * SPAN);
    }
    for (int i = 0; i < game->boardN() + 2; i++) {
        painter.drawLine(i * SPAN, 0, i * SPAN, (game->boardM() + 1) * SPAN);
    }

    // draw chess
    for (int i = 0; i < game->boardM(); i++) {
        for (int j = 0; j < game->boardN(); j++) {
            if (game->chess(i, j) == Game::BLACK_PLAYER) {
                painter.setBrush(QBrush(Qt::black));
                painter.setPen(QPen(Qt::black));
                painter.drawEllipse(QPoint((i + 1) * SPAN, (j + 1) * SPAN), RADIUS, RADIUS);
            } else if (game->chess(i, j) == Game::WHITE_PLAYER) {
                painter.setBrush(QBrush(Qt::white));
                painter.setPen(QPen(Qt::white));
                painter.drawEllipse(QPoint((i + 1) * SPAN, (j + 1) * SPAN), RADIUS, RADIUS);
            }
        }
    }

    // draw not pos
    if (game->player() != Game::GAME_OVER) {
        Point p = game->notPos();
        painter.setBrush(QBrush(Qt::red));
        painter.drawEllipse(QPoint((p.x + 1) * SPAN, (p.y + 1) * SPAN), RADIUS, RADIUS);
    }

    // draw last position
    Point p = game->lastPos();
    painter.setPen(QPen(Qt::red));
    painter.setBrush(QBrush());
    painter.drawRect(p.x * SPAN + (SPAN - RADIUS), p.y * SPAN + (SPAN - RADIUS), RADIUS * 2, RADIUS * 2);

    if (!controller->enabled()) {
        return;
    }

    // draw current position
    painter.setPen(QPen(Qt::blue));
    painter.setBrush(QBrush());
    painter.drawEllipse(QPoint((currentPos.x + 1) * SPAN, (currentPos.y + 1) * SPAN), RADIUS, RADIUS);
}

void Board::mouseMoveEvent(QMouseEvent *event)
{
    if (!controller->enabled()) {
        return;
    }

    updateCurrentPos(event->x(), event->y());
}

void Board::mousePressEvent(QMouseEvent *event)
{

}

void Board::mouseReleaseEvent(QMouseEvent *event)
{

}

void Board::updateCurrentPos(int x, int y)
{
    currentPos.x = x / SPAN - 1;
    currentPos.y = y / SPAN - 1;
    update();
}
