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
  CU_ASSERT(ColorListIsIn(possColors, 'Y'));
  CU_ASSERT(ColorListIsIn(possColors, 'B'));
  CU_ASSERT(ColorListIsIn(possColors, 'G'));
  freeBoard(b);
  ColorListDestroy(possColors);
}

void test_Solver_getColoredAreaSize() {
  Board* b = initBoard(4);
  setGrid(b, (char[16]){
          'B', 'B', 'Y', 'R',
          'B', 'B', 'B', 'R',
          'R', 'B', 'R', 'R',
          'R', 'R', 'R', 'R',
  });

  bool* visitedTiles = calloc(getBoardSize(b) * getBoardSize(b), sizeof(bool)); // Keep track of visited tiles

  size_t s = 0;
  getColoredAreaSize(b, visitedTiles, 0, 0, &s);
  
  CU_ASSERT(s == 6);

}

void test_Solver_solveBoard() {
  Board* b = initBoard(3);
  setGrid(b, (char[9]){
          'R', 'R', 'R',
          'B', 'O', 'B',
          'M', 'Y', 'O',
  });
  ColorList* bestSol = ColorListCreateEmpty();
  ColorList* crtSol = ColorListCreateEmpty();

  int finalSize = solveBoard(b, bestSol, crtSol);
  CU_ASSERT(finalSize == 4);

  char current;
  int i = 0;

  while(ColorListForward(bestSol, &current)) {
    switch (i){
      case 0 : CU_ASSERT(current == 'B'); break;
      case 1 : CU_ASSERT(current == 'O'); break;
      case 2 : CU_ASSERT(current == 'M' || current ==  'Y'); break;
      case 3 : CU_ASSERT(current == 'Y' || current == 'M'); break;
    }
    i++;
  }

  ColorListDestroy(crtSol);
  ColorListDestroy(bestSol);
  freeBoard(b);
}

void test_Solver_solveBoardEfficient() {
  Board* b = initBoard(3);
  setGrid(b, (char[9]){
          'R', 'R', 'R',
          'B', 'O', 'B',
          'M', 'Y', 'O',
  });
  ColorList* solution = ColorListCreateEmpty();

  size_t solSize = solveBoardEfficient(b, solution);

  CU_ASSERT(solSize == 4);

  char current;
  int i = 0;
  while(ColorListForward(solution, &current)) {
    switch (i){
      case 0 : CU_ASSERT(current == 'B'); break;
      case 1 : CU_ASSERT(current == 'O'); break;
      case 2 : CU_ASSERT(current == 'M' || current ==  'Y'); break;
      case 3 : CU_ASSERT(current == 'Y' || current == 'M'); break;
    }
    i++;
  }

}

void addAllSolverTests(){
    CU_pSuite pSuite = CU_add_suite("Solver algorithm for a Board structure", NULL, NULL);

    CU_add_test(pSuite, "getPossibleColors() should correctly return adjacent colors", test_Solver_getPossibleColors);
    CU_add_test(pSuite, "solveBoard() should output an optimal solution to solve the board and return the size of the latter", test_Solver_solveBoard);
    CU_add_test(pSuite, "getColoredAreaSize() should output the size of the top-left colored area", test_Solver_getColoredAreaSize);
    CU_add_test(pSuite, "solveBoardEfficient() should output a solution to solve the board in < 1s and return its size", test_Solver_solveBoardEfficient);
}
