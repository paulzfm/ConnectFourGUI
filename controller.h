#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QLabel>
#include <QTimer>
#include <QMainWindow>

#include <string>

#include "strategy.h"
#include "game.h"
#include "board.h"

struct Params
{
    int boardM;
    int boardN;
    int firstPlayer;
    bool isRandom;
    int blackPlayer;
    int whitePlayer;
    std::string blackStrategy;
    std::string whiteStrategy;
    int interval;

    Params();
};


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
    void loadSettings(Params& param, Board* board);

    // restart a new game with current setting
    void restartGame();

    // set status bar
    void setStatus(QLabel *status);

    // set info bar
    void setInfo(QLabel *info);

    // set main window and desktop
    void setWindow(QMainWindow *window);

    // game speed: only available in compete mode (two computer players)
    int getSpeed();

    // access game object
    Game* getGame();

    // save current params
    Params paramsBak;

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
    QLabel *info;
    QMainWindow *window;

    // first call this then applyMove
    void makeDecision();

    // after game is over
    void gameOver();

private slots:
    // call this when timer is timed out
    void callStrategy();
};

#endif // CONTROLLER_H
