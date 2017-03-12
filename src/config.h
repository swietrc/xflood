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

typedef enum screenState { menuState, gameState } screenState;

typedef struct config {
  screenState state; //!< Enum representing the state of the game
  size_t boardSize;  //!< ???
  int allowedTurns;  //!< Number of turns allowed for the current game
  int turnsLeft;     //!< Number of turns left for the current game
  Board* board;      //!< Data about the board of the current game
} config;

#endif
