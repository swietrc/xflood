/**
 *  \file main.c
 *  \author Simon Wietrich
 **/

#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameScreen.h"
#include "board.h"

void checkEvents(Board* board, SDL_Event mouse_event, SDL_Renderer* ren, SDL_Window* win) {
  switch(mouse_event.type) {
    case SDL_QUIT:
      SDL_DestroyRenderer(ren);
      SDL_DestroyWindow(win);
      SDL_Quit();
      exit(0);
      break;
    case SDL_MOUSEBUTTONDOWN:
      updateBoard(board, mouse_event.button.x, mouse_event.button.y);
      displayGameScreen(board, ren);
      if(isBoardOneColored(board)) {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(0);
      }
      break;
  }
}

/**
 * \fn
 * \return int
 **/
int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Color Flood", 100, 100, 1000, 620, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return 1;
    }

    // Set background to black
    SDL_SetRenderDrawColor( ren, 0, 0, 0, 255 );

    // Clear window
    // SDL_RenderClear( ren );

    Board* board = initRandomBoard(MAX_SIZE);
    SDL_Event mouse_event;

    displayGameScreen(board, ren);
    while(1) {
      SDL_WaitEvent(&mouse_event);
      checkEvents(board, mouse_event, ren, win);
    }
    return 0;
}
