/*
 * unit_list.h
 *
 * Declarations of unit tests for list implementation. For unit test 
 * definitions, see unit_list.c.
*/
#include "list.h"

#define UNIT_LIST_NUM_TESTS 62

/* Initialisation */
bool test_list_init_normal(void);
bool test_list_init_null_params(void);

bool test_list_free_normal(void);
bool test_list_free_null_params(void);
bool test_list_free_empty_list(void);

/* Equality */
bool test_list_equal_normal(void);
bool test_list_equal_null_params(void);
bool test_list_equal_unequal_lists(void);
bool test_list_equal_same_lists(void);

/* Membership */
bool test_list_in_normal(void);
bool test_list_in_null_params(void);
bool test_list_in_empty_list(void);

/* Access */
bool test_list_get_normal(void);
bool test_list_get_null_params(void);
bool test_list_get_out_of_bounds(void);

bool test_list_set_normal(void);
bool test_list_set_null_params(void);
bool test_list_set_out_of_bounds(void);

bool test_list_length_normal(void);
bool test_list_length_null_params(void);
bool test_list_length_empty_list(void);

/* Operations */
bool test_list_insert_normal(void);
bool test_list_insert_null_params(void);
bool test_list_insert_out_of_bounds(void);
bool test_list_insert_new_head(void);
bool test_list_insert_new_tail(void);
bool test_list_insert_empty_list(void);

bool test_list_remove_normal(void);
bool test_list_remove_null_params(void);
bool test_list_remove_out_of_bounds(void);
bool test_list_remove_new_head(void);
bool test_list_remove_new_tail(void);

bool test_list_traverse_normal(void);
bool test_list_traverse_null_params(void);
bool test_list_traverse_empty_list(void);
bool test_list_traverse_reverse(void);

/* Utilities */
bool test_list_append_normal(void);
bool test_list_append_null_params(void);
bool test_list_append_empty_list(void);

bool test_list_concatenate_normal(void);
bool test_list_concatenate_null_params(void);
bool test_list_concatenate_empty_lists(void);
bool test_list_concatenate_left_empty_list(void);
bool test_list_concatenate_right_empty_list(void);

bool test_list_swap_normal(void);
bool test_list_swap_null_params(void);
bool test_list_swap_out_of_bounds(void);
bool test_list_swap_same_index(void);

bool test_list_find_normal(void);
bool test_list_find_null_params(void);
bool test_list_find_not_found(void);
bool test_list_find_empty_list(void);
bool test_list_find_duplicates(void);

bool test_list_count_normal(void);
bool test_list_count_null_params(void);
bool test_list_count_not_found(void);

bool test_list_minmax_normal(void);
bool test_list_minmax_null_params(void);
bool test_list_minmax_empty(void);

bool test_list_argminmax_normal(void);
bool test_list_argminmax_null_params(void);
bool test_list_argminmax_empty(void);
