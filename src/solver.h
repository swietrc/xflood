#ifndef __SOLVER_H__
#define __SOLVER_H__

#include "colorList.h"
#include "board.h"

ColorList* getPossibleColors(Board* b);
void getColoredAreaSize(Board* b, bool* visitedTiles, size_t x, size_t y, size_t* size);
int solveBoard(Board* b, ColorList* bestSolution, ColorList* currentSolution);
int solveBoardEfficient(Board* b, ColorList* solution);

#endif
