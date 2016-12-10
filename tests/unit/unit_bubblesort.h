/*
 * unit_bubblesort.h
 *
 * Declarations of unit tests for the bubblesort implementation. For unit test 
 * definitions, see unit_bubblesort.c.
*/
#include "bubblesort.h"

#define UNIT_BUBBLESORT_NUM_TESTS 6

bool test_bubblesort_slist_normal(void);
bool test_bubblesort_slist_null_params(void);
bool test_bubblesort_slist_empty_list(void);

bool test_bubblesort_dlist_normal(void);
bool test_bubblesort_dlist_null_params(void);
bool test_bubblesort_dlist_empty_list(void);
