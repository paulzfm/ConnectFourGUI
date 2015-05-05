#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{

}

void Controller::loadSettings(int boardM, int boardN, int roleBlack, int roleWhite,
                              const char *dylibBlack, const char *dylibWhite, int firstPlayer)
{
    this->roleBlack = roleBlack;
    this->roleWhite = roleWhite;
    if (roleBlack == COMPUTER) {
        this->strategyBlack = new Strategy(dylibBlack);
    }
    if (roleWhite == COMPUTER) {
        this->strategyWhite = new Strategy(dylibWhite);
    }

    game = new Game(boardM, boardN, firstPlayer);
}

