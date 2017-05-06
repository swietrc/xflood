#include <time.h>
#include <stdio.h>
#include "../src/colorList.h"
#include "../src/board.h"
#include "../src/solver.h"

int main(int argc, char** argv) {
  char *changesDesciption = "---";
  if(argc > 1){
    changesDesciption = argv[1];
  }

  Board* b = initBoardFromFile(9, "./test/storage/benchBoard9.data");
  ColorList* sol = ColorListCreateEmpty();
  float startTime = (float)clock()/CLOCKS_PER_SEC;
  solveBoard(b, sol, ColorListCreateEmpty());
  float endTime = (float)clock()/CLOCKS_PER_SEC;
  float timeElapsed = endTime - startTime;

  printf("=================================================================\n");
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime(&rawtime);

  printf("This bench was ran on : %s", asctime (timeinfo));
  printf("These changes have been made since last bench : %s\n", changesDesciption);
  printf("=================================================================\n\n");

  printf("Board to solve : \n\n");
  debug_displayBoard(b);
  printf("\nSolution : \n");

  ColorListPrint(sol);
  printf("\nsolved in %f seconds.\n\n", timeElapsed);

  return 0;
}