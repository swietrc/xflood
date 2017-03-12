#ifndef _GAME_H
#define _GAME_H

#include "board.h"

typedef enum screenState { menuState, gameState } screenState;

typedef struct config {
  screenState state;
  size_t boardSize;
  int allowedTurns;
  int turnsLeft;
  Board* board;
} config;

void runGame(SDL_Renderer* ren, SDL_Window* win);
void checkEvents(SDL_Event event, SDL_Renderer* ren, SDL_Window* win);

#endif
