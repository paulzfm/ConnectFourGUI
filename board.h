#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QVector>
#include "controller.h"

namespace Ui {
class Board;
}

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = 0);
    ~Board();
    void setController(Controller *controller);

    const static int SPAN = 30;
    const static int RADIUS = 12;
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enable();

private:
    Ui::Board *ui;
    Game *game;
    Controller *controller;
    Point currentPos;
    bool enabled;
    QVector<Point> available;
    void updateCurrentPos(int x, int y);
};

#endif // BOARD_H
