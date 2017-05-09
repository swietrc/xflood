/**
 * \file solverScreen.c
 * File displaying the solver window.
 * \author Simon Wietrich
 * \author Pierre Genthon
 * \author Celestin Caumes
 * \author Camille Schnell
 **/

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "board.h"
#include "solverScreen.h"
#include "colorList.h"
#include "game.h"
#include "utils.h"

static int needsRefresh = 1;

/**
 * \fn void solveNextMove(config* conf)
 * \brief Updates solvingBoard with the next color present in the bestSolution ColorList
 * \param conf Config struct containing board, boardSize and states
 */
static void solveNextMove(config* conf) {
  char color;
  if(ColorListForward(conf->bestSol, &color)) {
    floodBoard(conf->solvingBoard, getBoardCell(conf->solvingBoard, 0, 0), color, 0, 0);
  }
}


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
    conf->state = menuState;
  }

  // click on back-to-game button
  if(x >= 609 && x <=  909 && y >= 100 && y <= 180) {
    conf->state = gameState;
  }

  // click on next move button
  if(x >= 609 && x <=  909 && y >= 300 && y <= 380) {
    solveNextMove(conf);
  }
}

/**
 * \fn void displaySolverScreen(SDL_Renderer* ren, config* conf)
 * \brief Displays the board to solve in the window
 * \param ren SDL_Renderer object used to display the board
 * \param conf Config struct containing board, boardSize and states
 */
static void displaySolverScreen(SDL_Renderer* ren, config* conf) {
  // Set background to black
  SDL_SetRenderDrawColor( ren, 0xFF, 0xFF, 0xFF, 255 );
  SDL_RenderClear(ren);

  for(size_t x = 0; x < getBoardSize(conf->solvingBoard); x++) {
    for(size_t y = 0; y < getBoardSize(conf->solvingBoard); y++) {
      // Init rect
      SDL_Rect rect;
      rect.x = x + (BOARDWIDTH / getBoardSize(conf->solvingBoard))*x;
      rect.y = y + (BOARDWIDTH / getBoardSize(conf->solvingBoard))*y;
      rect.w = (BOARDWIDTH / getBoardSize(conf->solvingBoard));
      rect.h = (BOARDWIDTH / getBoardSize(conf->solvingBoard));

      // Set render color ( rect will be rendered in this color )
      switch(getBoardCell(conf->solvingBoard, x, y)) {
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
    }
  }

  // back to game button
  SDL_Color btnTxtColor = {0xF2, 0xF2, 0xF2, 255};
  SDL_Color btnBgColor = {0x42, 0x72, 0x3D, 255};
  drawButton(" Retour au jeu ", BOARDWIDTH + 105, 100, 300, 80, btnTxtColor, btnBgColor, ren);

  // next move button
  drawButton(" Coup suivant ", BOARDWIDTH + 105, 300, 300, 80, btnTxtColor, btnBgColor, ren);

  // back to menu button
  drawButton(" Retour au menu ", BOARDWIDTH + 105, 500, 300, 80, btnTxtColor, btnBgColor, ren);
}

/**
 * \fn void solverScreenCheckEvents(SDL_Event event, config* conf)
 * \brief Function checking for events and treating them
 * \param event SDL_Event object used to check and treat the current event
 * \param conf Config struct containing board, boardSize and states
 */
static void solverScreenCheckEvents(SDL_Event event, config* conf) {
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
 * \fn void solutionTooLongSorry(SDL_Renderer* ren, SDL_Event event, config* conf)
 * \brief When boardSize > 10, the solver isn't able to solve it. This function displays a message to inform the player
 * \param ren SDL_Renderer object used to display the screen
 * \param event SDL_Event object used to check and treat the current event
 * \param conf Config struct containing board, boardSize and states
 */
static void solutionTooLongSorry(SDL_Renderer* ren, SDL_Event event, config* conf) {
  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
  SDL_RenderClear(ren);
  // back to game button
  SDL_Color btnTxtColor = {0xF2, 0xF2, 0xF2, 255};
  SDL_Color btnBgColor = {0x42, 0x72, 0x3D, 255};
  drawButton(" Solution impossible en moins de 1000 ans... ", 105, 250, 800, 80, btnTxtColor, btnBgColor, ren);
  drawButton(" Retour au jeu ", BOARDWIDTH + 105, 100, 300, 80, btnTxtColor, btnBgColor, ren);
  drawButton(" Retour au menu ", BOARDWIDTH + 105, 500, 300, 80, btnTxtColor, btnBgColor, ren);
  switch(event.type) {
    case SDL_MOUSEBUTTONDOWN:
    // click on back-to-menu button
    if(event.button.x >= 609 && event.button.x <=  909 && event.button.y >= 500 && event.button.y <= 580){
      conf->state = menuState;
    }

    // click on back-to-game button
    if(event.button.x >= 609 && event.button.x <=  909 && event.button.y >= 100 && event.button.y <= 180) {
      conf->state = gameState;
    }
      break;
  }
  SDL_RenderPresent(ren);
}

/**
 * \fn void solverScreen(SDL_Event event, SDL_Renderer* ren, config* conf)
 * \brief Main function of solverScreen, checking for events and displaying the solverScreen
 * \param event SDL_Event object used to check and treat the current event
 * \param ren SDL_Renderer object used to display the board
 * \param conf Config struct containing board, boardSize and states
 */
extern void solverScreen(SDL_Event event, SDL_Renderer* ren, config* conf) {
  if(conf->boardSize < 10) {
    if(needsRefresh){
      SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
      SDL_RenderClear(ren);
      displaySolverScreen(ren, conf);
      SDL_RenderPresent(ren);
    }
    solverScreenCheckEvents(event, conf);
  }
  else
    solutionTooLongSorry(ren, event, conf);
}
