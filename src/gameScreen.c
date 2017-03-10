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
#include "board.h"
#include "gameScreen.h"

size_t boardHeight = BOARDWIDTH;

/**
 * \fn void updateBoard(Board* board, size_t x, size_t y)
 * \brief Updates the board with the color chosen by the user (color of the cell he clicked)
 * \param board Board to update
 * \param x X coordinate of the cell chosen by the user
 * \param y Y coordinate of the cell chosen by the user
 */
void updateBoard(Board* board, size_t x, size_t y) {
  char color;
  size_t width = BOARDWIDTH / 6;
  size_t newX = x / ((BOARDWIDTH / MAX_SIZE) + 1); // x position of cell in Board
  size_t newY = y / ((BOARDWIDTH / MAX_SIZE) + 1); // y position of cell in Board
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
    if(newX < MAX_SIZE)
      color = getBoardCell(board, newX, newY);
  }

  printf("COLOR : %c\nWIDTH : %d  X : %d  Y : %d\nNX: %d  NY : %d\n", color, width, x, y, newX, newY);
  // Check if color contains a correct value
  if(!(color != 'R' && color != 'G' && color != 'B' && color != 'Y' && color != 'O' && color != 'M') )
    floodBoard(board, getBoardCell(board, 0, 0), color, 0, 0);
}


/**
 * \fn void displayGameScreen(Board* board, SDL_Renderer* ren)
 * \brief Displays the board in the game window
 * \param board Board to display
 * \param ren SDL_Renderer object used to display the board
 */
void displayGameScreen(Board* board, SDL_Renderer* ren) {
  // Set background to black
  SDL_SetRenderDrawColor( ren, 0, 0, 0, 255 );

  // Clear window
  SDL_RenderClear( ren );

  for(size_t x = 0; x < MAX_SIZE; x++) {
    for(size_t y = 0; y < MAX_SIZE; y++) {
      // Init rect
      SDL_Rect rect;
      rect.x = x + (BOARDWIDTH / MAX_SIZE)*x;
      rect.y = y + (BOARDWIDTH / MAX_SIZE)*y;
      rect.w = (BOARDWIDTH / MAX_SIZE);
      rect.h = (BOARDWIDTH / MAX_SIZE);

      // if MAX_SIZE is > 40, size of board will be > BOARDWIDTH
      if( y == MAX_SIZE - 1 && MAX_SIZE > 40)
        boardHeight = y + (BOARDWIDTH / MAX_SIZE)*y;

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

  // Creation of 6 buttons (one per color)
  for(int i = 0; i < 6; i ++) {
    int width = BOARDWIDTH / 6;
    SDL_Rect rect;
    rect.x = width*i + ((MAX_SIZE - 1) / 6 ) * i + i;
    rect.y = boardHeight + 20;
    rect.w = width + (MAX_SIZE - 1) / 6;
    rect.h = width + (MAX_SIZE - 1) / 6;

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

    // Render rect
    SDL_RenderFillRect( ren, &rect );
  }


  // Render the rect to the screen
  SDL_RenderPresent(ren);
}
