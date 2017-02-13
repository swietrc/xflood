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

/**
 * \fn board initBoard(int size)
 * \brief Initialises an empty board
 * \param size Width/Height  of the board to initialize
 * \return initialized empty board
 */
Board* initBoard(size_t size) {
    size_t board_size = size * size;
    Board* b = (Board*) malloc(sizeof(Board));
    b->grid = (Cell*) calloc(board_size, sizeof(Cell));
    b->size = size;
    return b;
}

/**
 * \fn board initRandomBoard(int size)
 * \brief Initialises a strictly random board.
 * \param size Width/Height of the board to initialize
 * \return initialized random board
 */
Board* initRandomBoard(size_t size) {
    srand(1);
    int board_size = size*size;

    Board* b = (Board*) malloc(sizeof(Board));
    b->grid = (Cell*) calloc(board_size, sizeof(Cell));
    b->size = size;
    for (size_t i = 0 ; i < board_size ; i++) {
        b->grid[i] = rand() % NB_COLOURS;
    }
    return b;
}

/**
 * \fn board getBoardCell(board b, size_t size, int x, int y)
 * \brief Get value of a specific cell on the board
 * \param b
 * \param size Size of board b
 * \param x X coordinate of the cell
 * \param y Y coordinate of the cell
 * \return cell at coords x, y on board b
 */
Cell getBoardCell(Board* b, int x, int y) {
    size_t s = b->size;
    return b->grid[y * s + x];
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
void setBoardCell(Board* b, int x, int y, Cell color) {
   b->grid[y * b->size + x] = color; 
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
void floodBoard(Board* b, Cell oldColor, Cell newColor, int x, int y) {
    char cchar[6] = { 'R', 'G', 'B', 'Y', 'O', 'M' };

    if ((oldColor == newColor) || (getBoardCell(b, x, y) != oldColor)) {
        printf("X: %d Y:%d | Current %d Old %c New %c\n", x, y,getBoardCell(b, x, y), cchar[oldColor], cchar[newColor]);
        return;
    }

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
    free(b);
}

void debug_displayBoard(Board* b) {
    char* cchar[6] = { "\e[31m0\e[0m", "\e[92m1\e[0m", "\e[34m2\e[0m", "\e[93m3\e[0m", "\e[38;5;166m4\e[0m", "\e[35m5\e[0m" };

    for (size_t i = 0 ; i < b->size * b->size; i++) {
        printf("%s ", cchar[b->grid[i]]);

        if (i%24 == 23) printf("\n");
    }
}

/**
 * Compare two boards (assuming they have the same size)
 * they will be considered similar if the color of the cells in the same spot is the same on both boards.
 * @param b1 first board
 * @param b2 second board
 * @param size The size of both boards
 * @return 1 if they are similar, 0 otherwise
 */
/*
int areSimilarBoards(Board* b1, Board* b2, size_t size) {
    for(int x=0; x<size; x++){
        for(int y=0; y<size; y++){
            if(getBoardCell(b1, size, x, y) != getBoardCell(b2, size, x, y)){
                return 0;
            }
        }
    }
    return 1;
}
*/
