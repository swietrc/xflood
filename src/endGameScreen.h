#ifndef _ENDGAMESCREEN_H
#define _ENDGAMESCREEN_H

#include <stdint.h>
#include <stdbool.h>

#include "config.h"

#define BOARDWIDTH 504

extern void endGameScreen(SDL_Event event, SDL_Renderer* ren, config* conf);

#endif
