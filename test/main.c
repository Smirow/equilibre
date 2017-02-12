#include "headers/grilleTest.h"
#include <CUnit/Basic.h>


/* The suite init function.
 */
int init_suite_1(void) {
   return 0;
}

/* The suite cleanup function.
 */
int clean_suite_1(void) {
   return 0;
}


int main(void) {
    CU_pSuite suite_grille = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    suite_grille = CU_add_suite("Module Grille", init_suite_1, clean_suite_1);
    if (NULL == suite_grille) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    /* add the tests to the suite */
    if ((NULL == CU_add_test(suite_grille, "test of initMatrix()", test_initMatrix)) ||
    (NULL == CU_add_test(suite_grille, "test of randomMatrix()", test_randomMatrix)) ||
    (NULL == CU_add_test(suite_grille, "test of initFromFile()", test_initFromFile))) {
        CU_cleanup_registry();
        return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
