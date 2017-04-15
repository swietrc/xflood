#include "solver.h"
#include "board.h"

#define MAX_ITER 6

/**
 * \fn void getPossibleColorsRed(Board* b, ColorList* l, bool*
 * visitedTiles, unsigned int x, unsigned int y, int* cpt)
 * \brief Recursively looks for all adjacent color tiles
 * \param b The board
 * \param l The list storing all adjacent colors
 * \param visitedTiles bool array keeping track of already visited tiles.
 * \param x The X position of the current tile
 * \param y The Y position of the current tile
 * \param cpt Counter keeping track of the number of adjacent tiles.
 */
void getPossibleColorsRec(Board* b, ColorList* l, bool* visitedTiles, unsigned int x, unsigned int y, int* cpt) {
    if(*cpt > MAX_ITER)
        return;
    visitedTiles[x+(y*getBoardSize(b))] = true;
    
    char currentColor = getBoardCell(b, 0, 0);
    char tileColor = getBoardCell(b, x, y);

    if (tileColor != currentColor) {
        ColorListPush(l, tileColor);
        (*cpt)++;
        return;
    }
    // Check left
    if (x > 0 && !(visitedTiles[(x-1)+(y*getBoardSize(b))]))
        getPossibleColorsRec(b, l, visitedTiles, x - 1, y, cpt);

    // Check right
    if (x < (getBoardSize(b) - 1) && !(visitedTiles[(x+1)+(y*getBoardSize(b))]))
        getPossibleColorsRec(b, l, visitedTiles, x + 1, y, cpt);

    // Check down
    if (y < (getBoardSize(b) - 1) && !(visitedTiles[x+((y+1)*getBoardSize(b))]))
        getPossibleColorsRec(b, l, visitedTiles, x, y + 1, cpt);

    // Check up
    if (y > 0 && !(visitedTiles[x+((y-1)*getBoardSize(b))]))
        getPossibleColorsRec(b, l, visitedTiles, x, y - 1, cpt);
}

/**
 * \fn ColorList* getPossibleColors(Board* b)
 * \brief Gets all useful color changes on Board b
 * \param b The board to check
 * \return ColorList* containing all possible color changes.
 */
ColorList* getPossibleColors(Board* b) {
    bool* visitedTiles = malloc(sizeof(bool) * getBoardSize(b) * getBoardSize(b));

	ColorList* l = ColorListCreateEmpty();
	char c = getBoardCell(b, 0, 0);
	int cpt = 0;
    int* cpt_ptr = &cpt;
	getPossibleColorsRec(b, l, visitedTiles, 0, 0, cpt_ptr);

    free(visitedTiles);

    return l;
}

/**
 * \fn int solveBoard(Board* b, ColorList** bestSolution, ColorList** currentSolution)
 * \brief Recursively finds optimal solution for b
 * \param b The board to check
 * \param bestSolution the current best possible solution
 * \param currentSolution the current solution
 * \return size of solution
 */
int solveBoard(Board* b, ColorList** bestSolution, ColorList** currentSolution) {
    
    if(*currentSolution == NULL) {                   // First time we call the solver
        *currentSolution = ColorListCreateEmpty();
    }
    
    if (*bestSolution != NULL && ColorListSize(*currentSolution) >= ColorListSize(*bestSolution)) {
        return -1;
    } else if(!isBoardOneColored(b)) {
        char currentColor;
        Board* b2;
        ColorList* possibleColors = getPossibleColors(b);
        
        while (ColorListForward(possibleColors, &currentColor)) {
            b2 = copyBoard(b);
            ColorListPush(*currentSolution, currentColor);
            floodBoard(b2, getBoardCell(b2, 0, 0), currentColor, 0, 0);
            ColorList* copy = ColorListCreateEmpty();
            ColorListCopy(*currentSolution, copy);
            solveBoard(b2, bestSolution, &copy);
            freeBoard(b2);
        }
        ColorListDestroy(possibleColors);
    } else {
        ColorList* copy = ColorListCreateEmpty();
        ColorListCopy(*currentSolution, copy);
        *bestSolution = copy;

        ColorListClean(*currentSolution);
        ColorListPrint(*bestSolution);
    }
    return ColorListSize(*bestSolution);
}

int solveBoardThatEnds(Board* b, ColorList** bestSolution) {
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
    return ColorListSize(solution);
}

