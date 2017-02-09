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

 int main() {
    board b = initRandomBoard(24);
    debug_displayBoard(24, b); 
    floodBoard(b, 24, G, B, 0, 0);
    printf("\n");
    printf("\n");
    printf("\n");
    debug_displayBoard(24, b); 
    floodBoard(b, 24, B, G, 0, 0);
    floodBoard(b, 24, G, B, 0, 0);
    printf("\n");
    printf("\n");
    printf("\n");
    debug_displayBoard(24, b); 

    freeBoard(b);
}
