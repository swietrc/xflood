#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

#include "boardTests.h"

int main() {
    srand(time(NULL));
    CU_initialize_registry();

    // Adding modules tests
    addAllBoardTests();

    // output to stdout
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // automated mode (output to xml)
    CU_set_output_filename("test/results/allTests");
    CU_automated_run_tests();
    CU_list_tests_to_file();

    CU_cleanup_registry();
    return 0;
}