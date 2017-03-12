#ifndef _CONFIG_H
#define _CONFIG_H

typedef enum screenState { menuState, gameState } screenState;

typedef struct config {
  screenState state;
  size_t boardSize;
  int allowedTurns;
  int turnsLeft;
  Board* board;
} config;

#endif
