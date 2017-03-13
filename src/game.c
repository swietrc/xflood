/**
 * \file game.c
 * Game loop/logic file
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

/**
 * \fn void checkEvents(SDL_Event event, SDL_Renderer* ren, SDL_Window* win)
 * \brief generic event handler
 * \param event SDL Event to be handled
 * \param ren SDL renderer on which to draw
 * \param win Current game window
 */
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

/**
 * \fn void runGame(SDL_Renderer* ren, SDL_Window* win)
 * \brief Game loop function
 * \param ren Current game renderer
 * \param win Current game window
 */
void runGame(SDL_Renderer* ren, SDL_Window* win) {
  SDL_Event event;

  config conf;
  conf.state = menuState;
  conf.boardSize = 24;
  conf.allowedTurns = 44;
  conf.turnsLeft = conf.allowedTurns;

  while(1) {
    // Wait for event
    SDL_WaitEvent(&event);

    // Handle event
    checkEvents(event, ren, win);

    // Clear the screen
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    switch(conf.state) {
      case menuState:
        menuScreen(event, ren, &conf);
        break;
      case gameState:
        gameScreen(event, ren, &conf);
        break;
    }
  }
}
