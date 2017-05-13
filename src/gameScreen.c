/**
 * \file gameScreen.c
 * File displaying the game window.
 * \author Simon Wietrich
 * \author Pierre Genthon
 * \author Celestin Caumes
 * \author Camille Schnell
 **/

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "board.h"
#include "gameScreen.h"
#include "game.h"
#include "utils.h"
#include "solver.h"

static int needsRefresh = 1;

/**
 * \fn void displayGameScreen(SDL_Renderer* ren, config* conf)
 * \brief Displays the board in the game window
 * \param ren SDL_Renderer object used to display the board
 * \param conf Config struct containing board, boardSize and states
 */
static void displayGameScreen(SDL_Renderer* ren, config* conf) {
  // Set background to black
  SDL_SetRenderDrawColor( ren, 0xFF, 0xFF, 0xFF, 255 );
  SDL_RenderClear(ren);

  // Init rect
  SDL_Rect rect;

  for(size_t x = 0; x < conf->boardSize; x++) {
    for(size_t y = 0; y < conf->boardSize; y++) {
      rect.x = x + (BOARDWIDTH / conf->boardSize)*x;
      rect.y = y + (BOARDWIDTH / conf->boardSize)*y;
      rect.w = (BOARDWIDTH / conf->boardSize);
      rect.h = (BOARDWIDTH / conf->boardSize);

      // Set render color ( rect will be rendered in this color )
      switch(getBoardCell(conf->board, x, y)) {
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

  // Creation of 6 buttons (one per color)
  for(int i = 0; i < 6; i ++) {
    int width = BOARDWIDTH / 6;
    rect.x = width*i + ((conf->boardSize - 1) / 6 ) * i + i;
    rect.y = BOARDWIDTH + 25;
    rect.w = width + (conf->boardSize - 1) / 6;
    rect.h = width + (conf->boardSize - 1) / 6;

    // Set render color ( rect will be rendered in this color )
    switch(i) {
      case 0:
        SDL_SetRenderDrawColor( ren, 0xFF, 0x5D, 0x5D, 0xFF );
        break;
      case 1:
        SDL_SetRenderDrawColor( ren, 0x4F, 0xE8, 0x58, 0xFF );
        break;
      case 2:
        SDL_SetRenderDrawColor( ren, 0x29, 0x71, 0xc4, 0xFF );
        break;
      case 3:
        SDL_SetRenderDrawColor( ren, 0xFF, 0xC2, 0x49, 0xFF );
        break;
      case 4:
        SDL_SetRenderDrawColor( ren, 0x62, 0xC4, 0xC9, 0xFF );
        break;
      case 5:
        SDL_SetRenderDrawColor( ren, 0xBE, 0x7A, 0xFF, 0xFF );
        break;
    }


    // Render board
    SDL_RenderFillRect( ren, &rect );

  }
  /** Writing label for size of board and turns left**/
  // SDL_Color messageColor = {0, 0, 255, 255};
  SDL_Color messageColor = {0x42, 0x72, 0x3D, 255};

  char turnsLeft[50];
  // sprintf(turnsLeft, "Coups restants : %d/%d", conf->turnsLeft, conf->allowedTurns);
  sprintf(turnsLeft, "%d coup(s) restant(s)", conf->turnsLeft);

  SDL_Surface* surfaceMessage = TTF_RenderText_Blended(defaultFont, turnsLeft, messageColor);
  SDL_Texture* Message = SDL_CreateTextureFromSurface(ren, surfaceMessage);

  SDL_Rect Message_rect; //create a rect
  Message_rect.x = BOARDWIDTH + 110;  //controls the rect's x coordinate
  Message_rect.y = 20; // controls the rect's y coordinte
  Message_rect.w = surfaceMessage->w; // controls the width of the rect
  Message_rect.h = surfaceMessage->h; // controls the height of the rect

  SDL_RenderCopy(ren, Message, NULL, &Message_rect);

  // display solution button
  SDL_Color btnTxtColor = {0xF2, 0xF2, 0xF2, 255};
  SDL_Color btnBgColor = {0x42, 0x72, 0x3D, 255};
  drawButton(" Solution ", BOARDWIDTH + 105, 100, 300, 80, btnTxtColor, btnBgColor, ren);

  // back to menu button
  drawButton(" Retour au menu ", BOARDWIDTH + 105, 500, 300, 80, btnTxtColor, btnBgColor, ren);

  // light bulb image
  SDL_Surface* lb = SDL_LoadBMP("resources/img/light_bulb.bmp");
  SDL_Texture* img = SDL_CreateTextureFromSurface(ren, lb);
  rect.x = BOARDWIDTH + 420;
  rect.y = 15;
  rect.w = lb->w;
  rect.h = lb->h;
  SDL_RenderCopy(ren, img, NULL, &rect);

  // Free surface and texture
  SDL_FreeSurface(surfaceMessage);
  SDL_FreeSurface(lb);
  SDL_DestroyTexture(Message);
  SDL_DestroyTexture(img);
}

/**
 * \fn void displayNextBestMove(SDL_Renderer* ren, config* conf)
 * \brief Displays the next best color to play on the game screen
 * \param ren SDL_Renderer object used to display the board
 * \param conf Config struct containing board, boardSize and states
 */
static void displayNextBestMove(SDL_Renderer* ren, config* conf) {
  conf->solvingBoard = copyBoard(conf->board);
  ColorList* bestSolution = ColorListCreateEmpty(); // init best solution list

  if(conf->boardSize <= MAX_SIZE_SOLVER) {
    ColorList* crtSol = ColorListCreateEmpty();
    solveBoard(conf->solvingBoard, bestSolution, crtSol);
    ColorListDestroy(crtSol);
  }
  else
    solveBoardEfficient(conf->solvingBoard, bestSolution);

  // Set background to white
  SDL_SetRenderDrawColor( ren, 0xFF, 0xFF, 0xFF, 255 );
  SDL_RenderClear(ren);

  displayGameScreen(ren, conf);
  SDL_Color btnTxtColor = {0xF2, 0xF2, 0xF2, 255};
  SDL_Color btnBgColor = {0xFF, 0xFF, 0xFF, 0xFF};

  // Display next best color
  char color;
  ColorListForward(bestSolution, &color);
  switch(color) {
    case 'R':
      btnBgColor.r = 0xFF;
      btnBgColor.g = 0x5D;
      btnBgColor.b = 0x5D;
      btnBgColor.a = 0xFF;
      break;
    case 'G':
      btnBgColor.r = 0x4F;
      btnBgColor.g = 0xE8;
      btnBgColor.b = 0x58;
      btnBgColor.a = 0xFF;
      break;
    case 'B':
      btnBgColor.r = 0x29;
      btnBgColor.g = 0x71;
      btnBgColor.b = 0xC4;
      btnBgColor.a = 0xFF;
      break;
    case 'Y':
      btnBgColor.r = 0xFF;
      btnBgColor.g = 0xC2;
      btnBgColor.b = 0x49;
      btnBgColor.a = 0xFF;
      break;
    case 'O':
      btnBgColor.r = 0x62;
      btnBgColor.g = 0xC4;
      btnBgColor.b = 0xC9;
      btnBgColor.a = 0xFF;
      break;
    case 'M':
      btnBgColor.r = 0xBE;
      btnBgColor.g = 0x7A;
      btnBgColor.b = 0xFF;
      btnBgColor.a = 0xFF;
      break;
  }

  drawButton(" ", BOARDWIDTH + 200, 250, 100, 100, btnTxtColor, btnBgColor, ren);

  SDL_RenderPresent(ren);
  ColorListDestroy(bestSolution);
}

/**
 * \fn void handleBoardClicks(size_t x, size_t y, config* conf)
 * \brief Updates the board with the color chosen by the user (color of the cell he clicked)
 * \param x X coordinate of the cell chosen by the user
 * \param y Y coordinate of the cell chosen by the user
 * \param conf Config struct containing board, boardSize and game/menuState
 */
static void handleBoardClicks(size_t x, size_t y, config* conf, SDL_Renderer* ren) {
  char color;
  size_t width = BOARDWIDTH / 6;
  size_t newX = x / ((BOARDWIDTH / conf->boardSize) + 1); // x position of cell in Board
  size_t newY = y / ((BOARDWIDTH / conf->boardSize) + 1); // y position of cell in Board
  // If user clicks on buttons
  if(y >= BOARDWIDTH + 25 && y <= BOARDWIDTH + 25 + width + (conf->boardSize - 1) / 6) {
    if(x <= width + ((conf->boardSize - 1) / 6 ) + 1)
      color = 'R';
    else if(x >= width + ((conf->boardSize - 1) / 6 ) + 1 && x <= width * 2 + ((conf->boardSize - 1) / 6 ) * 2 + 1)
      color = 'G';
    else if(x >= width * 2 + ((conf->boardSize - 1) / 6 ) * 2 + 1 && x <= width * 3 + ((conf->boardSize - 1) / 6 ) * 3 + 1)
      color = 'B';
    else if(x >= width * 3 + ((conf->boardSize - 1) / 6 ) * 3 + 1 && x <= width * 4 + ((conf->boardSize - 1) / 6 ) * 4 + 1)
      color = 'Y';
    else if(x >= width * 4 + ((conf->boardSize - 1) / 6 ) * 4 + 1 && x <= width * 5 + ((conf->boardSize - 1) / 6 ) * 5 + 1)
      color = 'O';
    else if(x >= width * 5 + ((conf->boardSize - 1) / 6 ) * 5 + 1 && x <= width * 6 + ((conf->boardSize - 1) / 6 ) * 6 + 1)
      color = 'M';
  }
  else // User clicked on the board
  {
    if(newX < conf->boardSize)
      color = getBoardCell(conf->board, newX, newY);
  }

  // click on back-to-menu button
  if(x >= 609 && x <=  909 && y >= 500 && y <= 580){
    conf->state = menuState;
  }

  // click on solution button
  if(x >= 609 && x <=  909 && y >= 100 && y <= 180) {
    conf->solvingBoard = copyBoard(conf->staticBoard); // reset board
    ColorListReset(conf->bestSol); // reset best solution list
    conf->state = solverState;
  }

  //click on light bulb
  if(x >= BOARDWIDTH + 420 && x <=  BOARDWIDTH + 468 && y >= 15 && y <= 63) {
    displayNextBestMove(ren, conf);
  }

  // Check if color contains a correct value
  if(!(color != 'R' && color != 'G' && color != 'B' && color != 'Y' && color != 'O' && color != 'M') && color != getBoardCell(conf->board, 0, 0)){
    floodBoard(conf->board, getBoardCell(conf->board, 0, 0), color, 0, 0);
    conf->turnsLeft--;
    if(isBoardOneColored(conf->board)){
      conf->state = victoryState;
    }
    else if(conf->turnsLeft == 0){
      conf->state = defeatState;
    }
  }
}

/**
 * \fn void gameScreenCheckEvents(SDL_Event event, config* conf)
 * \brief Function checking for events and treating them
 * \param event SDL_Event object used to check and treat the current event
 * \param conf Config struct containing board, boardSize and states
 */
static void gameScreenCheckEvents(SDL_Event event, config* conf, SDL_Renderer* ren) {
  needsRefresh = 1;
  switch(event.type) {
    case SDL_MOUSEBUTTONDOWN:
      handleBoardClicks(event.button.x, event.button.y, conf, ren);
      break;
    default:
      needsRefresh = 0;
  }
}

/**
 * \fn void gameScreen(SDL_Event event, SDL_Renderer* ren, config* conf)
 * \brief Main function of gameScreen, checking for events and displaying the gameScreen
 * \param event SDL_Event object used to check and treat the current event
 * \param ren SDL_Renderer object used to display the board
 * \param conf Config struct containing board, boardSize and states
 */
extern void gameScreen(SDL_Event event, SDL_Renderer* ren, config* conf) {
  if(needsRefresh){
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    displayGameScreen(ren, conf);
    SDL_RenderPresent(ren);
  }

  gameScreenCheckEvents(event, conf, ren);
}
