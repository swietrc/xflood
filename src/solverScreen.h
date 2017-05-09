#ifndef _SOLVERSCREEN_H
#define _SOLVERSCREEN_H

#include <stdint.h>
#include <stdbool.h>

#include "config.h"

#define BOARDWIDTH 504

extern void solverScreen(SDL_Event event, SDL_Renderer* ren, config* conf);

#endif
