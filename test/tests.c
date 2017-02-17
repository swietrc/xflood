#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

#include "../src/board.h"

void test_Board_initBoard() {
    const size_t BSIZE = 3;
    Board* b = initBoard(BSIZE);
    CU_ASSERT_PTR_NOT_NULL(b);

    freeBoard(b);
}

void test_Board_initRandom() {
    const size_t BSIZE = 3;
    Board* b1 = initRandomBoard(BSIZE);
    Board* b2 = initRandomBoard(BSIZE);
    CU_ASSERT_FALSE(areSimilarBoards(b1, b2));

    freeBoard(b1);
    freeBoard(b2);
}

void test_Board_floodBoard() {
    const char c1 = colours[0];
    const char c2 = colours[1];
    const char c3 = colours[2];
    #define NB_OF_GRIDS 6
    #define GRID_SIZE 3
    char gridsInOrder[NB_OF_GRIDS][GRID_SIZE * GRID_SIZE] = {
            {
                    c1, c2, c3,
                    c1, c3, c1,
                    c1, c3, c2
            }, // choosing c2...
            {
                    c2, c2, c3,
                    c2, c3, c1,
                    c2, c3, c2
            },
            // choosing c1...
            {
                    c1, c1, c3,
                    c1, c3, c1,
                    c1, c3, c2
            },
            // choosing c3...
            {
                    c3, c3, c3,
                    c3, c3, c1,
                    c3, c3, c2
            },
            // choosing c1...
            {
                    c1, c1, c1,
                    c1, c1, c1,
                    c1, c1, c2
            },
            // choosing c2...
            {
                    c2, c2, c2,
                    c2, c2, c2,
                    c2, c2, c2
            },
    };
    const char colorChoicesInOrder[NB_OF_GRIDS-1] = {c2, c1, c3, c1, c2};
    Board* b1 = initBoard(GRID_SIZE);
    setGrid(b1, gridsInOrder[0]);
    Board* b2 = initBoard(GRID_SIZE);
    char oldColor = getBoardCell(b1, 0, 0);
    char newColor;

    for(unsigned int gridNumber=1; gridNumber<NB_OF_GRIDS; gridNumber++){
        newColor = colorChoicesInOrder[gridNumber-1];
        setGrid(b2, gridsInOrder[gridNumber]);
        floodBoard(b1, oldColor, newColor, 0, 0);
        CU_ASSERT(areSimilarBoards(b1, b2));
        oldColor = newColor;
        b1 = b2;
    }

    free(b1);
    free(b2);
}

void test_Board_getBoardCell(){
    Board* b = initBoard(3);
    char c1 = colours[0];
    char c2 = colours[1];
    setGrid(b, (char[9]) {
            c1, c2, c1,
            c2, c2, c1,
            c1, c2, c1
    });

    CU_ASSERT(getBoardCell(b, 0, 0) == c1);
    CU_ASSERT(getBoardCell(b, 1, 0) == c2);

    free(b);
}

void test_Board_setBoardCell(){
    Board* b = initBoard(3);
    char c1 = colours[0];
    char c2 = colours[1];
    setGrid(b, (char[9]){
            c1, c2, c1,
            c2, c2, c1,
            c1, c2, c1
    });

    setBoardCell(b, 2, 0, c2);
    CU_ASSERT(getBoardCell(b, 2, 0) == c2);

    free(b);
}

void test_Board_isBoardOneColored() {
    Board* b1 = initBoard(3);
    Board* b2 = initBoard(3);

    char c1 = colours[0];
    char c2 = colours[1];
    setGrid(b1, (char[9]){
            c1, c2, c1,
            c2, c2, c1,
            c1, c2, c1
    });

    setGrid(b2, (char[9]){
            c1, c1, c1,
            c1, c1, c1,
            c1, c1, c1
    });

    CU_ASSERT(isBoardOneColored(b1) == false);
    CU_ASSERT(isBoardOneColored(b2));

    free(b1);
    free(b2);
}


int main() {
    srand(time(NULL));
    CU_pSuite pSuite = NULL;
    CU_initialize_registry();

    pSuite = CU_add_suite("Testing elementary data structure and operations on them", NULL, NULL);

    CU_add_test(pSuite, "initBoard() should return a non null pointer to a Cell", test_Board_initBoard);
    CU_add_test(pSuite, "initRandomBoard() should produce a different board each time it is executed", test_Board_initRandom);
    CU_add_test(pSuite, "floodBoard() should flood correctly", test_Board_floodBoard);
    CU_add_test(pSuite, "getBoardCell() should return the correct value at a given coordinate pair", test_Board_getBoardCell);
    CU_add_test(pSuite, "setBoardCell() should set the correct value on grid at given X Y coords", test_Board_setBoardCell);
    CU_add_test(pSuite, "isBoardOneColored() should return true if the board is one-colored", test_Board_isBoardOneColored);


    // output to stdout
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // automated mode (output to xml)
    CU_set_output_filename("allTests");
    CU_automated_run_tests();

    CU_cleanup_registry();
    return 0;
}