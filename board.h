#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QVector>
#include <QRect>

#include "game.h"

namespace Ui {
class Board;
}

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = 0);
    ~Board();

    // parameters for drawing
    const static int SPAN = 40;
    const static int RADIUS = 15;

    // drawing events
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    // associate with a specified game
    void setGame(Game* game);

    // enable board
    void enable();

signals:
    // player makes a move by clicking
    void moveMade(const Point& pos);

private:
    Ui::Board *ui;
    Game *game;
    Point currentPos;
    bool enabled;
    QVector<Point> available;

    // update currentPos
    void updateCurrentPos(int x, int y);

    // transformer
    Point toBoardPos(const Point& pos);
    QRect toChessRect(const Point& pos);
};

#endif // BOARD_H
