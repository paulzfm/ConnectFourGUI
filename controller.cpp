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
    makeDecision();
}

void Controller::restartGame()
{
    Game* tmp = game;
    game = new Game(tmp->boardM(), tmp->boardN(), tmp->firstPlayer());
    delete tmp;
    makeDecision();
}

void Controller::makeDecision()
{
    int player = game->player();
    if (player == Game::BLACK_PLAYER && roleBlack == COMPUTER) {
        const int* top = game->top();
        const int* board = game->board();
        Point pos = strategyBlack->getDecision(game->boardM(), game->boardN(), top, board,
            game->lastPos().x, game->lastPos().y, game->notPos().x, game->notPos().y);
        delete[] top;
        delete[] board;
        applyMove(pos);
    } else if (player == Game::WHITE_PLAYER && roleWhite == COMPUTER) {
        const int* top = game->top();
        const int* board = game->board();
        Point pos = strategyWhite->getDecision(game->boardM(), game->boardN(), top, board,
            game->lastPos().x, game->lastPos().y, game->notPos().x, game->notPos().y);
        delete[] top;
        delete[] board;
        applyMove(pos);
    } else { // HUMAN
        //board->enable();
        // wait for callback: applyMove
    }
}

void Controller::applyMove(const Point &pos)
{
    switch (game->applyMove(pos)) {
    case Game::ILLEGAL_MOVE:
        break;
    case Game::BLACK_WIN:
        break;
    case Game::WHITE_WIN:
        break;
    case Game::IS_TIE:
        break;
    case Game::GAME_CONTINUE:
        makeDecision();
        break;
    default:
        break;
    }
}

Game* Controller::getGame()
{
    return game;
}
