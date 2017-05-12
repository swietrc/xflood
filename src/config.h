/**
 * \file config.h
 * Contains the game configuration data structure
 * \author Simon Wietrich
 * \author Pierre Genthon
 * \author Celestin Caumes
 * \author Camille Schnell
 **/

#ifndef _CONFIG_H
#define _CONFIG_H

#include "colorList.h"

#define MAX_SIZE_SOLVER 8
#define BOARDWIDTH 504

typedef enum screenState { menuState, gameState, solverState, defeatState, victoryState } screenState;

typedef struct config {
  screenState state; //!< Enum representing the state of the game
  size_t boardSize;  //!< ???
  int allowedTurns;  //!< Number of turns allowed for the current game
  int turnsLeft;     //!< Number of turns left for the current game
  Board* board;      //!< Data about the board of the current game
  ColorList* bestSol; //!< Best solution to solve the current board
  Board* solvingBoard; //!< Data about the board being solved
  Board* staticBoard; //!< Board initialized as a copy of board, but will never be modified
} config;

#endif
