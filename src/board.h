#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdint.h>
#include <stdbool.h>

#define MAX_SIZE   24
#define NB_COLOURS 6

typedef struct board Board;

extern const char colours[NB_COLOURS];

Board* initBoard(size_t size);
Board* initRandomBoard(size_t size);
char getBoardCell(Board* b, int x, int y);
void setBoardCell(Board* b, int x, int y, char color);
void floodBoard(Board* b, char oldColor, char newColor, int x, int y);
void freeBoard(Board* b);
void debug_displayBoard(Board* b);
bool areSimilarBoards(Board* b1, Board* b2);
bool isBoardOneColored(Board* b);

#endif
