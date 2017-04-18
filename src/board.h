#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdint.h>
#include <stdbool.h>

#define MAX_SIZE   18
#define NB_COLOURS 6

typedef struct board Board;

extern const char colours[NB_COLOURS];

Board* initBoard(size_t size);
Board* initRandomBoard(size_t size);
Board* initBoardFromFile (size_t size, const char* filePath);
char getBoardCell(Board* b, unsigned int x, unsigned int y);
void setBoardCell(Board* b, unsigned int x, unsigned int y, char color);
void setGrid(Board* b, char* newGrid);
void floodBoard(Board* b, char oldColor, char newColor, unsigned int x, unsigned int y);
void freeBoard(Board* b);
void debug_displayBoard(Board* b);
bool areSimilarBoards(Board* b1, Board* b2);
bool isBoardOneColored(Board* b);
size_t getBoardSize(Board*);
Board* copyBoard(Board*);

#endif
