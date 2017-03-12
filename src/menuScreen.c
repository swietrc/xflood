/**
 * \file menuScreen.c
 * File displaying the game menu window.
 * \author Simon Wietrich
 * \author Pierre Genthon
 * \author Celestin Caumes
 * \author Camille Schnell
 **/

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "board.h"
#include "utils.h"
#include "menuScreen.h"

static void drawButton(char* txt, int x, int y, int w, int h, SDL_Color txtColor, SDL_Color backgroundColor, SDL_Renderer* ren) {
  SDL_Surface* surfaceText = TTF_RenderText_Blended(defaultFont, txt, txtColor);
  SDL_Texture* text = SDL_CreateTextureFromSurface(ren, surfaceText);

  SDL_Rect text_rect;
  text_rect.x = x;  //controls the rect's x coordinate
  text_rect.y = y; // controls the rect's y coordinte
  text_rect.w = w; // controls the width of the rect
  text_rect.h = h; // controls the height of the rect

  SDL_SetRenderDrawColor( ren, backgroundColor.r, backgroundColor.g,  backgroundColor.b, backgroundColor.a ); // Color background of button
  SDL_RenderFillRect( ren, &text_rect );
  SDL_RenderCopy(ren, text, NULL, &text_rect);

  // Free surface and texture
  SDL_FreeSurface(surfaceText);
  SDL_DestroyTexture(text);
}

static void updateMenu(int x, int y, config* conf, SDL_Renderer* ren) {
  if(y >= 300 && y <= 400) { // size buttons
    if(x >= 270 && x <= 370) {
      conf->boardSize = 12;
      /** Change current button background when clicked **/
      SDL_Color backColorCurrent = {50, 50, 50, 255};
      SDL_Color backColor = {50, 50, 50, 255};
      // First button
      SDL_Color messageColorB1 = {0, 0, 255, 255};
      drawButton("12 x 12", 270, 300, 100, 50, messageColorB1, backColorCurrent, ren);
      // Second button
      SDL_Color messageColorB2 = {0, 0, 255, 255};
      drawButton("18 x 18", 410, 300, 100, 50, messageColorB2, backColor, ren);
      // Third button
      SDL_Color messageColorB3 = {0, 0, 255, 255};
      drawButton("24 x 24", 550, 300, 100, 50, messageColorB3, backColor, ren);
    }
    else if(x >= 410  && x <= 510) {
      conf->boardSize = 18;

    }
    else if(x >= 550 && x <= 650) {
      conf->boardSize = 24;

    }
  }
  else if(y >= 400 && y <= 550 && x >= 280 && x <= 680){
    conf->state = gameState;
    // allowed turns is a function of board size
    switch (conf->boardSize) {
      case 12:
        conf->allowedTurns = 22;
        break;
      case 18:
        conf->allowedTurns = 34;
        break;
      case 24:
        conf->allowedTurns = 44;
        break;
    }
    conf->turnsLeft = conf->allowedTurns;
    conf->board = initRandomBoard(conf->boardSize);
  }

  printf("x : %d  y : %d\nsize : %d state : %d\n", x, y, conf->boardSize, conf->state);
}

/**
 * \fn void displayGameScreen(Board* board, SDL_Renderer* ren)
 * \brief Displays the board in the game window
 * \param board Board to display
 * \param ren SDL_Renderer object used to display the board
 */
static void displayMenuScreen(SDL_Renderer* ren) {
  // Set background to black
  SDL_SetRenderDrawColor( ren, 0, 0, 0, 255 );

  // Clear renderer
  SDL_RenderClear(ren);

  /** Writing label for size of board **/
  SDL_Color messageColor = {0, 255, 255, 255};

  SDL_Surface* surfaceMessage = TTF_RenderText_Blended(defaultFont, "Taille de la grille", messageColor);

  SDL_Texture* Message = SDL_CreateTextureFromSurface(ren, surfaceMessage); // convert surface into a texture

  SDL_Rect Message_rect; //create a rect
  Message_rect.x = 220;  //controls the rect's x coordinate
  Message_rect.y = 220; // controls the rect's y coordinte
  Message_rect.w = 500; // controls the width of the rect
  Message_rect.h = 80; // controls the height of the rect

  SDL_RenderCopy(ren, Message, NULL, &Message_rect);

  /** Creation of 3 buttons for the board size **/
  SDL_Color backColor = {50, 50, 50, 255};
  // First button
  SDL_Color messageColorB1 = {0, 0, 255, 255};
  drawButton("12 x 12", 270, 300, 100, 50, messageColorB1, backColor, ren);

  // Second button
  SDL_Color messageColorB2 = {255, 255, 255, 255};
  drawButton("18 x 18", 410, 300, 100, 50, messageColorB2, backColor, ren);

  // Third button
  SDL_Color messageColorB3 = {255, 0, 0, 255};
  drawButton("24 x 24", 550, 300, 100, 50, messageColorB3, backColor, ren);

  // Play game button
  SDL_Color messageColorB4 = {0, 255, 0, 255};
  drawButton("Let's go !", 280, 400, 400, 150, messageColorB4, backColor, ren);

  /** Adding Logo image **/
  SDL_Surface* surfaceImage = IMG_Load("resources/img/logo.png");
  SDL_Texture* textureImage = SDL_CreateTextureFromSurface(ren, surfaceImage);

  SDL_Rect imageRect; //create a rect
  imageRect.x = 370;  //controls the rect's x coordinate
  imageRect.y = 10; // controls the rect's y coordinte
  imageRect.w = 200; // controls the width of the rect
  imageRect.h = 200; // controls the height of the rect

  SDL_RenderCopy(ren, textureImage, NULL, &imageRect);

  // Free surfaces and textures
  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(Message);
  SDL_FreeSurface(surfaceImage);
  SDL_DestroyTexture(textureImage);
}

static void menuScreenCheckEvents(SDL_Event event, config* conf, SDL_Renderer* ren) {
  switch(event.type) {
    case SDL_MOUSEBUTTONDOWN:
      updateMenu(event.button.x, event.button.y, conf, ren);
      break;
  }
}

extern void menuScreen(SDL_Event event, SDL_Renderer* ren, config* conf) {
  menuScreenCheckEvents(event, conf, ren);
  displayMenuScreen(ren);
}
