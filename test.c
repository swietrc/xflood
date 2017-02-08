#include <stdio.h>
#include <CUnit/Basic.h>

int example() {
    return 2;
}

void test_example() {
    CU_ASSERT(example() == 2);
}

int main() {
    CU_pSuite pSuite = NULL;
    CU_initialize_registry();

    pSuite = CU_add_suite("Suite", NULL, NULL);

    CU_add_test(pSuite, "test de example()", test_example);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
