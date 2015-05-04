#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
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
    void setGame(Game *game);

    const static int SPAN = 30;
    const static int RADIUS = 12;
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::Board *ui;
    Game *game;
    bool enabled;

    Point chessPos(QMouseEvent* event) const;
};

#endif // BOARD_H
