#include "game.h"
#include "judge.h"

#include <vector>
#include <stdlib.h>

Game::Game(const int M, const int N, int firstPlayer)
{
    _boardM = M;
    _boardN = N;
    _player = firstPlayer;
    _firstPlayer = firstPlayer;

    _tops = new int[N];
    for (int i = 0; i < N; i++) {
        _tops[i] = M;
    }

    _board = new int*[M];
    for (int i = 0; i < M; i++) {
        _board[i] = new int[N];
        for (int j = 0; j < N; j++) {
            _board[i][j] = 0;
        }
    }

    _lastPos = Point(-2, -2);

    // randomize not position
    _notPos = Point(rand() % M, rand() % N);
}

Game::~Game()
{
    delete[] _tops;
    for (int i = 0; i < _boardM; i++) {
        delete[] _board[i];
    }
    delete[] _board;
}

int Game::applyMove(const Point& pos)
{
    if (isLegalMove(pos)) {
        return ILLEGAL_MOVE;
    }

    // apply
    _board[pos.x][pos.y] = _player;
    _tops[pos.y]--;
    _lastPos = pos;

    // judge
    // so-called "user" is BLACK player with mark "1" and "machine" is WHITE player with mark "2"
    if (_player == BLACK_PLAYER && userWin(pos.x, pos.y, _boardM, _boardN, _board)) {
        return BLACK_WIN;
    } else if (_player == WHITE_PLAYER && machineWin(pos.x, pos.y, _boardM, _boardN, _board)) {
        return WHITE_WIN;
    } else if (isTie(_boardN, _tops)) {
        return IS_TIE;
    }

    _player = _player == BLACK_PLAYER ? WHITE_PLAYER : BLACK_PLAYER;
    return GAME_CONTINUE;
}

bool Game::isLegalMove(const Point& pos)
{
    return pos.inRect(_boardM, _boardN) && (_tops[pos.y] == pos.x - 1) && !(_notPos == pos);
}

int Game::player() const
{
    return _player;
}

int Game::boardM() const
{
    return _boardM;
}

int Game::boardN() const
{
    return _boardN;
}

int Game::chess(const Point &p) const
{
    return _board[p.x][p.y];
}

int Game::chess(int x, int y) const
{
    return _board[x][y];
}

Point Game::lastPos() const
{
    return _lastPos;
}

Point Game::notPos() const
{
    return _notPos;
}

const int* Game::top() const
{
    int* tmp = new int[_boardN];
    for (int i = 0; i < _boardN; i++) {
        if (i == _notPos.y && _tops[i] - 1 == _notPos.x) {
            tmp[i] = 0;
        } else {
            tmp[i] = _tops[i];
        }
    }

    return tmp;
}

const int* Game::board() const
{
    int* tmp = new int[_boardM * _boardN];
    if (_player == WHITE_PLAYER) {
        for (int i = 0; i < _boardM; i++) {
            for (int j = 0; j < _boardN; j++) {
                tmp[i * _boardM + j] = _board[i][j];
            }
        }
    } else { // _player == BLACK_PLAYER
        for (int i = 0; i < _boardM; i++) {
            for (int j = 0; j < _boardN; j++) {
                if (_board[i][j] == 0) {
                    tmp[i * _boardM + j] = 0;
                } else if (_board[i][j] == 1) {
                    tmp[i * _boardM + j] = 2;
                } else { // _board[i][j] == 2
                    tmp[i * _boardM + j] = 1;
                }
            }
        }
    }

    return tmp;
}

int Game::firstPlayer() const
{
    return _firstPlayer;
}
