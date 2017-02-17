/**
 * \file board.c
 * Contains all board related data structures and operations.
 * \author Simon Wietrich
 * \author Pierre Genthon
 * \author Celestin Caumes
 * \author Camille Schnell
 **/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"

struct board {
    size_t size;
    char* grid;
};

/* Conversion table for the rand() function
   used to convert random generated number between 0-5
   into one of the 6 chars below */
const char colours[NB_COLOURS] = {'R', 'G', 'B', 'Y', 'O', 'M'};

/**
 * \fn board initBoard(int size)
 * \brief Initialises an empty board
 * \param size Width/Height  of the board to initialize
 * \return initialized empty board
 */
Board* initBoard(size_t size) {
    size_t board_size = size * size;
    Board* b = malloc(sizeof(Board));
    b->grid = calloc(board_size, sizeof(char));
    b->size = size;
    return b;
}

/**
 * \fn board initRandomBoard(int size)
 * \brief Initialises a strictly random 6-colored board.
 * \param size Width/Height of the board to initialize
 * \return initialized random board
 */
Board* initRandomBoard(size_t size) {
    /* Conversion table for the rand() function
       used to convert random generated number between 0-5
       into one of the 6 chars below */
    size_t board_size = size * size;

    Board* b = malloc(sizeof(Board));
    b->grid = calloc(board_size, sizeof(char));
    b->size = size;

    for (size_t i = 0 ; i < board_size ; i++) {
        b->grid[i] = colours[rand() % NB_COLOURS];
    }

    return b;
}

/**
 * \fn board getBoardCell(board b, size_t size, int x, int y)
 * \brief Get value of a specific cell on the board
 * \param b the board
 * \param x X coordinate of the cell
 * \param y Y coordinate of the cell
 * \return cell at coords x, y on board b
 */
char getBoardCell(Board* b, unsigned int x, unsigned int y) {
    return b->grid[y * b->size + x];
}

/**
 * \fn void setBoardCell(board b, size_t size, int x, int y, Cell color)
 * \brief Set value of a specific cell on the board
 * \param b
 * \param size Size of board b
 * \param x X coordinate of the cell
 * \param y Y coordinate of the cell
 * \param color new value of the cell
 */
void setBoardCell(Board* b, unsigned int x, unsigned int y, char color) {
   b->grid[y * b->size + x] = color; 
}

/**
 * Sets the Board's grid
 * @param b The board that will hold the new grid
 * @param newGrid The new grid, must be of the same size as the board
 */
void setGrid(Board* b, char* newGrid){
    free(b->grid);
    b->grid = newGrid;
}

/**
 * \fn void floodBoard(board b, size_t size, Cell oldColor, Cell newColor, int x, int y)
 * \brief Recursive implementation of flood fill algorithm
 * \param b board to flood
 * \param size Size of board b
 * \param oldColor previous board color
 * \param newColor color of the flood
 * \param x X position to flood
 * \param y Y position to flood
 */
void floodBoard(Board* b, char oldColor, char newColor, unsigned int x, unsigned int y) {

    if ((oldColor == newColor) || (getBoardCell(b, x, y) != oldColor))
        return;

    setBoardCell(b, x, y, newColor);

    // Check left
    if (x > 0)
        floodBoard(b, oldColor, newColor, x - 1, y);
    // Check right
    if (x < (b->size - 1))
        floodBoard(b, oldColor, newColor, x + 1, y);
    // Check up
    if (y > 0)
        floodBoard(b, oldColor, newColor, x, y - 1);
    // Check down
    if (y < (b->size - 1))
        floodBoard(b, oldColor, newColor, x, y + 1);
}

void freeBoard(Board* b) {
    free(b->grid);
    free(b);
}

/**
 * \brief Display the board \a b to stdin
 */
void debug_displayBoard(Board* b) {
    // char* cchar[6] = { "\e[31m0\e[0m", "\e[92m1\e[0m", "\e[34m2\e[0m", "\e[93m3\e[0m", "\e[38;5;166m4\e[0m", "\e[35m5\e[0m" };
    for (size_t i = 0 ; i < b->size * b->size; i++) {
        printf("%c", b->grid[i]);

        if (i%b->size == b->size-1) printf("\n");
    }
}

/**
 * Compare two boards (assuming they both have the size of b1)
 * they will be considered similar if the color of the cells in the same spot is the same on both boards.
 * @param b1 first board
 * @param b2 second board
 * @param size The size of both boards
 * @return true if they are similar, false otherwise
 */
bool areSimilarBoards(Board* b1, Board* b2) {
    size_t size = b1->size;
    for(unsigned int x=0; x<size; x++){
        for(unsigned int y=0; y<size; y++){
            if(getBoardCell(b1, x, y) != getBoardCell(b2, x, y)){
                return false;
            }
        }
    }
    return true;
}

/**
 * Checks if all the cells on the board's grid are of the same color
 * @param b the board to check
 * @retrun true if the board is colored with only one color, false otherwise
 */
bool isBoardOneColored(Board* b){
    // the board color is the color of the first cell (in top left corner of the grid)
    char boardColor = b->grid[0];

    for(unsigned int x=0; x<b->size; x++){
        for(unsigned int y=0; y<b->size; y++){
            if(getBoardCell(b, x, y) != boardColor){
                return false;
            }
        }
    }
    return true;
}