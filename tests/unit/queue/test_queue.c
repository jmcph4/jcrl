/*
 * test_queue.c
 * 
 * Test executable for the queue implementation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "unit_queue.h"

/* test names */
const char* tests[UNIT_QUEUE_NUM_TESTS] = {
                                    "test_queue_init_normal",
                                    "test_queue_init_null_params",
                                    "test_queue_free_normal",
                                    "test_queue_free_null_params",
                                    "test_queue_free_empty_queue",
                                    "test_queue_equal_normal",
                                    "test_queue_equal_null_params",
                                    "test_queue_equal_unequal_queues",
                                    "test_queue_equal_same_queues",
                                    "test_queue_peek_normal",
                                    "test_queue_peek_null_params",
                                    "test_queue_peek_empty_queue",
                                    "test_queue_length_normal",
                                    "test_queue_length_null_params",
                                    "test_queue_length_empty_queue",
                                    "test_queue_push_normal",
                                    "test_queue_push_null_params",
                                    "test_queue_push_empty_queue",
                                    "test_queue_pop_normal",
                                    "test_queue_pop_null_params",
                                    "test_queue_pop_empty_queue"
                                    };

int main(void)
{
    unsigned int t = 0;
    bool results[UNIT_QUEUE_NUM_TESTS];
    memset(results, 0, sizeof(bool) * UNIT_QUEUE_NUM_TESTS);
    
    /* Initialisation */
    results[t] = test_queue_init_normal();
    t++;
    results[t] = test_queue_init_null_params();
    t++;
    
    results[t] = test_queue_free_normal();
    t++;
    results[t] = test_queue_free_null_params();
    t++;
    results[t] = test_queue_free_empty_queue();
    t++;
    
    /* Equality */
    results[t] = test_queue_equal_normal();
    t++;
    results[t] = test_queue_equal_null_params();
    t++;
    results[t] = test_queue_equal_unequal_queues();
    t++;
    results[t] = test_queue_equal_same_queues();
    t++;
    
    /* Access */
    results[t] = test_queue_peek_normal();
    t++;
    results[t] = test_queue_peek_null_params();
    t++;
    results[t] = test_queue_peek_empty_queue();
    t++;
    
    results[t] = test_queue_length_normal();
    t++;
    results[t] = test_queue_length_null_params();
    t++;
    results[t] = test_queue_length_empty_queue();
    t++;
    
    /* Operations */
    results[t] = test_queue_push_normal();
    t++;
    results[t] = test_queue_push_null_params();
    t++;
    results[t] = test_queue_push_empty_queue();
    t++;
    
    results[t] = test_queue_pop_normal();
    t++;
    results[t] = test_queue_pop_null_params();
    t++;
    results[t] = test_queue_pop_empty_queue();
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
