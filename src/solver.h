#ifndef __SOLVER_H__
#define __SOLVER_H__

#include <stdbool.h>
#include <stddef.h>

#include "colorList.h"
#include "board.h"

ColorList* getPossibleColors(Board* b);

int solveBoard(Board* b, ColorList** bestSolution, ColorList** currentSolution);

#endif
