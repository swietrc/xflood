#include "solver.h"
#include "board.h"

void getPossibleColorsRec(Board* b, ColorList* l, unsigned int x, unsigned int y, int cpt) {

    char currentColor = getBoardCell(b, 0, 0);
    char tileColor = getBoardCell(b, x, y);

    /*
    if ((boardColor == tileColor) || (getBoardCell(b, x, y) != oldColor))
        return;
    */

    if (tileColor != currentColor) {
        ColorListPush(l, tileColor);
        cpt++;
        return;
    }

    // Check right
    if (x < (getBoardSize(b) - 1))
        getPossibleColorsRec(b, l, x + 1, y, cpt);
    // Check down
    if (y < (getBoardSize(b) - 1))
        getPossibleColorsRec(b, l, x, y + 1, cpt);
}

ColorList* getPossibleColors(Board* b) {
	ColorList* l = ColorListCreateEmpty();
	char c = getBoardCell(b, 0, 0);
	int cpt = 0;
	getPossibleColorsRec(b, l, 0, 0, cpt);

    return l;
}

int solveBoard(Board* b, ColorList** bestSolution, ColorList* currentSolution) {
    /*
    if(currentSolution == NULL)                    // First time we call the solver
        currentSolution = ColorListCreateEmpty();
    
    if (bestSolution != NULL && ColorListSize(currentSolution) >= ColorListSize(bestSolution)) {
        return -1;
    } else if(!isBoardOneColored(b)) {
        puts("\n\n\n-------------------------zerzer\n\n\n");
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
        ColorListCopy(currentSolution, bestSolution);
        ColorListClean(currentSolution);
    }
    return ColorListSize(bestSolution);
    */
    debug_displayBoard(b);
    ColorList* nextColors;
    ColorList* solution = ColorListCreateEmpty();
    char nextColor;
    while (!isBoardOneColored(b)) {
        nextColors = getPossibleColors(b);
        ColorListForward(nextColors, &nextColor);
        printf("NextColor: %c", nextColor);
        ColorListPush(solution, nextColor);
        floodBoard(b, getBoardCell(b, 0, 0), nextColor, 0, 0);
        free(nextColors);
        debug_displayBoard(b);
    }
    ColorListPrint(solution);
    *bestSolution = solution;
    return 0;
}

