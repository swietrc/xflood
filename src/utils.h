#ifndef _UTILS_H
#define _UTILS_H

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 620

#define FONT_DIR "./vendor/fonts"

TTF_Font* defaultFont;
TTF_Font* buttonFont;

void drawButton(char* txt, int x, int y, int w, int h, SDL_Color txtColor, SDL_Color backgroundColor, SDL_Renderer* ren);

#endif
