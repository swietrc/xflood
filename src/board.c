/**
 * \file board.c
 * Contains all operations done on the board.
 * \author Simon Wietrich
 **/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"

/**
 * \fn
 * Initialises an empty board
 * \param size Size of the board to initialize
 **/
board initBoard(int size) {
    board b = (board) calloc(size, sizeof(Cell));
    return b;
}

board initRandomBoard(int size) {
    srand(1);
    int board_size = size*size;

    board b = (board) malloc(sizeof(Cell) * board_size);
    for (size_t i = 0 ; i < board_size ; i++) {
        b[i] = rand() % NB_COLOURS;
    }
    return b;
}

Cell getBoardCell(board b, size_t size, int x, int y) {
    return b[x * size + y];
}

void setBoardCell(board b, size_t size, int x, int y, Cell color) {
   b[x * size + y] = color; 
}

void floodBoard(board b, size_t size, Cell oldColor, Cell newColor, int x, int y) {
    if ((oldColor == newColor) || (getBoardCell(b, size, x, y) != oldColor)) {
        printf("%d %d\n", x, y);
        return;
    }

    setBoardCell(b, size, x, y, newColor);

    if (x > 0)
        floodBoard(b, size, oldColor, newColor, x - 1, y);
    if (x < size - 1)
        floodBoard(b, size, oldColor, newColor, x + 1, y);
    if (y > 0)
        floodBoard(b, size, oldColor, newColor, x, y - 1);
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