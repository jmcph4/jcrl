/*
 * unit_slist.c
 * 
 * Unit tests for the singly-linked list implementation. For test declarations,
 * see unit_slist.h.
 */
#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"
#include "slist.h"
#include "unit_slist.h"

/* stub callback for testing list traversal */
void trav_clbk(void* data, unsigned int pos)
{
    pos++; /* useless */
    char* new_ptr = (char*)data + pos; /* useless */
    new_ptr++; /* useless */
}

/* Initialisation */
bool test_slist_init_normal(void)
{
    bool pass = false;
    
    bool equal = false;
    
    /* correct list */
    SList expected_list;
    slist_init(&expected_list);
    
    /* list we're testing */
    SList list;
    unsigned int res = slist_init(&list);
    
    slist_equal(&equal, &list, &expected_list); /* test equality */
    
    slist_free(&list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_init_null_params(void)
{
    bool pass = false;
    
    unsigned int res = slist_init(NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_free_normal(void)
{
    bool pass = false;
    
    /* set up list */
    unsigned int a = 12; /* arbitrary value */
    SList list;
    slist_init(&list);
    slist_append((void*)a, &list);
    slist_append((void*)a, &list);
    slist_append((void*)a, &list);
    
    unsigned int res = slist_free(&list);
    
    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_free_null_params(void)
{
    bool pass = false;
    
    unsigned int res = slist_free(NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_free_empty_list(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    unsigned int res = slist_free(&list);
    
    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }
    
    return pass;
}

/* Equality */
bool test_slist_equal_normal(void)
{
    bool pass = false;
    
    SList list_a;
    slist_init(&list_a);
    
    SList list_b;
    slist_init(&list_b);
    
    /* arbitrary numbers to insert */
    unsigned int a = 0;
    unsigned int b = 1;
    
    /* set up first list */
    slist_append((void*)a, &list_a);
    slist_append((void*)b, &list_a);
    slist_append((void*)b, &list_a);
    
    /* set up second list */
    slist_append((void*)a, &list_b);
    slist_append((void*)b, &list_b);
    slist_append((void*)b, &list_b);
    
    bool equal = false;
    
    unsigned int res = slist_equal(&equal, &list_a, &list_b);
    
    slist_free(&list_a);
    slist_free(&list_b);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_equal_null_params(void)
{
    bool pass = false;
    
    unsigned int res = slist_equal(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_equal_unequal_lists(void)
{
    bool pass = false;
    
    SList list_a;
    slist_init(&list_a);
    
    SList list_b;
    slist_init(&list_b);
    
    /* arbitrary numbers to insert */
    unsigned int a = 0;
    unsigned int b = 1;
    
    /* set up first list */
    slist_append((void*)a, &list_a);
    slist_append((void*)b, &list_a);
    slist_append((void*)b, &list_a);
    
    /* set up second list */
    slist_append((void*)b, &list_b);
    slist_append((void*)a, &list_b);
    slist_append((void*)a, &list_b);
    
    bool equal = false;
    
    unsigned int res = slist_equal(&equal, &list_a, &list_b);
    
    slist_free(&list_a);
    slist_free(&list_b);
    
    if(res == JCRL_ERR_OK && !equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_equal_same_lists(void)
{
    bool pass = false;
    
    SList list_a;
    slist_init(&list_a);
    
    /* arbitrary numbers to insert */
    unsigned int a = 0;
    unsigned int b = 1;
    
    /* set up test list */
    slist_append((void*)a, &list_a);
    slist_append((void*)b, &list_a);
    slist_append((void*)b, &list_a);
    
    bool equal = false;
    
    unsigned int res = slist_equal(&equal, &list_a, &list_a);
    
    slist_free(&list_a);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

/* Membership */
bool test_slist_in_normal(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    
    slist_append((void*)a, &list);
    slist_append((void*)b, &list);
    
    slist_append((void*)a, &expected_list);
    slist_append((void*)b, &expected_list);
    
    bool in = false;
    unsigned int res = slist_in(&in, (void*)a, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    slist_free(&list);
    slist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal && in)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_in_null_params(void)
{
    bool pass = false;
    
    unsigned int res = slist_in(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_in_empty_list(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    bool in = false;
    unsigned int res = slist_in(&in, (void*)a, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    slist_free(&list);
    slist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal && !in)
    {
        pass = true;
    }
    
    return pass;
}

/* Access */
bool test_slist_get_normal(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    unsigned int a = 12; /* arbitrary number to insert */
    
    slist_append((void*)a, &list);
    
    unsigned int* val = calloc(1, sizeof(unsigned int)); /* store elem here */
    
    unsigned int res = slist_get((void*)&val, 0, &list);
    
    slist_free(&list);
    
    if(res == JCRL_ERR_OK && (unsigned int)val == a)
    {
        pass = true;
    }
    
    free(val);
    
    return pass;
}

bool test_slist_get_null_params(void)
{
    bool pass = false;

    unsigned int res = slist_get(NULL, 0, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_get_out_of_bounds(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    unsigned int a = 12; /* arbitrary number to insert */
    
    slist_append((void*)a, &list);
    
    unsigned int* val = calloc(1, sizeof(unsigned int)); /* store elem here */
    
    unsigned int res = slist_get((void*)&val, 1, &list);
    
    slist_free(&list);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS)
    {
        pass = true;
    }
    
    free(val);
    
    return pass;
}

bool test_slist_set_normal(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    /* list we'll compare results against */
    SList expected_list;
    slist_init(&expected_list);
    
    /* arbitrary values to insert into list */
    unsigned int a = 12;
    unsigned int b = 3;
    
    /* set up first list */
    slist_append((void*)a, &list);
    slist_append((void*)b, &list);
    slist_append((void*)a, &list);
    
    /* set up expected list */
    slist_append((void*)a, &expected_list);
    slist_append((void*)a, &expected_list);
    slist_append((void*)a, &expected_list);
    
    unsigned int res = slist_set((void*)a, 1, &list);
    
    /* test equality */
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    slist_free(&list);
    
    return pass;
}

bool test_slist_set_null_params(void)
{
    bool pass = false;
 
    unsigned int res = slist_set(NULL, 0, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_set_out_of_bounds(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    /* list we'll compare results against */
    SList expected_list;
    slist_init(&expected_list);
    
    /* arbitrary values to insert into list */
    unsigned int a = 12;
    unsigned int b = 3;
    
    /* set up first list */
    slist_append((void*)a, &list);
    slist_append((void*)b, &list);
    slist_append((void*)a, &list);
    
    /* set up expected list */
    slist_append((void*)a, &expected_list);
    slist_append((void*)a, &expected_list);
    slist_append((void*)a, &expected_list);
    
    unsigned int res = slist_set((void*)a, 3, &list);
    
    /* test equality */
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS && !equal)
    {
        pass = true;
    }
    
    slist_free(&list);
    
    return pass;
}

bool test_slist_length_normal(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    unsigned int a = 12;
    
    slist_append((void*)a, &list);
    slist_append((void*)a, &list);
    slist_append((void*)a, &list);
    
    unsigned int len = 0;
    
    unsigned int res = slist_length(&len, &list);
    
    slist_free(&list);
    
    if(res == JCRL_ERR_OK && len == 3)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_length_null_params(void)
{
    bool pass = false;
    
    unsigned int res = slist_length(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_length_empty_list(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    unsigned int len = 1;
    
    unsigned int res = slist_length(&len, &list);
    
    slist_free(&list);
    
    if(res == JCRL_ERR_OK && len == 0)
    {
        pass = true;
    }
    
    return pass;
}

/* Operations */
bool test_slist_insert_normal(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    
    slist_append((void*)a, &list);
    slist_append((void*)c, &list);
    
    slist_append((void*)a, &expected_list);
    slist_append((void*)b, &expected_list);
    slist_append((void*)c, &expected_list);
    
    unsigned int res = slist_insert((void*)b, 1, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_insert_null_params(void)
{
    bool pass = false;
    
    unsigned int res = slist_insert(NULL, 0, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_insert_out_of_bounds(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    slist_append((void*)a, &list);
    slist_append((void*)b, &list);
    
    slist_append((void*)a, &expected_list);
    slist_append((void*)b, &expected_list);
    
    unsigned int res = slist_insert((void*)b, 3, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_insert_new_head(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    slist_append((void*)a, &list);
    slist_append((void*)b, &list);
    
    slist_append((void*)b, &expected_list);
    slist_append((void*)a, &expected_list);
    slist_append((void*)b, &expected_list);
    
    unsigned int res = slist_insert((void*)b, 0, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_insert_new_tail(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    slist_append((void*)a, &list);
    slist_append((void*)b, &list);
    
    slist_append((void*)a, &expected_list);
    slist_append((void*)b, &expected_list);
    slist_append((void*)b, &expected_list);
    
    unsigned int res = slist_insert((void*)b, 2, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_insert_empty_list(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    slist_append((void*)a, &expected_list);
    
    unsigned int res = slist_insert((void*)a, 0, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_remove_normal(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    
    slist_append((void*)a, &list);
    slist_append((void*)b, &list);
    slist_append((void*)c, &list);
    
    slist_append((void*)a, &expected_list);
    slist_append((void*)c, &expected_list);
    
    unsigned int res = slist_remove(1, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_remove_null_params(void)
{
    bool pass = false;
    
    unsigned int res = slist_remove(0, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_remove_out_of_bounds(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;

    
    slist_append((void*)a, &list);
    slist_append((void*)b, &list);
    
    slist_append((void*)a, &expected_list);
    slist_append((void*)b, &expected_list);
    
    unsigned int res = slist_remove(2, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_remove_new_head(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    
    slist_append((void*)c, &list);
    slist_append((void*)a, &list);
    slist_append((void*)b, &list);
    
    slist_append((void*)a, &expected_list);
    slist_append((void*)b, &expected_list);
    
    unsigned int res = slist_remove(0, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_remove_new_tail(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    
    slist_append((void*)a, &list);
    slist_append((void*)b, &list);
    slist_append((void*)c, &list);
    
    slist_append((void*)a, &expected_list);
    slist_append((void*)b, &expected_list);
    
    unsigned int res = slist_remove(2, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_traverse_normal(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    unsigned int a = 12; /* arbitrary value */
    
    slist_append((void*)a, &list);
    slist_append((void*)a, &list);
    slist_append((void*)a, &list);
    
    slist_append((void*)a, &expected_list);
    slist_append((void*)a, &expected_list);
    slist_append((void*)a, &expected_list);
    
    unsigned int res = slist_traverse(&trav_clbk, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    slist_free(&list);
    slist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_traverse_null_params(void)
{
    bool pass = false;
    
    unsigned int res = slist_traverse(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_traverse_empty_list(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    unsigned int res = slist_traverse(&trav_clbk, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    slist_free(&list);
    slist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

/* Utilities */
bool test_slist_append_normal(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    unsigned int a = 12; /* arbitrary value */
    
    slist_insert((void*)a, 0, &list);
    
    slist_insert((void*)a, 0, &expected_list);
    slist_insert((void*)a, 1, &expected_list);
    
    unsigned int res = slist_append((void*)a, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    slist_free(&list);
    slist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_append_null_params(void)
{
    bool pass = false;
    
    unsigned int res = slist_append(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_append_empty_list(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    unsigned int a = 12; /* arbitrary value */
    
    slist_insert((void*)a, 0, &expected_list);
    
    unsigned int res = slist_append((void*)a, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    slist_free(&list);
    slist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_concatenate_normal(void)
{
    bool pass = false;
    
    SList list_a;
    slist_init(&list_a);
    
    SList list_b;
    slist_init(&list_b);
    
    /* expected result of concatenation */
    SList expected_list_concat;
    slist_init(&expected_list_concat);
    
    /* expected state of list_b after concatenation */
    SList expected_list_b;
    slist_init(&expected_list_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    slist_append((void*)a, &list_a);
    slist_append((void*)b, &list_a);
    
    slist_append((void*)b, &list_b);
    slist_append((void*)a, &list_b);
    
    slist_append((void*)a, &expected_list_concat);
    slist_append((void*)b, &expected_list_concat);
    slist_append((void*)b, &expected_list_concat);
    slist_append((void*)a, &expected_list_concat);

    slist_append((void*)b, &expected_list_b);
    slist_append((void*)a, &expected_list_b);
    
    unsigned int res = slist_concatenate(&list_a, &list_b);
    
    bool equal_a = false;
    slist_equal(&equal_a, &list_a, &expected_list_concat);
    
    /* we must check that list_b wasn't modified */
    bool equal_b = false;
    slist_equal(&equal_b, &list_b, &expected_list_b);
    
    slist_free(&list_a);
    slist_free(&list_b);
    slist_free(&expected_list_concat);
    slist_free(&expected_list_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_concatenate_null_params(void)
{
    bool pass = false;
    
    unsigned int res = slist_concatenate(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_concatenate_empty_lists(void)
{
    bool pass = false;
    
    SList list_a;
    slist_init(&list_a);
    
    SList list_b;
    slist_init(&list_b);
    
    /* expected result of concatenation */
    SList expected_list;
    slist_init(&expected_list);
    
    unsigned int res = slist_concatenate(&list_a, &list_b);
    
    bool equal_a = false;
    slist_equal(&equal_a, &list_a, &expected_list);
    
    /* we must check that list_b wasn't modified */
    bool equal_b = false;
    slist_equal(&equal_b, &list_b, &expected_list);
    
    slist_free(&list_a);
    slist_free(&list_b);
    slist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b)
    {
        pass = true;
    }    
    
    return pass;
}

bool test_slist_concatenate_left_empty_list(void)
{
    bool pass = false;
    
    SList list_a;
    slist_init(&list_a);
    
    SList list_b;
    slist_init(&list_b);
    
    /* expected result of concatenation */
    SList expected_list_concat;
    slist_init(&expected_list_concat);
    
    /* expected state of list_b after concatenation */
    SList expected_list_b;
    slist_init(&expected_list_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    slist_append((void*)b, &list_b);
    slist_append((void*)a, &list_b);
    
    slist_append((void*)b, &expected_list_concat);
    slist_append((void*)a, &expected_list_concat);

    slist_append((void*)b, &expected_list_b);
    slist_append((void*)a, &expected_list_b);
    
    unsigned int res = slist_concatenate(&list_a, &list_b);
    
    bool equal_a = false;
    slist_equal(&equal_a, &list_a, &expected_list_concat);
    
    /* we must check that list_b wasn't modified */
    bool equal_b = false;
    slist_equal(&equal_b, &list_b, &expected_list_b);
    
    slist_free(&list_a);
    slist_free(&list_b);
    slist_free(&expected_list_concat);
    slist_free(&expected_list_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_concatenate_right_empty_list(void)
{
    bool pass = false;
    
    SList list_a;
    slist_init(&list_a);
    
    SList list_b;
    slist_init(&list_b);
    
    /* expected result of concatenation */
    SList expected_list_concat;
    slist_init(&expected_list_concat);
    
    /* expected state of list_b after concatenation */
    SList expected_list_b;
    slist_init(&expected_list_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    slist_append((void*)b, &list_a);
    slist_append((void*)a, &list_a);
    
    slist_append((void*)b, &expected_list_concat);
    slist_append((void*)a, &expected_list_concat);
    
    unsigned int res = slist_concatenate(&list_a, &list_b);
    
    bool equal_a = false;
    slist_equal(&equal_a, &list_a, &expected_list_concat);
    
    /* we must check that list_b wasn't modified */
    bool equal_b = false;
    slist_equal(&equal_b, &list_b, &expected_list_b);
    
    slist_free(&list_a);
    slist_free(&list_b);
    slist_free(&expected_list_concat);
    slist_free(&expected_list_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_swap_normal(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    slist_append((void*)a, &list);
    slist_append((void*)b, &list);
    slist_append((void*)b, &list);
    slist_append((void*)a, &list);
    
    /* expected list */
    slist_append((void*)a, &expected_list);
    slist_append((void*)b, &expected_list);
    slist_append((void*)a, &expected_list);
    slist_append((void*)b, &expected_list);
    
    unsigned int res = slist_swap(2, 3, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    slist_free(&list);
    slist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_swap_null_params(void)
{
    bool pass = false;
    
    unsigned int res = slist_swap(0, 1, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_swap_out_of_bounds(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    slist_append((void*)a, &list);
    slist_append((void*)b, &list);
    slist_append((void*)b, &list);
    slist_append((void*)a, &list);
    
    /* expected list */
    slist_append((void*)a, &expected_list);
    slist_append((void*)b, &expected_list);
    slist_append((void*)a, &expected_list);
    slist_append((void*)b, &expected_list);
    
    unsigned int res = slist_swap(4, 5, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    slist_free(&list);
    slist_free(&expected_list);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS && !equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_slist_swap_same_index(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    slist_append((void*)a, &list);
    slist_append((void*)b, &list);
    slist_append((void*)b, &list);
    slist_append((void*)a, &list);
    
    /* expected list */
    slist_append((void*)a, &expected_list);
    slist_append((void*)b, &expected_list);
    slist_append((void*)b, &expected_list);
    slist_append((void*)a, &expected_list);
    
    unsigned int res = slist_swap(0, 0, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    slist_free(&list);
    slist_free(&expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}
