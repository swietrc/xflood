#ifndef _GAME_H
#define _GAME_H

#include "board.h"
#include "config.h"

void runGame(SDL_Renderer* ren, SDL_Window* win, config* conf);
void checkEvents(SDL_Event event, SDL_Renderer* ren, SDL_Window* win);

#endif
