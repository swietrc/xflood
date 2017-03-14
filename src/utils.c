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
