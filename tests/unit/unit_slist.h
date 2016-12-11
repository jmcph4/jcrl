/*
 * unit_slist.h
 *
 * Declarations of unit tests for the singly-linked lists
 * implementation. For unit test definitions, see unit_slist.c.
*/
#include "slist.h"

#define UNIT_SLIST_NUM_TESTS 52

/* Initialisation */
bool test_slist_init_normal(void);
bool test_slist_init_null_params(void);

bool test_slist_free_normal(void);
bool test_slist_free_null_params(void);
bool test_slist_free_empty_list(void);

/* Equality */
bool test_slist_equal_normal(void);
bool test_slist_equal_null_params(void);
bool test_slist_equal_unequal_lists(void);
bool test_slist_equal_same_lists(void);

/* Membership */
bool test_slist_in_normal(void);
bool test_slist_in_null_params(void);
bool test_slist_in_empty_list(void);

/* Access */
bool test_slist_get_normal(void);
bool test_slist_get_null_params(void);
bool test_slist_get_out_of_bounds(void);

bool test_slist_set_normal(void);
bool test_slist_set_null_params(void);
bool test_slist_set_out_of_bounds(void);

bool test_slist_length_normal(void);
bool test_slist_length_null_params(void);
bool test_slist_length_empty_list(void);

/* Operations */
bool test_slist_insert_normal(void);
bool test_slist_insert_null_params(void);
bool test_slist_insert_out_of_bounds(void);
bool test_slist_insert_new_head(void);
bool test_slist_insert_new_tail(void);
bool test_slist_insert_empty_list(void);

bool test_slist_remove_normal(void);
bool test_slist_remove_null_params(void);
bool test_slist_remove_out_of_bounds(void);
bool test_slist_remove_new_head(void);
bool test_slist_remove_new_tail(void);

bool test_slist_traverse_normal(void);
bool test_slist_traverse_null_params(void);
bool test_slist_traverse_empty_list(void);

/* Utilities */
bool test_slist_append_normal(void);
bool test_slist_append_null_params(void);
bool test_slist_append_empty_list(void);

bool test_slist_concatenate_normal(void);
bool test_slist_concatenate_null_params(void);
bool test_slist_concatenate_empty_lists(void);
bool test_slist_concatenate_left_empty_list(void);
bool test_slist_concatenate_right_empty_list(void);

bool test_slist_swap_normal(void);
bool test_slist_swap_null_params(void);
bool test_slist_swap_out_of_bounds(void);
bool test_slist_swap_same_index(void);

bool test_slist_find_normal(void);
bool test_slist_find_null_params(void);
bool test_slist_find_not_found(void);
bool test_slist_find_empty_list(void);
bool test_slist_find_duplicates(void);
