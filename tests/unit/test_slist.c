/*
 * test_slist.c
 * 
 * Test executable for the singly-linked list implementation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "unit_slist.h"

/* test names */
const char* tests[UNIT_SLIST_NUM_TESTS] = {
                                    "test_slist_init_normal",
                                    "test_slist_init_null_params",
                                    "test_slist_free_normal",
                                    "test_slist_free_null_params",
                                    "test_slist_free_empty_list",
                                    "test_slist_equal_normal",
                                    "test_slist_equal_null_params",
                                    "test_slist_equal_unequal_lists",
                                    "test_slist_equal_same_lists",
                                    "test_slist_get_normal",
                                    "test_slist_get_null_params",
                                    "test_slist_get_out_of_bounds",
                                    "test_slist_set_normal",
                                    "test_slist_set_null_params",
                                    "test_slist_set_out_of_bounds",
                                    "test_slist_length_normal",
                                    "test_slist_length_null_params",
                                    "test_slist_length_empty_list",
                                    "test_slist_insert_normal",
                                    "test_slist_insert_null_params",
                                    "test_slist_insert_out_of_bounds",
                                    "test_slist_insert_new_head",
                                    "test_slist_insert_new_tail",
                                    "test_slist_insert_empty_list",
                                    "test_slist_remove_normal",
                                    "test_slist_remove_null_params",
                                    "test_slist_remove_out_of_bounds",
                                    "test_slist_remove_new_head",
                                    "test_slist_remove_new_tail",
                                    "test_slist_traverse_normal",
                                    "test_slist_traverse_null_params",
                                    "test_slist_traverse_empty_list",
                                    "test_slist_append_normal",
                                    "test_slist_append_null_params",
                                    "test_slist_append_empty_list",
                                    "test_slist_concatenate_normal",
                                    "test_slist_concatenate_null_params",
                                    "test_slist_concatenate_empty_lists",
                                    "test_slist_concatenate_left_empty_list",
                                    "test_slist_concatenate_right_empty_list"
                                    };

int main(void)
{
    unsigned int t = 0;
    bool results[UNIT_SLIST_NUM_TESTS];
    memset(results, 0, sizeof(bool) * UNIT_SLIST_NUM_TESTS);
    
    /* Initialisation */
    results[t] = test_slist_init_normal();
    t++;
    results[t] = test_slist_init_null_params();
    t++;
    
    results[t] = test_slist_free_normal();
    t++;
    results[t] = test_slist_free_null_params();
    t++;
    results[t] = test_slist_free_empty_list();
    t++;
    
    /* Equality */
    results[t] = test_slist_equal_normal();
    t++;
    results[t] = test_slist_equal_null_params();
    t++;
    results[t] = test_slist_equal_unequal_lists();
    t++;
    results[t] = test_slist_equal_same_lists();
    t++;
    
    /* Access */
    results[t] = test_slist_get_normal();
    t++;
    results[t] = test_slist_get_null_params();
    t++;
    results[t] = test_slist_get_out_of_bounds();
    t++;
    
    results[t] = test_slist_set_normal();
    t++;
    results[t] = test_slist_set_null_params();
    t++;
    results[t] = test_slist_set_out_of_bounds();
    t++;
    
    results[t] = test_slist_length_normal();
    t++;
    results[t] = test_slist_length_null_params();
    t++;
    results[t] = test_slist_length_empty_list();
    t++;
    
    /* Operations */
    results[t] = test_slist_insert_normal();
    t++;
    results[t] = test_slist_insert_null_params();
    t++;
    results[t] = test_slist_insert_out_of_bounds();
    t++;
    results[t] = test_slist_insert_new_head();
    t++;
    results[t] = test_slist_insert_new_tail();
    t++;
    results[t] = test_slist_insert_empty_list();
    t++;
    
    results[t] = test_slist_remove_normal();
    t++;
    results[t] = test_slist_remove_null_params();
    t++;
    results[t] = test_slist_remove_out_of_bounds();
    t++;
    results[t] = test_slist_remove_new_head();
    t++;
    results[t] = test_slist_remove_new_tail();
    t++;
    
    results[t] = test_slist_traverse_normal();
    t++;
    results[t] = test_slist_traverse_null_params();
    t++;
    results[t] = test_slist_traverse_empty_list();
    t++;
    
    /* Utilities */
    results[t] = test_slist_append_normal();
    t++;
    results[t] = test_slist_append_null_params();
    t++;
    results[t] = test_slist_append_empty_list();
    t++;
    
    results[t] = test_slist_concatenate_normal();
    t++;
    results[t] = test_slist_concatenate_null_params();
    t++;
    results[t] = test_slist_concatenate_empty_lists();
    t++;
    results[t] = test_slist_concatenate_left_empty_list();
    t++;
    results[t] = test_slist_concatenate_right_empty_list();
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
