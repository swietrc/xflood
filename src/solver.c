#include "solver.h"
#include "board.h"


ColorList* getPossibleColors(Board* b) {
	ColorList l = ColorListCreateEmpty();
	char c = getBoardCell(b, 0, 0);
	int cpt = 0;
	void getPossibleColorsRec(Board* b, ColorList* l, char Color, unsigned int x, unsigned int y, int cpt) {
		if ((oldColor == newColor) || (getBoardCell(b, x, y) != oldColor))
        		return;
		if (cpt == 6)
			return;
		if (getBoardCell(b, x, y) != c) {
			ColorListPush(l, c);
			cpt++;
		}
		// Check left
		if (x > 0)
			getPossibleColorsRec(b, l, c, x - 1, y, cpt);
		// Check right
		if (x < (b->size - 1))
			getPossibleColorsRec(b, l, c, x + 1, y, cpt);
		// Check up
		if (y > 0)
			getPossibleColorsRec(b, l, c, x, y - 1, cpt);
		// Check down
		if (y < (b->size - 1))
			getPossibleColorsRec(b, l, c, x, y + 1, cpt);
	}
	getPossibleColorsRec(b, l, c, 0, 0, cpt);
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

