/*
 * test_isort.c
 * 
 * Test executable for the insertion sort implementation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "unit_isort.h"

/* test names */
const char* tests[UNIT_ISORT_NUM_TESTS] = {
                                    "test_isort_normal",
                                    "test_isort_null_params",
                                    "test_isort_empty_list"
                                    };

int main(void)
{
    unsigned int t = 0;
    bool results[UNIT_ISORT_NUM_TESTS];
    memset(results, 0, sizeof(bool) * UNIT_ISORT_NUM_TESTS);
    
    results[t] = test_isort_normal();
    t++;
    results[t] = test_isort_null_params();
    t++;
    results[t] = test_isort_empty_list();
    t++;
    
    /* check for test failure */
    for(unsigned int i=0;i<t;i++)
    {
        if(results[i])
        {
            printf("TEST %s: PASS\n", tests[i]);
        }
        else
        {
            printf("!TEST %s: FAIL\n", tests[i]);
        }
    }
    
    return EXIT_SUCCESS;
}
