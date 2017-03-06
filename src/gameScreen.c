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

/**
 * \fn void updateBoard(Board* board, size_t x, size_t y)
 * \brief Updates the board with the color chosen by the user (color of the cell he clicked)
 * \param board Board to update
 * \param x X coordinate of the cell chosen by the user
 * \param y Y coordinate of the cell chosen by the user
 */
void updateBoard(Board* board, size_t x, size_t y) {
  char color = getBoardCell(board, x, y);
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
