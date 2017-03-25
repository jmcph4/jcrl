/*
 * unit_isort.h
 *
 * Declarations of unit tests for the insertion sort implementation. For unit
 * test definitions, see unit_isort.c.
*/
#include "isort.h"

#define UNIT_ISORT_NUM_TESTS 3

bool test_isort_normal(void);
bool test_isort_null_params(void);
bool test_isort_empty_list(void);
