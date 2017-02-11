#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdint.h>

#define MAX_SIZE   24
#define NB_COLOURS 6

typedef enum cell { R, G, B, Y, O, M } Cell;
typedef Cell* board;

board initBoard(int);
board initRandomBoard(int);
Cell getBoardCell(board b, size_t size, int x, int y);
void setBoardCell(board b, size_t size, int x, int y, Cell color);
void floodBoard(board b, size_t size, Cell oldColor, Cell newColor, int x, int y);
void freeBoard(board b);
void debug_displayBoard(size_t, board);
int areSimilarBoards(board b1, board b2, size_t size);

#endif
