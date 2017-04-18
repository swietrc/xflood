/**
 *  \file main.c
 *  \author Camille Schnell
 *  \author Simon Wietrich
 *  \author Pierre Genthon
 *  \author Celestin Caumes
 **/

#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "game.h"
#include "utils.h"
#include "config.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 620

/**
 * \fn int main()
 * \brief Initializes window and calls the function to run the game
 * \return int
 **/
int main(int argc, char** argv) {
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Color Flood", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() != 0) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        return 1;
    }

    // Initialize default font
    defaultFont = TTF_OpenFont("vendor/fonts/Roboto-Regular.ttf", 72); // open a font style and set a size

    // Set background to black
    SDL_SetRenderDrawColor( ren, 0, 0, 0, 255 );

    // game configuration init
    config conf;
    conf.state = menuState;
    conf.boardSize = 24;
    conf.allowedTurns = 44;

    if(argc > 1){
        conf.boardSize = atoi(argv[1]);
        if(argc > 2) conf.allowedTurns = atoi(argv[2]);
    }

    conf.turnsLeft = conf.allowedTurns;
    runGame(ren, win, &conf);

    return 0;
}
