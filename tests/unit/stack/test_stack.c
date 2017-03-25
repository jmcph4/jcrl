/*
 * test_stack.c
 * 
 * Test executable for the stack implementation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "unit_stack.h"

/* test names */
const char* tests[UNIT_STACK_NUM_TESTS] = {
                                    "test_stack_init_normal",
                                    "test_stack_init_null_params",
                                    "test_stack_free_normal",
                                    "test_stack_free_null_params",
                                    "test_stack_equal_normal",
                                    "test_stack_equal_null_params",
                                    "test_stack_equal_unequal_stacks",
                                    "test_stack_equal_same_stacks",
                                    "test_stack_peek_normal",
                                    "test_stack_peek_null_params",
                                    "test_stack_peek_empty_stack",
                                    "test_stack_depth_normal",
                                    "test_stack_depth_null_params",
                                    "test_stack_depth_empty_stack",
                                    "test_stack_push_normal",
                                    "test_stack_push_null_params",
                                    "test_stack_push_empty_stack",
                                    "test_stack_pop_normal",
                                    "test_stack_pop_null_params",
                                    "test_stack_pop_empty_stack"
                                    };

int main(void)
{
    unsigned int t = 0;
    bool results[UNIT_STACK_NUM_TESTS];
    memset(results, 0, sizeof(bool) * UNIT_STACK_NUM_TESTS);
    
    /* Initialisation */
    results[t] = test_stack_init_normal();
    t++;
    results[t] = test_stack_init_null_params();
    t++;
    
    results[t] = test_stack_free_normal();
    t++;
    results[t] = test_stack_free_null_params();
    t++;
    
    /* Equality */
    results[t] = test_stack_equal_normal();
    t++;
    results[t] = test_stack_equal_null_params();
    t++;
    results[t] = test_stack_equal_unequal_stacks();
    t++;
    results[t] = test_stack_equal_same_stacks();
    t++;
    
    /* Access */
    results[t] = test_stack_peek_normal();
    t++;
    results[t] = test_stack_peek_null_params();
    t++;
    results[t] = test_stack_peek_empty_stack();
    t++;
    
    results[t] = test_stack_depth_normal();
    t++;
    results[t] = test_stack_depth_null_params();
    t++;
    results[t] = test_stack_depth_empty_stack();
    t++;
    
    /* Operations */
    results[t] = test_stack_push_normal();
    t++;
    results[t] = test_stack_push_null_params();
    t++;
    results[t] = test_stack_push_empty_stack();
    t++;
    
    results[t] = test_stack_pop_normal();
    t++;
    results[t] = test_stack_pop_null_params();
    t++;
    results[t] = test_stack_pop_empty_stack();
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
