#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QLabel>
#include <QTimer>

#include <string>

#include "strategy.h"
#include "game.h"
#include "board.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();

    // player roles
    const static int HUMAN = 1;
    const static int COMPUTER = 2;

    // must first call this when create a new game
    void loadSettings(int boardM, int boardN, int roleBlack, int roleWhite,
                      std::string dylibBlack, std::string dylibWhite,
                      int firstPlayer, Board* board, int speed = 1,
                      bool random = false);

    // restart a new game with current setting
    void restartGame();

    // set status bar
    void setStatus(QLabel *status);

    // game speed: only available in compete mode (two computer players)
    int getSpeed();

    // access game object
    Game* getGame();

public slots:
    // either call manually for callback with signal emiting
    void applyMove(const Point& pos);

    // set speed
    void setSpeed(int speed);

private:
    int roleBlack;
    int roleWhite;
    std::string dylibBlack;
    std::string dylibWhite;
    bool isRandom;
    Strategy *strategyBlack;
    Strategy *strategyWhite;
    Board *board;
    Game *game;

    bool isCompete;
    int speed;
    QTimer *timer;

    QLabel *status;

    // first call this then applyMove
    void makeDecision();

    // after game is over
    void gameOver();

private slots:
    // call this when timer is timed out
    void callStrategy();
};

#endif // CONTROLLER_H
