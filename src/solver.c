/**
 * \file solver.c
 * Contains all solver related functions
 * \author Simon Wietrich
 * \author Pierre Genthon
 * \author Celestin Caumes
 * \author Camille Schnell
 **/

#include <stdlib.h>
#include "solver.h"
#include "board.h"
#include "colorList.h"

/**
 * \fn void getPossibleColorsRec(Board* b, ColorList* l, bool* visitedTiles, unsigned int x, unsigned int y)
 * \brief Recursively looks for all adjacent color tiles
 * \param b The board
 * \param l The list storing all adjacent colors
 * \param visitedTiles bool array keeping track of already visited tiles.
 * \param x The X position of the current tile
 * \param y The Y position of the current tile
 */
void getPossibleColorsRec(Board* b, ColorList* l, bool* visitedTiles, unsigned int x, unsigned int y) {
  visitedTiles[x+(y*getBoardSize(b))] = true;

  char currentColor = getBoardCell(b, 0, 0);
  char tileColor = getBoardCell(b, x, y);

  if (tileColor != currentColor) {
    if(!ColorListIsIn(l, tileColor))
      ColorListPush(l, tileColor);

    return;
  }
  // Check left
  if (x > 0 && !(visitedTiles[(x-1)+(y*getBoardSize(b))]))
    getPossibleColorsRec(b, l, visitedTiles, x - 1, y);

  // Check right
  if (x < (getBoardSize(b) - 1) && !(visitedTiles[(x+1)+(y*getBoardSize(b))]))
    getPossibleColorsRec(b, l, visitedTiles, x + 1, y);

  // Check down
  if (y < (getBoardSize(b) - 1) && !(visitedTiles[x+((y+1)*getBoardSize(b))]))
    getPossibleColorsRec(b, l, visitedTiles, x, y + 1);

  // Check up
  if (y > 0 && !(visitedTiles[x+((y-1)*getBoardSize(b))]))
    getPossibleColorsRec(b, l, visitedTiles, x, y - 1);
}

/**
 * \fn ColorList* getPossibleColors(Board* b)
 * \brief Gets all useful color changes on Board b
 * \param b The board to check
 * \return ColorList* containing all possible color changes.
 */
ColorList* getPossibleColors(Board* b) {
  bool* visitedTiles = calloc(getBoardSize(b) * getBoardSize(b), sizeof(bool));
  ColorList* l = ColorListCreateEmpty();
  getPossibleColorsRec(b, l, visitedTiles, 0, 0);
  free(visitedTiles);

  return l;
}

/**
 * \fn int solveBoard(Board* b, ColorList* bestSolution, ColorList* currentSolution)
 * \brief Recursively finds optimal solution for b
 * \param b The board to check
 * \param bestSolution the current best possible solution
 * \param currentSolution the current solution
 * \return size of the best solution
 */
int solveBoard(Board* b, ColorList* bestSolution, ColorList* currentSolution) {
  //If the size of the solution currently being explored is greater than the size of the best solution yet,
  //we stop searching a solution in this 'branch'.
  //Obviously we need to have a best solution yet for the comparison to be valid
  size_t bestSolutionSize = ColorListSize(bestSolution);
  if (bestSolutionSize != 0 && ColorListSize(currentSolution) >= bestSolutionSize){
    ColorListClean(currentSolution);
    return -1 ;
  }
  else {
    if(!isBoardOneColored(b)) { // game's not over, we continue exploring
      ColorList* possibleColors = getPossibleColors(b);
      char currentColor;
      Board* b2;
      ColorList* copy = ColorListCreateEmpty();
      // for each color that will get us closer to a solution
      while(ColorListForward(possibleColors, &currentColor)) {
        b2 = copyBoard(b);
        ColorListPush(currentSolution, currentColor);
        floodBoard(b2, getBoardCell(b2, 0, 0), currentColor , 0, 0);
        ColorListCopy(currentSolution, copy);
        solveBoard(b2, bestSolution, copy);
        freeBoard(b2);
      }
      ColorListDestroy(copy);
      ColorListDestroy(possibleColors);
    }
    else { // if the game's over and the current solution is smaller in size compared to the best solution
      // we can free the old best solution and set the latter with the current solution's values
      ColorListCopy(currentSolution, bestSolution);
      // we have to reset the current solution, otherwise we might add some colors to it when exploring a new branch
      ColorListClean(currentSolution);
    }
    return ColorListSize(bestSolution);
  }
}
