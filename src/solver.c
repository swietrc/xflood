/**
 * \file solver.c
 * Contains all solver related functions
 * \author Simon Wietrich
 * \author Pierre Genthon
 * \author Celestin Caumes
 * \author Camille Schnell
 **/

#include <stdlib.h>
#include <stdio.h>
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

/**
 * \fn void getColoredAreaSize(Board* b, bool* visitedTiles, size_t x, size_t y, size_t* size)
 * \brief Recursively finds top-left colored area size
 * \param b The board to check
 * \param visitedTiles array keeping track of visited tiles
 * \param x the X position to check
 * \param y the Y position to check
 * \param size the size of the top-left area
 */
void getColoredAreaSize(Board* b, bool* visitedTiles, size_t x, size_t y, size_t* size) {

  if (getBoardCell(b, x, y) != getBoardCell(b, 0, 0)) {
      return;
  }

  visitedTiles[x+(y*getBoardSize(b))] = true;
  *size = *size + 1;

  // Check left
  if (x > 0 && !(visitedTiles[(x-1)+(y*getBoardSize(b))]))
    getColoredAreaSize(b, visitedTiles, x - 1, y, size);

  // Check right
  if (x < (getBoardSize(b) - 1) && !(visitedTiles[(x+1)+(y*getBoardSize(b))]))
    getColoredAreaSize(b, visitedTiles, x + 1, y, size);

  // Check down
  if (y < (getBoardSize(b) - 1) && !(visitedTiles[x+((y+1)*getBoardSize(b))]))
    getColoredAreaSize(b, visitedTiles, x, y + 1, size);

  // Check up
  if (y > 0 && !(visitedTiles[x+((y-1)*getBoardSize(b))]))
    getColoredAreaSize(b, visitedTiles, x, y - 1, size);
}

/**
 * \fn int solveBoardEfficient(Board* b, ColorList* solution)
 * \brief Recursively finds top-left colored area size
 * \param b The board to check
 * \param solution the solution found by the algorithm
 * \return size of the solution
 */
int solveBoardEfficient(Board* b, ColorList* solution) {
  bool* visitedTiles;
  ColorList* possibleColors = NULL;

  char currentColor;
  char bestColor;
  size_t areaSize = 0;
  size_t bestAreaSize = 0;

  Board* solvedBoard = copyBoard(b); // Copy of the board to test the solution
  Board* testerBoard; // copy of board used to find next best color

  while (!isBoardOneColored(solvedBoard)) {
    possibleColors = getPossibleColors(solvedBoard); // Get all possible colors for next turn.
    visitedTiles = calloc(getBoardSize(b) * getBoardSize(b), sizeof(bool)); // Keep track of visited tiles

    while (ColorListForward(possibleColors, &currentColor)) { // Test all possible colors to get the one that will get us the farthest.
      areaSize = 0;
      testerBoard = copyBoard(solvedBoard);
      floodBoard(testerBoard, getBoardCell(testerBoard, 0, 0), currentColor , 0, 0);
      getColoredAreaSize(testerBoard, visitedTiles, 0, 0, &areaSize);

      if (areaSize > bestAreaSize) {
        bestAreaSize = areaSize;
        bestColor = currentColor;
      }

      freeBoard(testerBoard);
    }
    ColorListPush(solution, bestColor);
    floodBoard(solvedBoard, getBoardCell(solvedBoard, 0, 0), bestColor, 0, 0);

    free(visitedTiles);
    ColorListDestroy(possibleColors);
  }

  freeBoard(solvedBoard);

  return ColorListSize(solution);
}
