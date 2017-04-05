#include "solver.h"
#include "board.h"


ColorList* getPossibleColors(Board* b) {
    ColorList* l = ColorListCreate();
    
    
}




int solveBoard(Board* b, ColorList* bestSolution, ColorList* currentSolution) {
    if(currentSolution == NULL)                    // First time we call the solver
        currentSolution = ColorListCreateEmpty();
    
    if (bestSolution != NULL && ColorListSize(currentSolution) >= ColorListSize(bestSolution)) {
        return -1;
    } else if(!isBoardOneColored(b)) {
        char currentColor;
        Board* b2;
        ColorList* possibleColors = getPossibleColors(b);
    
        while (ColorListForward(possibleColors, &currentColor)) {
            b2 = copyBoard(b);
            ColorListPush(currentSolution, currentColor);
            floodBoard(b2, getBoardCell(b2, 0, 0), currentColor, 0, 0);
            solveBoard(b2, bestSolution, currentSolution);
            freeBoard(b2);
        }
        ColorListDestroy(possibleColors);
    } else {
        ColorlistCopy(currentSolution, bestSolution);
        ColorListClean(currentSolution);
    }
    return ColorListSize(bestSolution);
}

