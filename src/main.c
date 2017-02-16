/**
 *  \file main.c
 *  \author Simon Wietrich
 **/

#include <stdio.h>
#include <SDL2/SDL.h>
#include "board.h"

void displayBoard(Board* board, SDL_Renderer* ren) {
  for(size_t x = 0; x < 24; x++) {
    for(size_t y = 0; y < 24; y++) {
      // Init rect
      SDL_Rect rect;
      rect.x = x + 20*x;
      rect.y = y + 20*y;
      rect.w = 20;
      rect.h = 20;

      // Set render color ( rect will be rendered in this color )
      switch(getBoardCell(board, x, y)) {
        case 'R':
          SDL_SetRenderDrawColor( ren, 255, 0, 0, 255 );
          break;
        case 'G':
          SDL_SetRenderDrawColor( ren, 0, 255, 0, 255 );
          break;
        case 'B':
          SDL_SetRenderDrawColor( ren, 0, 0, 255, 255 );
          break;
        case 'Y':
          SDL_SetRenderDrawColor( ren, 255, 255, 0, 255 );
          break;
        case 'O':
          SDL_SetRenderDrawColor( ren, 0, 255, 255, 255 );
          break;
        case 'M':
          SDL_SetRenderDrawColor( ren, 255, 0, 255, 255 );
          break;
      }

      // Render rect
      SDL_RenderFillRect( ren, &rect );
    }
  }
  // Render the rect to the screen
  SDL_RenderPresent(ren);
}

void updateBoard(Board* board, size_t x, size_t y, SDL_Renderer* ren) {
  char color = getBoardCell(board, x, y);
  floodBoard(board, getBoardCell(board, 0, 0), color, 0, 0);
  displayBoard(board, ren);
}

void checkEvents(Board* board, SDL_Event mouse_event, SDL_Renderer* ren, SDL_Window* win) {
  switch(mouse_event.type) {
    case SDL_QUIT:
      SDL_DestroyRenderer(ren);
      SDL_DestroyWindow(win);
      SDL_Quit();
      exit(0);
      break;
    case SDL_MOUSEBUTTONDOWN:
      updateBoard(board, mouse_event.button.x / 21, mouse_event.button.y / 21, ren);
      break;
  }
}

/**
 * \fn
 * \return int
 **/
int main() {
    void* nullptr = NULL;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Color Flood", 100, 100, MAX_SIZE * 20, MAX_SIZE * 20, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return 1;
    }

    // Set background to white
    SDL_SetRenderDrawColor( ren, 0, 0, 0, 255 );

    // Clear window
    SDL_RenderClear( ren );

    Board* board = initRandomBoard(MAX_SIZE);
    SDL_Event mouse_event;

    displayBoard(board, ren);
    while(1) {
      SDL_WaitEvent(&mouse_event);
      checkEvents(board, mouse_event, ren, win);
    }
    return 0;
}
