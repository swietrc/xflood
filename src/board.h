#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdint.h>

#define MAX_SIZE   24
#define NB_COLOURS 6


typedef enum cell { R, G, B, Y, O, M } Cell;

typedef struct board {
    size_t size;
    char color;
    char* grid;
} Board;

Board* initBoard(size_t size);
Board* initRandomBoard(size_t size);
char getBoardCell(Board* b, int x, int y);
void setBoardCell(Board* b, int x, int y, char color);
void floodBoard(Board* b, char oldColor, char newColor, int x, int y);
void freeBoard(Board* b);
void debug_displayBoard(Board* b);
// int areSimilarBoards(board b1, board b2, size_t size);

#endif
