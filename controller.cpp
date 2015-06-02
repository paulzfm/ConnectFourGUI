#include "controller.h"

#include <QApplication>
#include <QMessageBox>
#include <QFileInfo>
#include <QSize>

#include <string>

Params::Params()
{
    boardM = boardN = 10;
    firstPlayer = Game::BLACK_PLAYER;
    isRandom = false;
    blackPlayer = Controller::HUMAN;
    whitePlayer = Controller::HUMAN;
    blackStrategy = "";
    whiteStrategy = "";
    interval = 0;
}

Controller::Controller(QObject *parent) : QObject(parent)
{
    isCompete = false;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(callStrategy()));

    strategyBlack = NULL;
    strategyWhite = NULL;
    game = NULL;
    board = NULL;
}

Controller::~Controller()
{
    if (game)
        delete game;
    if (strategyBlack)
        delete strategyBlack;
    if (strategyWhite)
        delete strategyWhite;
}

void Controller::loadSettings(Params& param, Board* board)
{
    status->setText("Loading...");

    // allocate players
    this->roleBlack = param.blackPlayer;
    this->roleWhite = param.whitePlayer;
    this->board = board;
    this->dylibBlack = param.blackStrategy;
    this->dylibWhite = param.whiteStrategy;
    Strategy* old1 = this->strategyBlack;
    Strategy* old2 = this->strategyWhite;
    if (roleBlack == COMPUTER) {
        this->strategyBlack = new Strategy(dylibBlack);
    }
    if (roleWhite == COMPUTER) {
        this->strategyWhite = new Strategy(dylibWhite);
    }
    if (old1) {
        delete old1;
    }
    if (old2) {
        delete old2;
    }

    // compete mode
    if (roleBlack == COMPUTER && roleWhite == COMPUTER) {
        isCompete = true;
    } else {
        isCompete = false;
    }

    // random mode
    int boardM = param.boardM;
    int boardN = param.boardN;
    int firstPlayer = param.firstPlayer;
    if (param.isRandom) {
        isRandom = true;
        boardM = 7 + rand() % 6;
        boardN = 7 + rand() % 6;
        firstPlayer = rand() % 2 == 0 ?
            Game::BLACK_PLAYER : Game::WHITE_PLAYER;
    } else {
        isRandom = false;
    }

    // associate with game and board
    Game* old = game;
    game = new Game(boardM, boardN, param.firstPlayer);
    board->setGame(game);
    connect(board, SIGNAL(moveMade(Point)), this, SLOT(applyMove(Point)));
    if (old) {
        delete old;
    }

    // speed
    this->speed = param.interval;

    // save current params
    this->paramsBak = param;

    // resize window
    QSize size(board->SPAN * (boardN + 1), board->SPAN * (boardM + 1));
    board->setFixedSize(size);
    window->resize(size.width(), size.height() + board->SPAN + 20);

    // update info
    QString txt;
    std::string black = "HUMAN";
    std::string white = "HUMAN";
    if (roleBlack == COMPUTER) {
        black = QFileInfo(QString::fromStdString(dylibBlack)).fileName().toStdString();
    }
    if (roleWhite == COMPUTER) {
        white = QFileInfo(QString::fromStdString(dylibWhite)).fileName().toStdString();
    }
    txt.sprintf("[%i×%i] (Black) %s VS %s (White)",
                boardM, boardN, black.c_str(), white.c_str());
    info->setText(txt);

    // start first round
    makeDecision();
}

void Controller::setStatus(QLabel *status)
{
    this->status = status;
}

void Controller::setInfo(QLabel *info)
{
    this->info = info;
}

void Controller::setWindow(QMainWindow *window)
{
    this->window = window;
}

void Controller::restartGame()
{
    // clear trash
    disconnect(board, SIGNAL(moveMade(Point)), this, SLOT(applyMove(Point)));

    // start game with current settings
    loadSettings(this->paramsBak, this->board);
}

void Controller::makeDecision()
{
    int player = game->player();
    if (player == Game::BLACK_PLAYER) {
        status->setText("Black's move...");
    } else {
        status->setText("White's move...");
    }

    if ((player == Game::BLACK_PLAYER && roleBlack == COMPUTER) ||
        (player == Game::WHITE_PLAYER && roleWhite == COMPUTER)) {
        if (isCompete) {
            timer->start(1000 * speed);
            // wait for timeout
        } else {
            callStrategy();
        }
    } else { // HUMAN
        board->enable();
        // wait for move made
    }
}

void Controller::callStrategy()
{
    if (timer->isActive()) {
        timer->stop();
    }

    const int* top = game->top();
    const int* board = game->board();
    Point pos;
    if (game->player() == Game::BLACK_PLAYER) {
        pos = strategyBlack->getDecision(game->boardM(), game->boardN(), top, board,
            game->lastPos().x, game->lastPos().y, game->notPos().x, game->notPos().y);
    } else { // player == Game::WHITE_PLAYER
        pos = strategyWhite->getDecision(game->boardM(), game->boardN(), top, board,
            game->lastPos().x, game->lastPos().y, game->notPos().x, game->notPos().y);
    }
    delete[] top;
    delete[] board;
    applyMove(pos);
}

void Controller::applyMove(const Point &pos)
{
    int ret = game->applyMove(pos);
    board->update();

    switch (ret) {
    case Game::ILLEGAL_MOVE:
        status->setText("Illegal move!");
        QMessageBox::critical(NULL, "Error", "Illegal move! Game will terminate soon!", QMessageBox::Ok);
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
    status->setText("Game over.");
    QMessageBox::StandardButton ret = QMessageBox::question(NULL,
        "Game Over", "Do you want to play again?",
        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (ret == QMessageBox::Yes) {
        restartGame();
    } else {
        status->setText("Please launch a new game.");
    }
}

Game* Controller::getGame()
{
    return game;
}

int Controller::getSpeed()
{
    return this->speed;
}

void Controller::setSpeed(int speed)
{
    this->speed = speed;
}
