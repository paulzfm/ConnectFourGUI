#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "strategy.h"
#include "game.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    void loadSettings(int boardM, int boardN, int roleBlack, int roleWhite,
                      const char* dylibBlack, const char* dylibWhite, int firstPlayer);

    const static int HUMAN = 1;
    const static int COMPUTER = 2;
signals:

public slots:

private:
    int roleBlack;
    int roleWhite;
    Strategy *strategyBlack;
    Strategy *strategyWhite;
    Game *game;
};

#endif // CONTROLLER_H
