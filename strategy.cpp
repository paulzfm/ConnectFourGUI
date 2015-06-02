#include "strategy.h"
#include <stdio.h>
#include <dlfcn.h>

Strategy::Strategy(std::string dylib)
{
    hDylib = dlopen(dylib.c_str(), RTLD_LOCAL | RTLD_NOW);

    if (!hDylib) {
        fprintf(stderr, "***Error: cannot find library \"%s\".\n", dylib.c_str());
    }

    // obtain function pointers
    getPoint = (GETPOINT)dlsym(hDylib, "getPoint");
    clearPoint = (CLEARPOINT)dlsym(hDylib, "clearPoint");

    if (getPoint == NULL || clearPoint == NULL) {
        fprintf(stderr, "***Error: cannot load function.\n");
    }
}

Strategy::~Strategy()
{
    if (hDylib) {
        dlclose(hDylib);
    }
}

Point Strategy::getDecision(const int M, const int N, const int *_top, const int *_board,
                            const int lastX, const int lastY, const int notX, const int notY)
{
    Point *p = getPoint(M, N, _top, _board, lastX, lastY, notX, notY);
    Point decision(p->x, p->y);
    if (p) {
        clearPoint(p);
    }
    return decision;
}
