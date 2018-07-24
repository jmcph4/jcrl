/*
 * test_list.c
 * 
 * Test executable for the list implementation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "unit_list.h"

/* test names */
const char* tests[UNIT_LIST_NUM_TESTS] = {
                                    "test_list_init_normal",
                                    "test_list_init_null_params",
                                    "test_list_free_normal",
                                    "test_list_free_null_params",
                                    "test_list_free_empty_list",
                                    "test_list_equal_normal",
                                    "test_list_equal_null_params",
                                    "test_list_equal_unequal_lists",
                                    "test_list_equal_same_lists",
                                    "test_list_in_normal",
                                    "test_list_in_null_params",
                                    "test_list_in_empty_list",
                                    "test_list_get_normal",
                                    "test_list_get_null_params",
                                    "test_list_get_out_of_bounds",
                                    "test_list_set_normal",
                                    "test_list_set_null_params",
                                    "test_list_set_out_of_bounds",
                                    "test_list_length_normal",
                                    "test_list_length_null_params",
                                    "test_list_length_empty_list",
                                    "test_list_insert_normal",
                                    "test_list_insert_null_params",
                                    "test_list_insert_out_of_bounds",
                                    "test_list_insert_new_head",
                                    "test_list_insert_new_tail",
                                    "test_list_insert_empty_list",
                                    "test_list_remove_normal",
                                    "test_list_remove_null_params",
                                    "test_list_remove_out_of_bounds",
                                    "test_list_remove_new_head",
                                    "test_list_remove_new_tail",
                                    "test_list_traverse_normal",
                                    "test_list_traverse_null_params",
                                    "test_list_traverse_empty_list",
                                    "test_list_traverse_reverse",
                                    "test_list_append_normal",
                                    "test_list_append_null_params",
                                    "test_list_append_empty_list",
                                    "test_list_concatenate_normal",
                                    "test_list_concatenate_null_params",
                                    "test_list_concatenate_empty_lists",
                                    "test_list_concatenate_left_empty_list",
                                    "test_list_concatenate_right_empty_list",
                                    "test_list_swap_normal",
                                    "test_list_swap_null_params",
                                    "test_list_swap_out_of_bounds",
                                    "test_list_swap_same_index",
                                    "test_list_find_normal",
                                    "test_list_find_null_params",
                                    "test_list_find_not_found",
                                    "test_list_find_empty_list",
                                    "test_list_find_duplicates",
                                    "test_list_count_normal",
                                    "test_list_count_null_params",
                                    "test_list_count_not_found",
                                    "test_list_minmax_normal",
                                    "test_list_minmax_null_params",
                                    "test_list_minmax_empty",
                                    "test_list_argminmax_normal",
                                    "test_list_argminmax_null_params",
                                    "test_list_argminmax_empty",
                                    };

int main(void)
{
    unsigned int t = 0;
    bool results[UNIT_LIST_NUM_TESTS];
    memset(results, 0, sizeof(bool) * UNIT_LIST_NUM_TESTS);
    
    /* Initialisation */
    results[t] = test_list_init_normal();
    t++;
    results[t] = test_list_init_null_params();
    t++;
    
    results[t] = test_list_free_normal();
    t++;
    results[t] = test_list_free_null_params();
    t++;
    results[t] = test_list_free_empty_list();
    t++;
    
    /* Equality */
    results[t] = test_list_equal_normal();
    t++;
    results[t] = test_list_equal_null_params();
    t++;
    results[t] = test_list_equal_unequal_lists();
    t++;
    results[t] = test_list_equal_same_lists();
    t++;
    
    /* Membership */
    results[t] = test_list_in_normal();
    t++;
    results[t] = test_list_in_null_params();
    t++;
    results[t] = test_list_in_empty_list();
    t++;
    
    /* Access */
    results[t] = test_list_get_normal();
    t++;
    results[t] = test_list_get_null_params();
    t++;
    results[t] = test_list_get_out_of_bounds();
    t++;
    
    results[t] = test_list_set_normal();
    t++;
    results[t] = test_list_set_null_params();
    t++;
    results[t] = test_list_set_out_of_bounds();
    t++;
    
    results[t] = test_list_length_normal();
    t++;
    results[t] = test_list_length_null_params();
    t++;
    results[t] = test_list_length_empty_list();
    t++;
    
    /* Operations */
    results[t] = test_list_insert_normal();
    t++;
    results[t] = test_list_insert_null_params();
    t++;
    results[t] = test_list_insert_out_of_bounds();
    t++;
    results[t] = test_list_insert_new_head();
    t++;
    results[t] = test_list_insert_new_tail();
    t++;
    results[t] = test_list_insert_empty_list();
    t++;
    
    results[t] = test_list_remove_normal();
    t++;
    results[t] = test_list_remove_null_params();
    t++;
    results[t] = test_list_remove_out_of_bounds();
    t++;
    results[t] = test_list_remove_new_head();
    t++;
    results[t] = test_list_remove_new_tail();
    t++;
    
    results[t] = test_list_traverse_normal();
    t++;
    results[t] = test_list_traverse_null_params();
    t++;
    results[t] = test_list_traverse_empty_list();
    t++;
    results[t] = test_list_traverse_reverse();
    t++;
    
    /* Utilities */
    results[t] = test_list_append_normal();
    t++;
    results[t] = test_list_append_null_params();
    t++;
    results[t] = test_list_append_empty_list();
    t++;
    
    results[t] = test_list_concatenate_normal();
    t++;
    results[t] = test_list_concatenate_null_params();
    t++;
    results[t] = test_list_concatenate_empty_lists();
    t++;
    results[t] = test_list_concatenate_left_empty_list();
    t++;
    results[t] = test_list_concatenate_right_empty_list();
    t++;
    
    results[t] = test_list_swap_normal();
    t++;
    results[t] = test_list_swap_null_params();
    t++;
    results[t] = test_list_swap_out_of_bounds();
    t++;
    results[t] = test_list_swap_same_index();
    t++;
    
    results[t] = test_list_find_normal();
    t++;
    results[t] = test_list_find_null_params();
    t++;
    results[t] = test_list_find_not_found();
    t++;
    results[t] = test_list_find_empty_list();
    t++;
    results[t] = test_list_find_duplicates();
    t++;
    
    results[t] = test_list_count_normal();
    t++;
    results[t] = test_list_count_null_params();
    t++;
    results[t] = test_list_count_not_found();
    t++;

    results[t] = test_list_minmax_normal();
    t++;
    results[t] = test_list_minmax_null_params();
    t++;
    results[t] = test_list_minmax_empty();
    t++;
   
    results[t] = test_list_argminmax_normal();
    t++;
    results[t] = test_list_argminmax_null_params();
    t++;
    results[t] = test_list_argminmax_empty();
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
