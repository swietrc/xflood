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

size_t boardHeight = BOARDWIDTH;

/**
 * \fn void updateBoard(Board* board, size_t x, size_t y)
 * \brief Updates the board with the color chosen by the user (color of the cell he clicked)
 * \param board Board to update
 * \param x X coordinate of the cell chosen by the user
 * \param y Y coordinate of the cell chosen by the user
 */
static void updateBoard(size_t x, size_t y, config* conf) {
  char color;
  size_t width = BOARDWIDTH / 6;
  size_t newX = x / ((BOARDWIDTH / conf->boardSize) + 1); // x position of cell in Board
  size_t newY = y / ((BOARDWIDTH / conf->boardSize) + 1); // y position of cell in Board
  // If user clicks on buttons
  if(y >= boardHeight + 20 && y <= boardHeight + 20 + width) {
    printf("first case\n");
    if(x <= width + 2)
      color = 'R';
    else if(x >= width + 2 && x <= width * 2 + 2)
      color = 'G';
    else if(x >= width * 2 + 2 && x <= width * 3 + 2)
      color = 'B';
    else if(x >= width * 3 + 2 && x <= width * 4 + 2)
      color = 'Y';
    else if(x >= width * 4 + 2 && x <= width * 5 + 2)
      color = 'O';
    else if(x >= width * 5 + 2 && x <= width * 6 + 2)
      color = 'M';
  }
  else // User clicked on the board
  {
    printf("else\n");
    if(newX < conf->boardSize)
      color = getBoardCell(conf->board, newX, newY);
  }

  //printf("COLOR : %c\nWIDTH : %d  X : %d  Y : %d\nNX: %d  NY : %d\n", color, width, x, y, newX, newY);
  // Check if color contains a correct value
  if(!(color != 'R' && color != 'G' && color != 'B' && color != 'Y' && color != 'O' && color != 'M') ){
    floodBoard(conf->board, getBoardCell(conf->board, 0, 0), color, 0, 0);
    conf->turnsLeft--;
    if(isBoardOneColored(conf->board)){
      printf("gagné\n");
      conf->state = menuState;
    }
    else if(conf->turnsLeft == 0){
      printf("perdu\n");
      conf->state = menuState;
    }
  }
}


/**
 * \fn void displayGameScreen(Board* board, SDL_Renderer* ren)
 * \brief Displays the board in the game window
 * \param board Board to display
 * \param ren SDL_Renderer object used to display the board
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

      // if conf->boardSize is > 40, size of board will be > BOARDWIDTH
      if( y == conf->boardSize - 1 && conf->boardSize > 40)
        boardHeight = y + (BOARDWIDTH / conf->boardSize)*y;

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
    rect.y = boardHeight + 20;
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

    /** Writing label for size of board **/
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
  }
}

static void gameScreenCheckEvents(SDL_Event event, config* conf) {
  switch(event.type) {
    case SDL_MOUSEBUTTONDOWN:
      updateBoard(event.button.x, event.button.y, conf);
      /*if(isBoardOneColored(board)) {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(0);
      }*/
      break;
  }
}

extern void gameScreen(SDL_Event event, SDL_Renderer* ren, config* conf) {
  gameScreenCheckEvents(event, conf);
  displayGameScreen(ren, conf);
}
