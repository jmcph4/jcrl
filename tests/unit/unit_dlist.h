/*
 * unit_dlist.h
 *
 * Declarations of unit tests for the singly-linked lists
 * implementation. For unit test definitions, see unit_dlist.c.
*/
#include "dlist.h"

#define UNIT_DLIST_NUM_TESTS 48

/* Initialisation */
bool test_dlist_init_normal(void);
bool test_dlist_init_null_params(void);

bool test_dlist_free_normal(void);
bool test_dlist_free_null_params(void);
bool test_dlist_free_empty_list(void);

/* Equality */
bool test_dlist_equal_normal(void);
bool test_dlist_equal_null_params(void);
bool test_dlist_equal_unequal_lists(void);
bool test_dlist_equal_same_lists(void);

/* Membership */
bool test_dlist_in_normal(void);
bool test_dlist_in_null_params(void);
bool test_dlist_in_empty_list(void);

/* Access */
bool test_dlist_get_normal(void);
bool test_dlist_get_null_params(void);
bool test_dlist_get_out_of_bounds(void);

bool test_dlist_set_normal(void);
bool test_dlist_set_null_params(void);
bool test_dlist_set_out_of_bounds(void);

bool test_dlist_length_normal(void);
bool test_dlist_length_null_params(void);
bool test_dlist_length_empty_list(void);

/* Operations */
bool test_dlist_insert_normal(void);
bool test_dlist_insert_null_params(void);
bool test_dlist_insert_out_of_bounds(void);
bool test_dlist_insert_new_head(void);
bool test_dlist_insert_new_tail(void);
bool test_dlist_insert_empty_list(void);

bool test_dlist_remove_normal(void);
bool test_dlist_remove_null_params(void);
bool test_dlist_remove_out_of_bounds(void);
bool test_dlist_remove_new_head(void);
bool test_dlist_remove_new_tail(void);

bool test_dlist_traverse_normal(void);
bool test_dlist_traverse_null_params(void);
bool test_dlist_traverse_empty_list(void);
bool test_dlist_traverse_reverse(void);

/* Utilities */
bool test_dlist_append_normal(void);
bool test_dlist_append_null_params(void);
bool test_dlist_append_empty_list(void);

bool test_dlist_concatenate_normal(void);
bool test_dlist_concatenate_null_params(void);
bool test_dlist_concatenate_empty_lists(void);
bool test_dlist_concatenate_left_empty_list(void);
bool test_dlist_concatenate_right_empty_list(void);

bool test_dlist_swap_normal(void);
bool test_dlist_swap_null_params(void);
bool test_dlist_swap_out_of_bounds(void);
bool test_dlist_swap_same_index(void);
