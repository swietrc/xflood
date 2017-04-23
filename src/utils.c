/**
 * \file utils.c
 * File containing utility function, can be seen as the app toolkit
 * \author Simon Wietrich
 * \author Pierre Genthon
 * \author Celestin Caumes
 * \author Camille Schnell
 **/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "utils.h"

#define BTN_MARGIN 25 

/**
 * \fn void drawButton(char* txt, int x, int y, int w, int h, SDL_Color txtColor, SDL_Color backgroundColor, SDL_Renderer* ren)
 * \brief Draws a button on screen
 * \param txt Text to display on the button
 * \param x X position of the button
 * \param y Y position of the button
 * \param w Width of the button
 * \param h Height of the button
 * \param txtColor Color of the text of the button
 * \param backgroundColor Color of the button
 * \param ren Renderer on which to draw the button
 */

void drawButton(char* txt, int x, int y, int w, int h, SDL_Color txtColor, SDL_Color backgroundColor, SDL_Renderer* ren) {
    SDL_Surface* surfaceText = TTF_RenderText_Solid(buttonFont, txt, txtColor);
    SDL_Texture* text = SDL_CreateTextureFromSurface(ren, surfaceText);


    /* Text is positionned relative to the button and its size */
    SDL_Rect text_rect;   // Position and size of the text
    SDL_Rect button_rect; // Position and size of the button
    button_rect.x = x;
    button_rect.y = y;
    text_rect.w = surfaceText->w; // controls the width of the rect
    text_rect.h = surfaceText->h; // controls the height of the rect
    button_rect.w = w;
    button_rect.h = h;
    text_rect.x = button_rect.x + ((button_rect.w / 2) - (text_rect.w / 2));  //controls the rect's x coordinate
    text_rect.y = button_rect.y + ((button_rect.h / 2) - (text_rect.h / 2));  //controls the rect's x coordinate
    

    SDL_SetRenderDrawColor( ren, backgroundColor.r, backgroundColor.g,  backgroundColor.b, backgroundColor.a ); // Color background of button
    SDL_RenderDrawRect( ren, &button_rect );
    SDL_RenderCopy(ren, text, NULL, &text_rect);

    // Free surface and texture
    SDL_FreeSurface(surfaceText);
    SDL_DestroyTexture(text);
}
