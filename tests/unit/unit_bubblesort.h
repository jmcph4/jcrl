/*
 * unit_bubblesort.h
 *
 * Declarations of unit tests for the bubblesort implementation. For unit test 
 * definitions, see unit_bubblesort.c.
*/
#include "bubblesort.h"

#define UNIT_BUBBLESORT_NUM_TESTS 3

bool test_bubblesort_normal(void);
bool test_bubblesort_null_params(void);
bool test_bubblesort_empty_list(void);
