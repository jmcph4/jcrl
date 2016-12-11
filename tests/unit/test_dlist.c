/*
 * test_dlist.c
 * 
 * Test executable for the singly-linked list implementation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "unit_dlist.h"

/* test names */
const char* tests[UNIT_DLIST_NUM_TESTS] = {
                                    "test_dlist_init_normal",
                                    "test_dlist_init_null_params",
                                    "test_dlist_free_normal",
                                    "test_dlist_free_null_params",
                                    "test_dlist_free_empty_list",
                                    "test_dlist_equal_normal",
                                    "test_dlist_equal_null_params",
                                    "test_dlist_equal_unequal_lists",
                                    "test_dlist_equal_same_lists",
                                    "test_dlist_in_normal",
                                    "test_dlist_in_null_params",
                                    "test_dlist_in_empty_list",
                                    "test_dlist_get_normal",
                                    "test_dlist_get_null_params",
                                    "test_dlist_get_out_of_bounds",
                                    "test_dlist_set_normal",
                                    "test_dlist_set_null_params",
                                    "test_dlist_set_out_of_bounds",
                                    "test_dlist_length_normal",
                                    "test_dlist_length_null_params",
                                    "test_dlist_length_empty_list",
                                    "test_dlist_insert_normal",
                                    "test_dlist_insert_null_params",
                                    "test_dlist_insert_out_of_bounds",
                                    "test_dlist_insert_new_head",
                                    "test_dlist_insert_new_tail",
                                    "test_dlist_insert_empty_list",
                                    "test_dlist_remove_normal",
                                    "test_dlist_remove_null_params",
                                    "test_dlist_remove_out_of_bounds",
                                    "test_dlist_remove_new_head",
                                    "test_dlist_remove_new_tail",
                                    "test_dlist_traverse_normal",
                                    "test_dlist_traverse_null_params",
                                    "test_dlist_traverse_empty_list",
                                    "test_dlist_traverse_reverse",
                                    "test_dlist_append_normal",
                                    "test_dlist_append_null_params",
                                    "test_dlist_append_empty_list",
                                    "test_dlist_concatenate_normal",
                                    "test_dlist_concatenate_null_params",
                                    "test_dlist_concatenate_empty_lists",
                                    "test_dlist_concatenate_left_empty_list",
                                    "test_dlist_concatenate_right_empty_list",
                                    "test_dlist_swap_normal",
                                    "test_dlist_swap_null_params",
                                    "test_dlist_swap_out_of_bounds",
                                    "test_dlist_swap_same_index"
                                    };

int main(void)
{
    unsigned int t = 0;
    bool results[UNIT_DLIST_NUM_TESTS];
    memset(results, 0, sizeof(bool) * UNIT_DLIST_NUM_TESTS);
    
    /* Initialisation */
    results[t] = test_dlist_init_normal();
    t++;
    results[t] = test_dlist_init_null_params();
    t++;
    
    results[t] = test_dlist_free_normal();
    t++;
    results[t] = test_dlist_free_null_params();
    t++;
    results[t] = test_dlist_free_empty_list();
    t++;
    
    /* Equality */
    results[t] = test_dlist_equal_normal();
    t++;
    results[t] = test_dlist_equal_null_params();
    t++;
    results[t] = test_dlist_equal_unequal_lists();
    t++;
    results[t] = test_dlist_equal_same_lists();
    t++;
    
    /* Membership */
    results[t] = test_dlist_in_normal();
    t++;
    results[t] = test_dlist_in_null_params();
    t++;
    results[t] = test_dlist_in_empty_list();
    t++;
    
    /* Access */
    results[t] = test_dlist_get_normal();
    t++;
    results[t] = test_dlist_get_null_params();
    t++;
    results[t] = test_dlist_get_out_of_bounds();
    t++;
    
    results[t] = test_dlist_set_normal();
    t++;
    results[t] = test_dlist_set_null_params();
    t++;
    results[t] = test_dlist_set_out_of_bounds();
    t++;
    
    results[t] = test_dlist_length_normal();
    t++;
    results[t] = test_dlist_length_null_params();
    t++;
    results[t] = test_dlist_length_empty_list();
    t++;
    
    /* Operations */
    results[t] = test_dlist_insert_normal();
    t++;
    results[t] = test_dlist_insert_null_params();
    t++;
    results[t] = test_dlist_insert_out_of_bounds();
    t++;
    results[t] = test_dlist_insert_new_head();
    t++;
    results[t] = test_dlist_insert_new_tail();
    t++;
    results[t] = test_dlist_insert_empty_list();
    t++;
    
    results[t] = test_dlist_remove_normal();
    t++;
    results[t] = test_dlist_remove_null_params();
    t++;
    results[t] = test_dlist_remove_out_of_bounds();
    t++;
    results[t] = test_dlist_remove_new_head();
    t++;
    results[t] = test_dlist_remove_new_tail();
    t++;
    
    results[t] = test_dlist_traverse_normal();
    t++;
    results[t] = test_dlist_traverse_null_params();
    t++;
    results[t] = test_dlist_traverse_empty_list();
    t++;
    results[t] = test_dlist_traverse_reverse();
    t++;
    
    /* Utilities */
    results[t] = test_dlist_append_normal();
    t++;
    results[t] = test_dlist_append_null_params();
    t++;
    results[t] = test_dlist_append_empty_list();
    t++;
    
    results[t] = test_dlist_concatenate_normal();
    t++;
    results[t] = test_dlist_concatenate_null_params();
    t++;
    results[t] = test_dlist_concatenate_empty_lists();
    t++;
    results[t] = test_dlist_concatenate_left_empty_list();
    t++;
    results[t] = test_dlist_concatenate_right_empty_list();
    t++;
    
    results[t] = test_dlist_swap_normal();
    t++;
    results[t] = test_dlist_swap_null_params();
    t++;
    results[t] = test_dlist_swap_out_of_bounds();
    t++;
    results[t] = test_dlist_swap_same_index();
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
