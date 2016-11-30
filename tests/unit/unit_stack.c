/*
 * unit_stack.c
 * 
 * Unit tests for the singly-linked list implementation. For test declarations,
 * see unit_stack.h.
 */
#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"
#include "stack.h"
#include "unit_stack.h"

/* Initialisation */
bool test_stack_init_normal(void)
{
    bool pass = false;
    
    Stack stack;
    
    unsigned int res = stack_init(&stack);
    
    stack_free(&stack);
    
    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }
    
    return pass;
}

bool test_stack_init_null_params(void)
{
    bool pass = false;
    
    unsigned int res = stack_init(NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_stack_free_normal(void)
{
    bool pass = false;
    
    Stack stack;
    stack_init(&stack);
    
    unsigned int res = stack_free(&stack);
    
    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }
    
    return pass;
}

bool test_stack_free_null_params(void)
{
    bool pass = false;
    
    unsigned int res = stack_free(NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
        
    return pass;
}

bool test_stack_equal_normal(void)
{
    bool pass = false;
    
    Stack stack_a;
    stack_init(&stack_a);
    
    Stack stack_b;
    stack_init(&stack_b);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    stack_push((void*)a, &stack_a);
    stack_push((void*)a, &stack_b);
    
    bool equal = false;
    unsigned int res = stack_equal(&equal, &stack_a, &stack_b);
    
    stack_free(&stack_a);
    stack_free(&stack_b);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_stack_equal_null_params(void)
{
    bool pass = false;
    
    unsigned int res = stack_equal(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_stack_equal_unequal_stacks(void)
{
    bool pass = false;
    
    Stack stack_a;
    stack_init(&stack_a);
    
    Stack stack_b;
    stack_init(&stack_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    stack_push((void*)a, &stack_a);
    stack_push((void*)b, &stack_b);
    
    bool equal = false;
    unsigned int res = stack_equal(&equal, &stack_a, &stack_b);
    
    stack_free(&stack_a);
    stack_free(&stack_b);
    
    if(res == JCRL_ERR_OK && !equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_stack_equal_same_stacks(void)
{
    bool pass = false;
    
    Stack stack_a;
    stack_init(&stack_a);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    stack_push((void*)a, &stack_a);
    
    bool equal = false;
    unsigned int res = stack_equal(&equal, &stack_a, &stack_a);
    
    stack_free(&stack_a);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

/* Access */
bool test_stack_peek_normal(void)
{
    bool pass = false;
    
    Stack stack;
    stack_init(&stack);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    stack_push((void*)a, &stack);
    
    unsigned int peek = 0;
    
    unsigned int res = stack_peek((void*)&peek, &stack);
    
    stack_free(&stack);
    
    if(res == JCRL_ERR_OK && peek == a)
    {
        pass = true;
    }
    
    return pass;
}

bool test_stack_peek_null_params(void)
{
    bool pass = false;
    
    unsigned int res = stack_peek(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_stack_peek_empty_stack(void)
{
    bool pass = false;
    
    Stack stack;
    stack_init(&stack);
    
    unsigned int peek = 0;
    unsigned int res = stack_peek((void*)&peek, &stack);
    
    stack_free(&stack);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS && peek == 0)
    {
        pass = true;
    }
    
    return pass;
}

bool test_stack_depth_normal(void)
{
    bool pass = false;
    
    Stack stack;
    stack_init(&stack);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    stack_push((void*)a, &stack);
    stack_push((void*)a, &stack);
    stack_push((void*)a, &stack);
    
    unsigned int depth = 0;
    unsigned int res = stack_depth(&depth, &stack);
    
    stack_free(&stack);
    
    if(res == JCRL_ERR_OK && depth == 3)
    {
        pass = true;
    }
    
    return pass;
}

bool test_stack_depth_null_params(void)
{
    bool pass = false;
 
    unsigned int res = stack_depth(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
 
    return pass;
}

bool test_stack_depth_empty_stack(void)
{
    bool pass = false;
    
    Stack stack;
    stack_init(&stack);
    
    unsigned int depth = 0;
    unsigned int res = stack_depth(&depth, &stack);
    
    stack_free(&stack);
    
    if(res == JCRL_ERR_OK && depth == 0)
    {
        pass = true;
    }
    
    return pass;
}

/* Operations */
bool test_stack_push_normal(void)
{
    bool pass = false;
    
    Stack stack;
    stack_init(&stack);
    
    Stack expected_stack;
    stack_init(&expected_stack);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    stack_push((void*)a, &expected_stack);
    stack_push((void*)b, &expected_stack);
    
    stack_push((void*)a, &stack);
    
    unsigned int res = stack_push((void*)b, &stack);
    
    bool equal = false;
    stack_equal(&equal, &stack, &expected_stack);
    
    stack_free(&stack);
    stack_free(&expected_stack);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_stack_push_null_params(void)
{
    bool pass = false;
    
    unsigned int res = stack_push(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_stack_push_empty_stack(void)
{
    bool pass = false;
    
    Stack stack;
    stack_init(&stack);
    
    Stack expected_stack;
    stack_init(&expected_stack);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    stack_push((void*)a, &expected_stack);
    
    unsigned int res = stack_push((void*)a, &stack);
    
    bool equal = false;
    stack_equal(&equal, &stack, &expected_stack);
    
    stack_free(&stack);
    stack_free(&expected_stack);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_stack_pop_normal(void)
{
    bool pass = false;
    
    Stack stack;
    stack_init(&stack);
    
    Stack expected_stack;
    stack_init(&expected_stack);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    stack_push((void*)a, &expected_stack);
    stack_push((void*)b, &expected_stack);
    
    stack_push((void*)a, &stack);
    stack_push((void*)b, &stack);
    stack_push((void*)b, &stack);
    
    unsigned int value = 0;
    unsigned int res = stack_pop((void*)&value, &stack);
    
    bool equal = false;
    stack_equal(&equal, &stack, &expected_stack);
    
    stack_free(&stack);
    stack_free(&expected_stack);
    
    if(res == JCRL_ERR_OK && equal && value == b)
    {
        pass = true;
    }
    
    return pass;
}

bool test_stack_pop_null_params(void)
{
    bool pass = false;
    
    unsigned int res = stack_pop(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_stack_pop_empty_stack(void)
{
    bool pass = false;
    
    Stack stack;
    stack_init(&stack);
    
    Stack expected_stack;
    stack_init(&expected_stack);
    
    unsigned int value = 0;
    unsigned int res = stack_pop((void*)&value, &stack);
    
    bool equal = false;
    stack_equal(&equal, &stack, &expected_stack);
    
    stack_free(&stack);
    stack_free(&expected_stack);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS && equal && value == 0)
    {
        pass = true;
    }
    
    return pass;
}
