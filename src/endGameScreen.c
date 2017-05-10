/**
 * \file endGameScreen.c
 * File displaying the end game window.
 * \author Simon Wietrich
 * \author Pierre Genthon
 * \author Celestin Caumes
 * \author Camille Schnell
 **/

#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "board.h"
#include "endGameScreen.h"
#include "game.h"
#include "utils.h"

static int needsRefresh = 1;

/**
 * \fn void handleBoardClicks(size_t x, size_t y, config* conf)
 * \brief Updates the board with the color chosen by the user (color of the cell he clicked)
 * \param x X coordinate of the cell chosen by the user
 * \param y Y coordinate of the cell chosen by the user
 * \param conf Config struct containing board, boardSize and states
 */
static void handleBoardClicks(size_t x, size_t y, config* conf) {
  // click on back-to-menu button
  if(x >= 609 && x <=  909 && y >= 500 && y <= 580){
    freeBoard(conf->board); // free Board at end of game
    conf->state = menuState;
  }

  // click on solution button
  if(x >= 609 && x <=  909 && y >= 100 && y <= 180) {
    if(conf->boardSize <= 10) {
      conf->solvingBoard = copyBoard(conf->staticBoard); // reset board
      ColorListReset(conf->bestSol); // reset best solution list
    }
    conf->state = solverState;
  }
}


/**
 * \fn void displayEndGameScreen(SDL_Renderer* ren, config* conf)
 * \brief Displays a screen after winning/losing the game
 * \param ren SDL_Renderer object used to display the board
 * \param conf Config struct containing board, boardSize and states
 */
static void displayEndGameScreen(SDL_Renderer* ren, config* conf) {
  // Set background to black
  SDL_SetRenderDrawColor( ren, 0xFF, 0xFF, 0xFF, 255 );
  SDL_RenderClear(ren);

  // display solution button
  SDL_Color btnTxtColor = {0xF2, 0xF2, 0xF2, 255};
  SDL_Color btnBgColor = {0x42, 0x72, 0x3D, 0x22};
  drawButton(" Solution ", BOARDWIDTH + 105, 100, 300, 80, btnTxtColor, btnBgColor, ren);

  // back to menu button
  drawButton(" Retour au menu ", BOARDWIDTH + 105, 500, 300, 80, btnTxtColor, btnBgColor, ren);

  Board* b = initRandomBoard(conf->boardSize);
  for(size_t x = 0; x < conf->boardSize; x++) {
    for(size_t y = 0; y < conf->boardSize; y++) {
      // Init rect
      SDL_Rect rect;
      rect.x = x + (BOARDWIDTH / conf->boardSize)*x;
      rect.y = y + (BOARDWIDTH / conf->boardSize)*y;
      rect.w = (BOARDWIDTH / conf->boardSize);
      rect.h = (BOARDWIDTH / conf->boardSize);

      // Set render color ( rect will be rendered in this color )
      switch(getBoardCell(b, x, y)) {
        case 'R':
          SDL_SetRenderDrawColor( ren, 0xFF, 0x5D, 0x5D, 0xFF );
          break;
        case 'G':
          SDL_SetRenderDrawColor( ren, 0x4F, 0xE8, 0x58, 0xFF );
          break;
        case 'B':
          SDL_SetRenderDrawColor( ren, 0x29, 0x71, 0xc4, 0xFF );
          break;
        case 'Y':
          SDL_SetRenderDrawColor( ren, 0xFF, 0xC2, 0x49, 0xFF );
          break;
        case 'O':
          SDL_SetRenderDrawColor( ren, 0x62, 0xC4, 0xC9, 0xFF );
          break;
        case 'M':
          SDL_SetRenderDrawColor( ren, 0xBE, 0x7A, 0xFF, 0xFF );
          break;
      }

      // Render rect
      SDL_RenderFillRect( ren, &rect );
      //sleep(0.75);
      //SDL_RenderPresent(ren);
    }
  }

  // victory/defeat button
  switch(conf->state) {
    case victoryState:
      drawButton(" VICTOIRE ! ", 100, 200, 300, 80, btnTxtColor, btnBgColor, ren);
      break;
    case defeatState:
      drawButton(" DEFAITE... ", 100, 200, 300, 80, btnTxtColor, btnBgColor, ren);
      break;
    default:
      break;
  }
}

/**
 * \fn void endGameScreenCheckEvents(SDL_Event event, config* conf)
 * \brief Function checking for events and treating them
 * \param event SDL_Event object used to check and treat the current event
 * \param conf Config struct containing board, boardSize and states
 */
static void endGameScreenCheckEvents(SDL_Event event, config* conf) {
  needsRefresh = 1;
  switch(event.type) {
    case SDL_MOUSEBUTTONDOWN:
      handleBoardClicks(event.button.x, event.button.y, conf);
      break;
    default:
      needsRefresh = 0;
  }
}

/**
 * \fn void endGameScreen(SDL_Event event, SDL_Renderer* ren, config* conf)
 * \brief Main function of endGameScreen, checking for events and displaying the endGameScreen
 * \param event SDL_Event object used to check and treat the current event
 * \param ren SDL_Renderer object used to display the board
 * \param conf Config struct containing board, boardSize and states
 */
extern void endGameScreen(SDL_Event event, SDL_Renderer* ren, config* conf) {
  if(needsRefresh){
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    displayEndGameScreen(ren, conf);
    SDL_RenderPresent(ren);
  }

  endGameScreenCheckEvents(event, conf);
}
