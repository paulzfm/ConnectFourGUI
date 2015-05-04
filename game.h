#ifndef GAME_H
#define GAME_H

#include "strategy.h"

class Game
{
public:
    // game states
    const static int UNINITIAL = 0;
    const static int BLACK_PLAYER = 1;
    const static int WHITE_PLAYER = 2;
    const static int GAME_OVER = 3;

    Game();

    // must call this before game really starts
    void init(const int M, const int N, int firstPlayer);

    // apply a move for current player
    int applyMove(const Point& pos);
    // returns one of the following
    const static int GAME_CONTINUE = 0;
    const static int ILLEGAL_MOVE = 1;
    const static int BLACK_WIN = 2;
    const static int WHITE_WIN = 3;
    const static int IS_TIE = 4;

    // update
    void updateNotPos();

    //
    bool isLegalMove(const Point& pos);

    // getters
    int player() const;
    int boardM() const;
    int boardN() const;
    int chess(const Point& p) const;
    int chess(int x, int y) const;
    Point lastPos() const;
    Point notPos() const;

private:
    // states
    int _boardM;
    int _boardN;
    int _player; // current status
    int* _tops;
    int** _board;
    Point _lastPos;
    Point _notPos;
};

#endif // GAME_H
