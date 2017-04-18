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

static int needsRefresh = 1;

/**
 * \fn void handleBoardClicks(size_t x, size_t y, config* conf)
 * \brief Updates the board with the color chosen by the user (color of the cell he clicked)
 * \param x X coordinate of the cell chosen by the user
 * \param y Y coordinate of the cell chosen by the user
 * \param conf Config struct containing board, boardSize and game/menuState
 */
static void handleBoardClicks(size_t x, size_t y, config* conf) {
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
  if(x >= BOARDWIDTH + 105 && x <=  BOARDWIDTH + 405 && y >= 540 && y <= 620){
    conf->state = menuState;
  }

  // Check if color contains a correct value
  if(!(color != 'R' && color != 'G' && color != 'B' && color != 'Y' && color != 'O' && color != 'M') && color != getBoardCell(conf->board, 0, 0)){
    floodBoard(conf->board, getBoardCell(conf->board, 0, 0), color, 0, 0);
    conf->turnsLeft--;
    if(isBoardOneColored(conf->board)){
      printf("gagné\n");
      freeBoard(conf->board); // free Board at end of game
      conf->state = menuState;
    }
    else if(conf->turnsLeft == 0){
      printf("perdu\n");
      freeBoard(conf->board); // free Board at end of game
      conf->state = menuState;
    }
  }
}


/**
 * \fn void displayGameScreen(SDL_Renderer* ren, config* conf)
 * \brief Displays the board in the game window
 * \param ren SDL_Renderer object used to display the board
 * \param conf Config struct containing board, boardSize and game/menuState
 */
static void displayGameScreen(SDL_Renderer* ren, config* conf) {
  // Set background to black
  SDL_SetRenderDrawColor( ren, 0, 0, 0, 255 );

  for(size_t x = 0; x < conf->boardSize; x++) {
    for(size_t y = 0; y < conf->boardSize; y++) {
      // Init rect
      SDL_Rect rect;
      rect.x = x + (BOARDWIDTH / conf->boardSize)*x;
      rect.y = y + (BOARDWIDTH / conf->boardSize)*y;
      rect.w = (BOARDWIDTH / conf->boardSize);
      rect.h = (BOARDWIDTH / conf->boardSize);

      // Set render color ( rect will be rendered in this color )
      switch(getBoardCell(conf->board, x, y)) {
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

  // Creation of 6 buttons (one per color)
  for(int i = 0; i < 6; i ++) {
    int width = BOARDWIDTH / 6;
    SDL_Rect rect;
    rect.x = width*i + ((conf->boardSize - 1) / 6 ) * i + i;
    rect.y = BOARDWIDTH + 25;
    rect.w = width + (conf->boardSize - 1) / 6;
    rect.h = width + (conf->boardSize - 1) / 6;

    // Set render color ( rect will be rendered in this color )
    switch(i) {
      case 0:
        SDL_SetRenderDrawColor( ren, 255, 0, 0, 255 );
            break;
      case 1:
        SDL_SetRenderDrawColor( ren, 0, 255, 0, 255 );
            break;
      case 2:
        SDL_SetRenderDrawColor( ren, 0, 0, 255, 255 );
            break;
      case 3:
        SDL_SetRenderDrawColor( ren, 255, 255, 0, 255 );
            break;
      case 4:
        SDL_SetRenderDrawColor( ren, 0, 255, 255, 255 );
            break;
      case 5:
        SDL_SetRenderDrawColor( ren, 255, 0, 255, 255 );
            break;
    }

    /** Writing label for size of board and turns left**/
    SDL_Color messageColor = {255, 255, 255, 255};

    char turnsLeft[50];
    sprintf(turnsLeft, "Coups restants : %d/%d", conf->turnsLeft, conf->allowedTurns);

    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(defaultFont, turnsLeft, messageColor);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(ren, surfaceMessage);

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = BOARDWIDTH + 50;  //controls the rect's x coordinate
    Message_rect.y = 20; // controls the rect's y coordinte
    Message_rect.w = 400; // controls the width of the rect
    Message_rect.h = 60; // controls the height of the rect

    SDL_RenderCopy(ren, Message, NULL, &Message_rect);

    // Render board
    SDL_RenderFillRect( ren, &rect );

    // Free surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

    // back to menu button
    SDL_Color backToMenuTxtColor = {0, 0, 100, 255};
    SDL_Color backToMenuBgColor = {70, 70, 70, 255};
    drawButton(" Retour au menu ", BOARDWIDTH + 105, 540, 300, 80, backToMenuTxtColor, backToMenuBgColor, ren);
  }
}

/**
 * \fn void gameScreenCheckEvents(SDL_Event event, config* conf)
 * \brief Function checking for events and treating them
 * \param event SDL_Event object used to check and treat the current event
 * \param conf Config struct containing board, boardSize and game/menuState
 */
static void gameScreenCheckEvents(SDL_Event event, config* conf) {
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
 * \fn void gameScreen(SDL_Event event, SDL_Renderer* ren, config* conf)
 * \brief Main function of gameScreen, checking for events and displaying the gameScreen
 * \param event SDL_Event object used to check and treat the current event
 * \param ren SDL_Renderer object used to display the board
 * \param conf Config struct containing board, boardSize and game/menuState
 */
extern void gameScreen(SDL_Event event, SDL_Renderer* ren, config* conf) {
  if(needsRefresh){
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    displayGameScreen(ren, conf);
    SDL_RenderPresent(ren);
  }

  gameScreenCheckEvents(event, conf);
}
