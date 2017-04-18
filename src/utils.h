#ifndef _UTILS_H
#define _UTILS_H

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

TTF_Font* defaultFont;

void drawButton(char* txt, int x, int y, int w, int h, SDL_Color txtColor, SDL_Color backgroundColor, SDL_Renderer* ren);

#endif
