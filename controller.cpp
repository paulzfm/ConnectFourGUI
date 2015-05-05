#include "controller.h"

#include <QMessageBox>

Controller::Controller(QObject *parent) : QObject(parent)
{

}

void Controller::loadSettings(int boardM, int boardN, int roleBlack, int roleWhite,
                              std::string dylibBlack, std::string dylibWhite, int firstPlayer,
                              Board* board)
{
    status->setText("Loading...");
    this->roleBlack = roleBlack;
    this->roleWhite = roleWhite;
    this->board = board;
    if (roleBlack == COMPUTER) {
        this->strategyBlack = new Strategy(dylibBlack);
    }
    if (roleWhite == COMPUTER) {
        this->strategyWhite = new Strategy(dylibWhite);
    }
    game = new Game(boardM, boardN, firstPlayer);
    board->setGame(game);
    connect(board, SIGNAL(moveMade(Point)), this, SLOT(applyMove(Point)));

    // start first round
    makeDecision();
}

void Controller::setStatus(QLabel *status)
{
    this->status = status;
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
    if (player == Game::BLACK_PLAYER) {
        status->setText("Black's move...");
    } else {
        status->setText("White's move...");
    }

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
        board->enable();
        // wait for callback: applyMove
    }
}

void Controller::applyMove(const Point &pos)
{
    int ret = game->applyMove(pos);
    board->update();

    switch (ret) {
    case Game::ILLEGAL_MOVE:
        status->setText("Illegal move!");
        QMessageBox::information(NULL, "Error", "Illegal move! Game will terminate soon!", QMessageBox::Ok);
        gameOver();
        break;
    case Game::BLACK_WIN:
        status->setText("Black wins!");
        QMessageBox::information(NULL, "Game over", "Black wins!", QMessageBox::Ok);
        gameOver();
        break;
    case Game::WHITE_WIN:
        status->setText("White wins!");
        QMessageBox::information(NULL, "Game over", "White wins!", QMessageBox::Ok);
        gameOver();
        break;
    case Game::IS_TIE:
        status->setText("Is tie!");
        QMessageBox::information(NULL, "Game over", "Tie!", QMessageBox::Ok);
        gameOver();
        break;
    case Game::GAME_CONTINUE:
        makeDecision();
        break;
    default:
        break;
    }
}

void Controller::gameOver()
{
    status->setText("");
}

Game* Controller::getGame()
{
    return game;
}
