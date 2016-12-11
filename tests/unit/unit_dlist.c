/*
 * unit_dlist.c
 * 
 * Unit tests for the singly-linked list implementation. For test declarations,
 * see unit_dlist.h.
 */
#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"
#include "dlist.h"
#include "unit_dlist.h"

/* stub callback for testing list traversal */
void trav_clbk(void* data, unsigned int pos)
{
    pos++; /* useless */
    char* new_ptr = (char*)data + pos; /* useless */
    new_ptr++; /* useless */
}

/* Initialisation */
bool test_dlist_init_normal(void)
{
    bool pass = false;
    
    bool equal = false;
    
    /* correct list */
    DList expected_list;
    dlist_init(&expected_list);
    
    /* list we're testing */
    DList list;
    unsigned int res = dlist_init(&list);
    
    dlist_equal(&equal, &list, &expected_list); /* test equality */
    
    dlist_free(&list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_init_null_params(void)
{
    bool pass = false;
    
    unsigned int res = dlist_init(NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_free_normal(void)
{
    bool pass = false;
    
    /* set up list */
    unsigned int a = 12; /* arbitrary value */
    DList list;
    dlist_init(&list);
    dlist_append((void*)a, &list);
    dlist_append((void*)a, &list);
    dlist_append((void*)a, &list);
    
    unsigned int res = dlist_free(&list);
    
    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_free_null_params(void)
{
    bool pass = false;
    
    unsigned int res = dlist_free(NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_free_empty_list(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    unsigned int res = dlist_free(&list);
    
    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }
    
    return pass;
}

/* Equality */
bool test_dlist_equal_normal(void)
{
    bool pass = false;
    
    DList list_a;
    dlist_init(&list_a);
    
    DList list_b;
    dlist_init(&list_b);
    
    /* arbitrary numbers to insert */
    unsigned int a = 0;
    unsigned int b = 1;
    
    /* set up first list */
    dlist_append((void*)a, &list_a);
    dlist_append((void*)b, &list_a);
    dlist_append((void*)b, &list_a);
    
    /* set up second list */
    dlist_append((void*)a, &list_b);
    dlist_append((void*)b, &list_b);
    dlist_append((void*)b, &list_b);
    
    bool equal = false;
    
    unsigned int res = dlist_equal(&equal, &list_a, &list_b);
    
    dlist_free(&list_a);
    dlist_free(&list_b);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_equal_null_params(void)
{
    bool pass = false;
    
    unsigned int res = dlist_equal(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_equal_unequal_lists(void)
{
    bool pass = false;
    
    DList list_a;
    dlist_init(&list_a);
    
    DList list_b;
    dlist_init(&list_b);
    
    /* arbitrary numbers to insert */
    unsigned int a = 0;
    unsigned int b = 1;
    
    /* set up first list */
    dlist_append((void*)a, &list_a);
    dlist_append((void*)b, &list_a);
    dlist_append((void*)b, &list_a);
    
    /* set up second list */
    dlist_append((void*)b, &list_b);
    dlist_append((void*)a, &list_b);
    dlist_append((void*)a, &list_b);
    
    bool equal = false;
    
    unsigned int res = dlist_equal(&equal, &list_a, &list_b);
    
    dlist_free(&list_a);
    dlist_free(&list_b);
    
    if(res == JCRL_ERR_OK && !equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_equal_same_lists(void)
{
    bool pass = false;
    
    DList list_a;
    dlist_init(&list_a);
    
    /* arbitrary numbers to insert */
    unsigned int a = 0;
    unsigned int b = 1;
    
    /* set up test list */
    dlist_append((void*)a, &list_a);
    dlist_append((void*)b, &list_a);
    dlist_append((void*)b, &list_a);
    
    bool equal = false;
    
    unsigned int res = dlist_equal(&equal, &list_a, &list_a);
    
    dlist_free(&list_a);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

/* Membership */
bool test_dlist_in_normal(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    
    dlist_append((void*)a, &list);
    dlist_append((void*)b, &list);
    
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)b, &expected_list);
    
    bool in = false;
    unsigned int res = dlist_in(&in, (void*)a, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    dlist_free(&list);
    dlist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal && in)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_in_null_params(void)
{
    bool pass = false;
    
    unsigned int res = dlist_in(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_in_empty_list(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    bool in = false;
    unsigned int res = dlist_in(&in, (void*)a, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    dlist_free(&list);
    dlist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal && !in)
    {
        pass = true;
    }
    
    return pass;
}

/* Access */
bool test_dlist_get_normal(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    unsigned int a = 12; /* arbitrary number to insert */
    
    dlist_append((void*)a, &list);
    
    unsigned int* val = calloc(1, sizeof(unsigned int)); /* store elem here */
    
    unsigned int res = dlist_get((void*)&val, 0, &list);
    
    dlist_free(&list);
    
    if(res == JCRL_ERR_OK && (unsigned int)val == a)
    {
        pass = true;
    }
    
    free(val);
    
    return pass;
}

bool test_dlist_get_null_params(void)
{
    bool pass = false;

    unsigned int res = dlist_get(NULL, 0, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_get_out_of_bounds(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    unsigned int a = 12; /* arbitrary number to insert */
    
    dlist_append((void*)a, &list);
    
    unsigned int* val = calloc(1, sizeof(unsigned int)); /* store elem here */
    
    unsigned int res = dlist_get((void*)&val, 1, &list);
    
    dlist_free(&list);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS)
    {
        pass = true;
    }
    
    free(val);
    
    return pass;
}

bool test_dlist_set_normal(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    /* list we'll compare results against */
    DList expected_list;
    dlist_init(&expected_list);
    
    /* arbitrary values to insert into list */
    unsigned int a = 12;
    unsigned int b = 3;
    
    /* set up first list */
    dlist_append((void*)a, &list);
    dlist_append((void*)b, &list);
    dlist_append((void*)a, &list);
    
    /* set up expected list */
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)a, &expected_list);
    
    unsigned int res = dlist_set((void*)a, 1, &list);
    
    /* test equality */
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    dlist_free(&list);
    
    return pass;
}

bool test_dlist_set_null_params(void)
{
    bool pass = false;
 
    unsigned int res = dlist_set(NULL, 0, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_set_out_of_bounds(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    /* list we'll compare results against */
    DList expected_list;
    dlist_init(&expected_list);
    
    /* arbitrary values to insert into list */
    unsigned int a = 12;
    unsigned int b = 3;
    
    /* set up first list */
    dlist_append((void*)a, &list);
    dlist_append((void*)b, &list);
    dlist_append((void*)a, &list);
    
    /* set up expected list */
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)a, &expected_list);
    
    unsigned int res = dlist_set((void*)a, 3, &list);
    
    /* test equality */
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS && !equal)
    {
        pass = true;
    }
    
    dlist_free(&list);
    
    return pass;
}

bool test_dlist_length_normal(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    unsigned int a = 12;
    
    dlist_append((void*)a, &list);
    dlist_append((void*)a, &list);
    dlist_append((void*)a, &list);
    
    unsigned int len = 0;
    
    unsigned int res = dlist_length(&len, &list);
    
    dlist_free(&list);
    
    if(res == JCRL_ERR_OK && len == 3)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_length_null_params(void)
{
    bool pass = false;
    
    unsigned int res = dlist_length(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_length_empty_list(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    unsigned int len = 1;
    
    unsigned int res = dlist_length(&len, &list);
    
    dlist_free(&list);
    
    if(res == JCRL_ERR_OK && len == 0)
    {
        pass = true;
    }
    
    return pass;
}

/* Operations */
bool test_dlist_insert_normal(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    
    dlist_append((void*)a, &list);
    dlist_append((void*)c, &list);
    
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)b, &expected_list);
    dlist_append((void*)c, &expected_list);
    
    unsigned int res = dlist_insert((void*)b, 1, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_insert_null_params(void)
{
    bool pass = false;
    
    unsigned int res = dlist_insert(NULL, 0, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_insert_out_of_bounds(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    dlist_append((void*)a, &list);
    dlist_append((void*)b, &list);
    
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)b, &expected_list);
    
    unsigned int res = dlist_insert((void*)b, 3, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_insert_new_head(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    dlist_append((void*)a, &list);
    dlist_append((void*)b, &list);
    
    dlist_append((void*)b, &expected_list);
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)b, &expected_list);
    
    unsigned int res = dlist_insert((void*)b, 0, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_insert_new_tail(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    dlist_append((void*)a, &list);
    dlist_append((void*)b, &list);
    
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)b, &expected_list);
    dlist_append((void*)b, &expected_list);
    
    unsigned int res = dlist_insert((void*)b, 2, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_insert_empty_list(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    dlist_append((void*)a, &expected_list);
    
    unsigned int res = dlist_insert((void*)a, 0, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_remove_normal(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    
    dlist_append((void*)a, &list);
    dlist_append((void*)b, &list);
    dlist_append((void*)c, &list);
    
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)c, &expected_list);
    
    unsigned int res = dlist_remove(1, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_remove_null_params(void)
{
    bool pass = false;
    
    unsigned int res = dlist_remove(0, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_remove_out_of_bounds(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    dlist_append((void*)a, &list);
    dlist_append((void*)b, &list);
    
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)b, &expected_list);
    
    unsigned int res = dlist_remove(2, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_remove_new_head(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    
    dlist_append((void*)c, &list);
    dlist_append((void*)a, &list);
    dlist_append((void*)b, &list);
    
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)b, &expected_list);
    
    unsigned int res = dlist_remove(0, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_remove_new_tail(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    
    dlist_append((void*)a, &list);
    dlist_append((void*)b, &list);
    dlist_append((void*)c, &list);
    
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)b, &expected_list);
    
    unsigned int res = dlist_remove(2, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_traverse_normal(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    unsigned int a = 12; /* arbitrary value */
    
    dlist_append((void*)a, &list);
    dlist_append((void*)a, &list);
    dlist_append((void*)a, &list);
    
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)a, &expected_list);
    
    unsigned int res = dlist_traverse(false, &trav_clbk, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    dlist_free(&list);
    dlist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_traverse_null_params(void)
{
    bool pass = false;
    
    unsigned int res = dlist_traverse(false, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_traverse_empty_list(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    unsigned int res = dlist_traverse(false, &trav_clbk, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    dlist_free(&list);
    dlist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_traverse_reverse(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    unsigned int a = 12; /* arbitrary value */
    
    dlist_append((void*)a, &list);
    dlist_append((void*)a, &list);
    dlist_append((void*)a, &list);
    
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)a, &expected_list);
    
    unsigned int res = dlist_traverse(true, &trav_clbk, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    dlist_free(&list);
    dlist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

/* Utilities */
bool test_dlist_append_normal(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    unsigned int a = 12; /* arbitrary value */
    
    dlist_insert((void*)a, 0, &list);
    
    dlist_insert((void*)a, 0, &expected_list);
    dlist_insert((void*)a, 1, &expected_list);
    
    unsigned int res = dlist_append((void*)a, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    dlist_free(&list);
    dlist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_append_null_params(void)
{
    bool pass = false;
    
    unsigned int res = dlist_append(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_append_empty_list(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    unsigned int a = 12; /* arbitrary value */
    
    dlist_insert((void*)a, 0, &expected_list);
    
    unsigned int res = dlist_append((void*)a, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    dlist_free(&list);
    dlist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_concatenate_normal(void)
{
    bool pass = false;
    
    DList list_a;
    dlist_init(&list_a);
    
    DList list_b;
    dlist_init(&list_b);
    
    /* expected result of concatenation */
    DList expected_list_concat;
    dlist_init(&expected_list_concat);
    
    /* expected state of list_b after concatenation */
    DList expected_list_b;
    dlist_init(&expected_list_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    dlist_append((void*)a, &list_a);
    dlist_append((void*)b, &list_a);
    
    dlist_append((void*)b, &list_b);
    dlist_append((void*)a, &list_b);
    
    dlist_append((void*)a, &expected_list_concat);
    dlist_append((void*)b, &expected_list_concat);
    dlist_append((void*)b, &expected_list_concat);
    dlist_append((void*)a, &expected_list_concat);

    dlist_append((void*)b, &expected_list_b);
    dlist_append((void*)a, &expected_list_b);
    
    unsigned int res = dlist_concatenate(&list_a, &list_b);
    
    bool equal_a = false;
    dlist_equal(&equal_a, &list_a, &expected_list_concat);
    
    /* we must check that list_b wasn't modified */
    bool equal_b = false;
    dlist_equal(&equal_b, &list_b, &expected_list_b);
    
    dlist_free(&list_a);
    dlist_free(&list_b);
    dlist_free(&expected_list_concat);
    dlist_free(&expected_list_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_concatenate_null_params(void)
{
    bool pass = false;
    
    unsigned int res = dlist_concatenate(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_concatenate_empty_lists(void)
{
    bool pass = false;
    
    DList list_a;
    dlist_init(&list_a);
    
    DList list_b;
    dlist_init(&list_b);
    
    /* expected result of concatenation */
    DList expected_list;
    dlist_init(&expected_list);
    
    unsigned int res = dlist_concatenate(&list_a, &list_b);
    
    bool equal_a = false;
    dlist_equal(&equal_a, &list_a, &expected_list);
    
    /* we must check that list_b wasn't modified */
    bool equal_b = false;
    dlist_equal(&equal_b, &list_b, &expected_list);
    
    dlist_free(&list_a);
    dlist_free(&list_b);
    dlist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b)
    {
        pass = true;
    }    
    
    return pass;
}

bool test_dlist_concatenate_left_empty_list(void)
{
    bool pass = false;
    
    DList list_a;
    dlist_init(&list_a);
    
    DList list_b;
    dlist_init(&list_b);
    
    /* expected result of concatenation */
    DList expected_list_concat;
    dlist_init(&expected_list_concat);
    
    /* expected state of list_b after concatenation */
    DList expected_list_b;
    dlist_init(&expected_list_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    dlist_append((void*)b, &list_b);
    dlist_append((void*)a, &list_b);
    
    dlist_append((void*)b, &expected_list_concat);
    dlist_append((void*)a, &expected_list_concat);

    dlist_append((void*)b, &expected_list_b);
    dlist_append((void*)a, &expected_list_b);
    
    unsigned int res = dlist_concatenate(&list_a, &list_b);
    
    bool equal_a = false;
    dlist_equal(&equal_a, &list_a, &expected_list_concat);
    
    /* we must check that list_b wasn't modified */
    bool equal_b = false;
    dlist_equal(&equal_b, &list_b, &expected_list_b);
    
    dlist_free(&list_a);
    dlist_free(&list_b);
    dlist_free(&expected_list_concat);
    dlist_free(&expected_list_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_concatenate_right_empty_list(void)
{
    bool pass = false;
    
    DList list_a;
    dlist_init(&list_a);
    
    DList list_b;
    dlist_init(&list_b);
    
    /* expected result of concatenation */
    DList expected_list_concat;
    dlist_init(&expected_list_concat);
    
    /* expected state of list_b after concatenation */
    DList expected_list_b;
    dlist_init(&expected_list_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    dlist_append((void*)b, &list_a);
    dlist_append((void*)a, &list_a);
    
    dlist_append((void*)b, &expected_list_concat);
    dlist_append((void*)a, &expected_list_concat);
    
    unsigned int res = dlist_concatenate(&list_a, &list_b);
    
    bool equal_a = false;
    dlist_equal(&equal_a, &list_a, &expected_list_concat);
    
    /* we must check that list_b wasn't modified */
    bool equal_b = false;
    dlist_equal(&equal_b, &list_b, &expected_list_b);
    
    dlist_free(&list_a);
    dlist_free(&list_b);
    dlist_free(&expected_list_concat);
    dlist_free(&expected_list_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_swap_normal(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    dlist_append((void*)a, &list);
    dlist_append((void*)b, &list);
    dlist_append((void*)b, &list);
    dlist_append((void*)a, &list);
    
    /* expected list */
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)b, &expected_list);
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)b, &expected_list);
    
    unsigned int res = dlist_swap(2, 3, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    dlist_free(&list);
    dlist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_swap_null_params(void)
{
    bool pass = false;
    
    unsigned int res = dlist_swap(0, 1, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_swap_out_of_bounds(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    dlist_append((void*)a, &list);
    dlist_append((void*)b, &list);
    dlist_append((void*)b, &list);
    dlist_append((void*)a, &list);
    
    /* expected list */
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)b, &expected_list);
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)b, &expected_list);
    
    unsigned int res = dlist_swap(4, 5, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    dlist_free(&list);
    dlist_free(&expected_list);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS && !equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_dlist_swap_same_index(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    dlist_append((void*)a, &list);
    dlist_append((void*)b, &list);
    dlist_append((void*)b, &list);
    dlist_append((void*)a, &list);
    
    /* expected list */
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)b, &expected_list);
    dlist_append((void*)b, &expected_list);
    dlist_append((void*)a, &expected_list);
    
    unsigned int res = dlist_swap(0, 0, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    dlist_free(&list);
    dlist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}
