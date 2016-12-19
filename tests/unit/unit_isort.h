/*
 * unit_isort.h
 *
 * Declarations of unit tests for the insertion sort implementation. For unit
 * test definitions, see unit_isort.c.
*/
#include "isort.h"

#define UNIT_ISORT_NUM_TESTS 6

bool test_isort_slist_normal(void);
bool test_isort_slist_null_params(void);
bool test_isort_slist_empty_list(void);

bool test_isort_dlist_normal(void);
bool test_isort_dlist_null_params(void);
bool test_isort_dlist_empty_list(void);
