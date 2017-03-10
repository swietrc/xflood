/**
 * \file game.c
 * File processing game
 * \author Simon Wietrich
 * \author Pierre Genthon
 * \author Celestin Caumes
 * \author Camille Schnell
 **/


#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameScreen.h"
#include "menuScreen.h"
#include "board.h"
#include "game.h"

void checkEvents(SDL_Event event, SDL_Renderer* ren, SDL_Window* win) {
  switch(event.type) {
    case SDL_QUIT:
      //freeBoard(board);
      SDL_DestroyRenderer(ren);
      SDL_DestroyWindow(win);
      SDL_Quit();
      exit(0);
      break;
  }
}

void runGame(SDL_Renderer* ren, SDL_Window* win) {
  SDL_Event event;

  config conf;
  conf.state = menuState;
  conf.boardSize = 24;
  conf.allowedTurns = 44;
  conf.turnsLeft = conf.allowedTurns;

  while(1) {
    SDL_WaitEvent(&event);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    checkEvents(event, ren, win);
    switch(conf.state) {
      case menuState:
        menuScreen(event, ren, &conf);
        break;
      case gameState:
        gameScreen(event, ren, &conf);
        break;
    }
    SDL_RenderPresent(ren); // Render the board to the screen
  }
}
