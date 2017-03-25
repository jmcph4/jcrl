/*
 * unit_stack.h
 *
 * Declarations of unit tests for the singly-linked lists
 * implementation. For unit test definitions, see unit_stack.c.
*/
#include "stack.h"

#define UNIT_STACK_NUM_TESTS 20

/* Initialisation */
bool test_stack_init_normal(void);
bool test_stack_init_null_params(void);

bool test_stack_free_normal(void);
bool test_stack_free_null_params(void);

/* Equality */
bool test_stack_equal_normal(void);
bool test_stack_equal_null_params(void);
bool test_stack_equal_unequal_stacks(void);
bool test_stack_equal_same_stacks(void);

/* Access */
bool test_stack_peek_normal(void);
bool test_stack_peek_null_params(void);
bool test_stack_peek_empty_stack(void);

bool test_stack_depth_normal(void);
bool test_stack_depth_null_params(void);
bool test_stack_depth_empty_stack(void);

/* Operations */
bool test_stack_push_normal(void);
bool test_stack_push_null_params(void);
bool test_stack_push_empty_stack(void);

bool test_stack_pop_normal(void);
bool test_stack_pop_null_params(void);
bool test_stack_pop_empty_stack(void);

