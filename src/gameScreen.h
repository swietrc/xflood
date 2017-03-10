#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include "board.h"
#include <stdint.h>
#include <stdbool.h>
#include "game.h"

#define BOARDWIDTH 504

extern void gameScreen(SDL_Event event, SDL_Renderer* ren, config* conf);

#endif
