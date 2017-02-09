#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdint.h>

#define MAX_SIZE   24
#define NB_COLOURS 6

typedef enum cell { R, G, B, Y, O, M } Cell;
typedef Cell* board;

board initBoard(int);
board initRandomBoard(int);

void debug_displayBoard(size_t, board);

#endif
