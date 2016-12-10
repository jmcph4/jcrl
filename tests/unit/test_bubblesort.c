/*
 * test_bubblesort.c
 * 
 * Test executable for the bubblesort implementation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "unit_bubblesort.h"

/* test names */
const char* tests[UNIT_BUBBLESORT_NUM_TESTS] = {
                                    "test_bubblesort_slist_normal",
                                    "test_bubblesort_slist_null_params",
                                    "test_bubblesort_slist_empty_list",
                                    "test_bubblesort_dlist_normal",
                                    "test_bubblesort_dlist_null_params",
                                    "test_bubblesort_dlist_empty_list"
                                    };

int main(void)
{
    unsigned int t = 0;
    bool results[UNIT_BUBBLESORT_NUM_TESTS];
    memset(results, 0, sizeof(bool) * UNIT_BUBBLESORT_NUM_TESTS);
    
    results[t] = test_bubblesort_slist_normal();
    t++;
    results[t] = test_bubblesort_slist_null_params();
    t++;
    results[t] = test_bubblesort_slist_empty_list();
    t++;
    
    results[t] = test_bubblesort_dlist_normal();
    t++;
    results[t] = test_bubblesort_dlist_null_params();
    t++;
    results[t] = test_bubblesort_dlist_empty_list();
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
