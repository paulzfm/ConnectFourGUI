#include "board.h"
#include "ui_board.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <iostream>

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

void Board::setGame(Game* game)
{
    this->game = game;
    this->setMouseTracking(true);
}

void Board::enable()
{
    enabled = true;
    available.clear();
    const int* top = game->top();
    for (int i = 0; i < game->boardN(); i++) {
        if (top[i] != 0) {
            available.push_back(Point(top[i] - 1, i));
        }
    }
    delete top;
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
                painter.setPen(QPen());
                painter.drawEllipse(toChessRect(Point(i, j)));
            } else if (game->chess(i, j) == Game::WHITE_PLAYER) {
                painter.setBrush(QBrush(Qt::white));
                painter.setPen(QPen());
                painter.drawEllipse(toChessRect(Point(i, j)));
            }
        }
    }

    // draw not pos
    if (game->player() != Game::GAME_OVER) {
        painter.setPen(QPen());
        painter.setBrush(QBrush(Qt::red));
        painter.drawEllipse(toChessRect(game->notPos()));
    }

    // draw last position
    painter.setPen(QPen(Qt::red));
    painter.setBrush(QBrush());
    painter.drawRect(toChessRect(game->lastPos()));

    // draw current position
    if (!enabled || currentPos.isEmpty()) {
        return;
    }

//    std::cout << game->player() << std::endl;
//    int color = game->player() == Game::BLACK_PLAYER ? Qt::black : Qt::white;
    painter.setPen(QPen());
    if (game->player() == Game::BLACK_PLAYER) {
        painter.setBrush(QBrush(Qt::black));
    } else {
        painter.setBrush(QBrush(Qt::white));
    }
    painter.drawEllipse(toChessRect(currentPos));
}

void Board::mouseMoveEvent(QMouseEvent *event)
{
    if (!enabled) {
        return;
    }

    updateCurrentPos(event->x(), event->y());
}

void Board::mouseReleaseEvent(QMouseEvent *event)
{
    if (!enabled) {
        return;
    }

    updateCurrentPos(event->x(), event->y());

    if (!currentPos.isEmpty()) {
        enabled = false;
        emit moveMade(currentPos);
        currentPos = Point::empty();
    }
}

void Board::updateCurrentPos(int x, int y)
{
    currentPos = toBoardPos(Point(x, y));
    update();
}

Point Board::toBoardPos(const Point &pos)
{
    for (int i = 0; i < available.size(); i++) {
        if (pos.inRect(toChessRect(available[i]))) {
            return available[i];
        }
    }

    return Point::empty();
}

QRect Board::toChessRect(const Point &pos)
{
    return QRect(pos.y * SPAN + (SPAN - RADIUS), pos.x * SPAN + (SPAN - RADIUS),
                 RADIUS * 2, RADIUS * 2);
}
