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

static int needsRefresh = 1;

/**
 * \fn void handleMenuClicks(int x, int y, config* conf)
 * \brief Alter the conf given a click on (x,y) coordinates
 * \param x int the x coordinate of the pixel that has been clicked relative to the application's window
 * \param y int the y coordinate of the pixel that has been clicked relative to the application's window
 * \param conf config* a pointer to the application's configuration data structure
 */
static void handleMenuClicks(int x, int y, config* conf) {
    if(y >= 300 && y <= 400) { // size buttons
        if(x >= 300 && x <= 425) {
            conf->boardSize = 12;
        }
        else if(x >= 437  && x <= 562) {
            conf->boardSize = 18;
        }
        else if(x >= 574 && x <= 699) {
            conf->boardSize = 24;
        }
    }
    else if(y >= 400 && y <= 500 && x >= 300 && x <= 700){ // Play button
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
}

/**
 * \fn void displayMenuScreen(SDL_Renderer* ren, config* conf)
 * \brief Given the application configuration, displays the menu through renderer passed in parameters
 * \param ren SDL_Renderer object used to display the menu
 * \param conf config* a pointer to the application's configuration data structure
 */
static void displayMenuScreen(SDL_Renderer* ren, config* conf) {
    // Set background to black
    SDL_SetRenderDrawColor( ren, 0xFF, 0xFF, 0xFF, 255 );

    // Clear renderer
    SDL_RenderClear(ren);

    /** Writing label for size of board **/
    SDL_Color messageColor = {0x55, 0x55, 0x55, 255};

    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(defaultFont, "Taille de la grille", messageColor);

    SDL_Texture* Message = SDL_CreateTextureFromSurface(ren, surfaceMessage); // convert surface into a texture

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = (WINDOW_WIDTH / 2) - (surfaceMessage->w / 2);  //controls the rect's x coordinate
    Message_rect.y = 250; // controls the rect's y coordinte
    Message_rect.w = surfaceMessage->w; // controls the width of the rect
    Message_rect.h = surfaceMessage->h; // controls the height of the rect

    SDL_RenderCopy(ren, Message, NULL, &Message_rect);

    /** Creation of 3 buttons for the board size **/
    const int w_total = 400;
    const int x_buttons = (WINDOW_WIDTH/2) - (w_total/2);
    const int y_buttons = 330;
    const int w_buttons = 125;
    const int margin_buttons = 12;

    SDL_Color backColor = {0x42, 0x72, 0x3d, 0xFF};

    // First button
    SDL_Color backColorB1 = {0x6F, 0xD8, 0x68, 0xFF};
    SDL_Color backColorCurrentB1 = {0x3F, 0xD8, 0x38, 0xFF};
    SDL_Color buttonTextColor = {0xF2, 0xF2, 0xF2, 0xFF};
    drawButton("12 x 12", x_buttons, y_buttons, w_buttons, 50, buttonTextColor, conf->boardSize == 12 ? backColorCurrentB1 : backColorB1, ren);

    // Second button
    SDL_Color backColorB2 = {0xFF, 0xB9, 0x5E, 0xFF};
    SDL_Color backColorCurrentB2 = {0xFF, 0xB9, 0x10, 0xFF};
    drawButton("18 x 18", x_buttons + w_buttons + margin_buttons, y_buttons, w_buttons, 50, buttonTextColor, conf->boardSize == 18 ? backColorCurrentB2 : backColorB2, ren);

    // Third button
    SDL_Color backColorB3 = {0xF9, 0x4D, 0x4D, 0xFF};
    SDL_Color backColorCurrentB3 = {0xFF, 0x2D, 0x2D, 0xFF};
    drawButton("24 x 24", x_buttons + (2*(w_buttons+margin_buttons)), y_buttons, w_buttons, 50, buttonTextColor, conf->boardSize == 24 ? backColorCurrentB3: backColorB3, ren);

    // Play game button
    drawButton("Let's go !", x_buttons, 400, w_total, 100, buttonTextColor, backColor, ren);

    /** Adding Logo image **/
    SDL_Surface* surfaceImage = IMG_Load("resources/img/logo.png");
    SDL_Texture* textureImage = SDL_CreateTextureFromSurface(ren, surfaceImage);

    SDL_Rect imageRect; //create a rect
    imageRect.x = (WINDOW_WIDTH/2) - (surfaceImage->w/2);  //controls the rect's x coordinate
    imageRect.y = 40; // controls the rect's y coordinte
    imageRect.w = surfaceImage->w; // controls the width of the rect
    imageRect.h = surfaceImage->h; // controls the height of the rect

    SDL_RenderCopy(ren, textureImage, NULL, &imageRect);

    // Free surfaces and textures
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
    SDL_FreeSurface(surfaceImage);
    SDL_DestroyTexture(textureImage);
    
    SDL_SetRenderDrawColor(ren, 0xFF, 0, 0, 0xFF);
    
    // DEBUG Center Line
    // SDL_RenderDrawLine(ren, WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
}

/**
 * \fn void menuScreenCheckEvents(SDL_Event event, config* conf)
 * \brief Dispatches all events to a handler for specific event type
 * \param event SDL_Event the event to process
 * \param conf config* a pointer to the application's configuration data structure
 */
static void menuScreenCheckEvents(SDL_Event event, config* conf) {
    needsRefresh = 1;
    switch(event.type) {
        case SDL_MOUSEBUTTONDOWN:
            handleMenuClicks(event.button.x, event.button.y, conf);
            break;
        default: // its useless to redraw the screen if no event was handled, the ui state wasn't changed
            needsRefresh = 0;
    }
}

/**
 * \fn menuScreen(SDL_Event event, SDL_Renderer* ren, config* conf)
 * \brief Dispatches given event and render the screen
 * \param event SDL_Event the event to process
 * \param ren SDL_Renderer the object used to draw on screen
 * \param conf config* a pointer to the application's configuration data structure
 */
extern void menuScreen(SDL_Event event, SDL_Renderer* ren, config* conf) {
    if(needsRefresh){
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        displayMenuScreen(ren, conf);
        SDL_RenderPresent(ren); // Render the board to the screen
    }

    menuScreenCheckEvents(event, conf);
}
