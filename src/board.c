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
board initBoard(size_t size) {
    board b = (board) calloc(size, sizeof(Cell));
    return b;
}

/**
 * \fn board initRandomBoard(int size)
 * \brief Initialises a strictly random board.
 * \param size Width/Height of the board to initialize
 * \return initialized random board
 */
board initRandomBoard(size_t size) {
    srand(time(1));
    int board_size = size*size;

    board b = (board) malloc(sizeof(Cell) * board_size);
    for (size_t i = 0 ; i < board_size ; i++) {
        b[i] = rand() % NB_COLOURS;
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
Cell getBoardCell(board b, size_t size, int x, int y) {
    return b[x * size + y];
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
void setBoardCell(board b, size_t size, int x, int y, Cell color) {
   b[x * size + y] = color; 
}

/**
 * \fn void floodBoard(board b, size_t size, Cell oldColor, Cell newColor, int x, int y)
 * \brief Recursive implementation of flood fill algorithm
 * \param b board to flood
 * \param size Size of board b
 * \param oldColor previous board color
 * \param newColor color of the flood
 * \param x X position to flood
 * \param y X position to flood
 */
void floodBoard(board b, size_t size, Cell oldColor, Cell newColor, int x, int y) {
    if ((oldColor == newColor) || (getBoardCell(b, size, x, y) != oldColor)) {
        printf("%d %d\n", x, y);
        return;
    }

    setBoardCell(b, size, x, y, newColor);

    // Check left
    if (x > 0)
        floodBoard(b, size, oldColor, newColor, x - 1, y);
    // Check right
    if (x < size - 1)
        floodBoard(b, size, oldColor, newColor, x + 1, y);
    // Check up
    if (y > 0)
        floodBoard(b, size, oldColor, newColor, x, y - 1);
    // Check down
    if (y < size - 1)
        floodBoard(b, size, oldColor, newColor, x, y + 1);
}

void freeBoard(board b) {
    free(b);
}

void debug_displayBoard(size_t size, board b) {
    char cchar[6] = { 'R', 'G', 'B', 'Y', 'O', 'M' };

    for (size_t i = 0 ; i < size*size ; i++) {
        printf("%c", cchar[b[i]]);

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
int areSimilarBoards(board b1, board b2, size_t size) {
    for(int x=0; x<size; x++){
        for(int y=0; y<size; y++){
            if(getBoardCell(b1, size, x, y) != getBoardCell(b2, size, x, y)){
                return 0;
            }
        }
    }
    return 1;
}
