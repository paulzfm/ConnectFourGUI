#ifndef STRATEGY_H
#define STRATEGY_H

#include <string>

#include "point.h"

// Function pointers
typedef Point* (*GETPOINT)(const int M, const int N, const int* _top,
    const int* _board, const int lastX, const int lastY, const int notX, const int notY);
typedef void (*CLEARPOINT)(Point* p);

class Strategy
{
public:
    Strategy(std::string dylib);

    Point getDecision(const int M, const int N, const int* _top, const int* _board,
                      const int lastX, const int lastY, const int notX, const int notY);

private:
    GETPOINT getPoint;
    CLEARPOINT clearPoint;
};

#endif // STRATEGY_H
