#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include "board.h"
#include <stdint.h>
#include <stdbool.h>

#define BOARDWIDTH 504

void updateBoard(Board* board, size_t x, size_t y);
void displayGameScreen(Board* board, SDL_Renderer* ren);

#endif