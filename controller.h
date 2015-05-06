#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QLabel>
#include <string>

#include "strategy.h"
#include "game.h"
#include "board.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    void loadSettings(int boardM, int boardN, int roleBlack, int roleWhite,
                      std::string dylibBlack, std::string dylibWhite, int firstPlayer,
                      Board* board, int speed = 0);
    void setStatus(QLabel *status);
    void setSpeed(int speed);
    void restartGame();

    void makeDecision();

    void gameOver();

    Game* getGame();

    const static int HUMAN = 1;
    const static int COMPUTER = 2;

public slots:
    void applyMove(const Point& pos);

private:
    int roleBlack;
    int roleWhite;
    Strategy *strategyBlack;
    Strategy *strategyWhite;
    Board *board;
    Game *game;
    QLabel *status;
    int speed;
};

#endif // CONTROLLER_H
