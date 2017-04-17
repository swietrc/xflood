#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

#include "../src/solver.h"

void test_Solver_getPossibleColors() {
  Board* b = initBoard(4);
  setGrid(b, (char[16]){
          'R', 'R', 'Y', 'R',
          'G', 'B', 'R', 'R',
          'R', 'R', 'R', 'R',
          'R', 'R', 'R', 'R',
  });
  ColorList* possColors = getPossibleColors(b);
  char current;
  int i;
  while(ColorListForward(possColors, &current)) {
    if(i == 0)
      CU_ASSERT(current == 'Y')
    else if (i == 1)
      CU_ASSERT(current == 'B')
    else if (i == 2)
      CU_ASSERT(current == 'G')
    i++;
  }
  freeBoard(b);
  ColorListDestroy(possColors);
}

void test_Solver_solveBoard() {
  Board* b = initBoard(3);
  setGrid(b, (char[9]){
          'R', 'R', 'R',
          'B', 'O', 'B',
          'M', 'Y', 'O',
  });
  ColorList* bestSol = 0;
  ColorList* crtSol = 0;

  int finalSize = solveBoard(b, &bestSol, &crtSol);
  CU_ASSERT(finalSize == 4);

  char current;
  int i;
  while(ColorListForward(bestSol, &current)) {
    if(i == 0)
      CU_ASSERT(current == 'B')
    else if (i == 1)
      CU_ASSERT(current == 'O')
    else if (i == 2)
      CU_ASSERT(current == 'M')
    else if (i == 3)
      CU_ASSERT(current == 'Y')
    i++;
  }
}

void addAllSolverTests(){
    CU_pSuite pSuite = CU_add_suite("Solver algorithm for a Board structure", NULL, NULL);

    CU_add_test(pSuite, "getPossibleColors() should correctly return adjacent colors", test_Solver_getPossibleColors);
    CU_add_test(pSuite, "solveBoard() should return the size of best solution liste to solve the board", test_Solver_solveBoard);
}
