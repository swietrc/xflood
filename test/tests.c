#include <stdio.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>
#include "../src/board.h"

void test_Board_initBoard() {
    const size_t BSIZE = 3;
    board b = initBoard(BSIZE);
    CU_ASSERT_PTR_NOT_NULL(b);
}

void test_Board_initRandom() {
    const size_t BSIZE = 3;
    board b1 = initRandomBoard(BSIZE);
    board b2 = initRandomBoard(BSIZE);
    CU_ASSERT_FALSE(areSimilarBoards(b1, b2, BSIZE));
}

void test_Board_floodBoard() {
    board b1 = (Cell[9]){
        R, G, B,
        R, B, Y,
        M, B, Y
    };
    Cell oldColor = getBoardCell(b1, 3, x, y);
    Cell newColor = B;
    board b2 = (Cell[9]){
        B, G, B,
        B, B, Y,
        M, B, Y
    };
    floodBoard(b, 3, oldColor, newColor, 0, 0);
    CU_ASSERT(areSimilarBoards(b, expectedAfter, 3));
}



int main() {
    CU_pSuite pSuite = NULL;
    CU_initialize_registry();

    pSuite = CU_add_suite("Testing elementary data structure and operations on them", NULL, NULL);

    CU_add_test(pSuite, "initBoard() should return a non null pointer to a Cell", test_Board_initBoard);
    CU_add_test(pSuite, "initRandomBoard() should produce a different board each time it is executed", test_Board_initRandom);
    CU_add_test(pSuite, "floodBoard() should flood correctly", test_Board_floodBoard);

    // output to stdout
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // automated mode (output to xml)
    CU_set_output_filename("allTests");
    CU_automated_run_tests();

    CU_cleanup_registry();
    return 0;
}