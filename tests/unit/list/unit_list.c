/*
 * unit_list.c
 * 
 * Unit tests for the list implementation. For test declarations,
 * see unit_list.h.
 */
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "constants.h"
#include "macros.h"
#include "list.h"
#include "unit_list.h"

/* stub callback for testing list traversal */
void trav_clbk(void* data, unsigned int pos)
{
    pos++; /* useless */
    char* new_ptr = (char*)data + pos; /* useless */
    new_ptr++; /* useless */
}

/* stub comparison function for testing list min/max */
bool cmp(void* a, void* b)
{
    return ((uintptr_t)a <= (uintptr_t)b);
}

/* Initialisation */
bool test_list_init_normal(void)
{
    bool pass = false;
    
    bool equal = false;
    
    /* correct list */
    List expected_list;
    list_init(&expected_list);
    
    /* list we're testing */
    List list;
    unsigned int res = list_init(&list);
    
    list_equal(&equal, &list, &expected_list); /* test equality */
    
    list_free(NULL, &list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_list_init_null_params(void)
{
    bool pass = false;
    
    unsigned int res = list_init(NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_list_free_normal(void)
{
    bool pass = false;
    
    /* set up list */
    unsigned int* a = calloc(1, sizeof(unsigned int));
    *a = 12; /* arbitrary value */
    
    List list;
    list_init(&list);
    list_append((void*)a, &list);
    list_append((void*)a, &list);
    list_append((void*)a, &list);
    
    unsigned int res = list_free(NULL, &list);
    
    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }
    
    free(a);

    return pass;
}

bool test_list_free_null_params(void)
{
    bool pass = false;
    
    unsigned int res = list_free(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_list_free_empty_list(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    unsigned int res = list_free(NULL, &list);
    
    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }
    
    return pass;
}

/* Equality */
bool test_list_equal_normal(void)
{
    bool pass = false;
    
    List list_a;
    list_init(&list_a);
    
    List list_b;
    list_init(&list_b);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));

    /* arbitrary numbers to insert */
    *a = 0;
    *b = 1;
    
    /* set up first list */
    list_append((void*)a, &list_a);
    list_append((void*)b, &list_a);
    list_append((void*)b, &list_a);
    
    /* set up second list */
    list_append((void*)a, &list_b);
    list_append((void*)b, &list_b);
    list_append((void*)b, &list_b);
    
    bool equal = false;
    
    unsigned int res = list_equal(&equal, &list_a, &list_b);
    
    list_free(NULL, &list_a);
    list_free(NULL, &list_b);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    free(a);
    free(b);

    return pass;
}

bool test_list_equal_null_params(void)
{
    bool pass = false;
    
    unsigned int res = list_equal(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_list_equal_unequal_lists(void)
{
    bool pass = false;
    
    List list_a;
    list_init(&list_a);
    
    List list_b;
    list_init(&list_b);

    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));

    
    /* arbitrary numbers to insert */
    *a = 0;
    *b = 1;
    
    /* set up first list */
    list_append((void*)a, &list_a);
    list_append((void*)b, &list_a);
    list_append((void*)b, &list_a);
    
    /* set up second list */
    list_append((void*)b, &list_b);
    list_append((void*)a, &list_b);
    list_append((void*)a, &list_b);
    
    bool equal = false;
    
    unsigned int res = list_equal(&equal, &list_a, &list_b);
    
    list_free(NULL, &list_a);
    list_free(NULL, &list_b);
    
    if(res == JCRL_ERR_OK && !equal)
    {
        pass = true;
    }
    
    free(a);
    free(b);

    return pass;
}

bool test_list_equal_same_lists(void)
{
    bool pass = false;
    
    List list_a;
    list_init(&list_a);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));

    /* arbitrary numbers to insert */
    *a = 0;
    *b = 1;
    
    /* set up test list */
    list_append((void*)a, &list_a);
    list_append((void*)b, &list_a);
    list_append((void*)b, &list_a);
    
    bool equal = false;
    
    unsigned int res = list_equal(&equal, &list_a, &list_a);
    
    list_free(NULL, &list_a);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    free(a);
    free(b);

    return pass;
}

/* Membership */
bool test_list_in_normal(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 33;
    
    list_append((void*)a, &list);
    list_append((void*)b, &list);
    
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    
    bool in = false;
    unsigned int res = list_in(&in, (void*)a, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_OK && equal && in)
    {
        pass = true;
    }
    
    free(a);
    free(b);

    return pass;
}

bool test_list_in_null_params(void)
{
    bool pass = false;
    
    unsigned int res = list_in(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_list_in_empty_list(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));

    *a = 12; /* arbitrary value to insert */
    
    bool in = false;
    unsigned int res = list_in(&in, (void*)a, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_OK && equal && !in)
    {
        pass = true;
    }
    
    free(a);

    return pass;
}

/* Access */
bool test_list_get_normal(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));

    *a = 12; /* arbitrary number to insert */
    
    list_append((void*)a, &list);
    
    unsigned int** val = calloc(1, sizeof(unsigned int*)); /* store elem here */
    
    unsigned int res = list_get((void**)val, 0, &list);
    
    list_free(NULL, &list);
    
    if(res == JCRL_ERR_OK && *val == a)
    {
        pass = true;
    }
    
    free(val);
    free(a);

    return pass;
}

bool test_list_get_null_params(void)
{
    bool pass = false;

    unsigned int res = list_get(NULL, 0, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_list_get_out_of_bounds(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));

    *a = 12; /* arbitrary number to insert */
    
    list_append((void*)a, &list);
    
    unsigned int* val = calloc(1, sizeof(unsigned int)); /* store elem here */
    
    unsigned int res = list_get((void*)&val, 1, &list);
    
    list_free(NULL, &list);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS)
    {
        pass = true;
    }
    
    free(val);
    free(a);
    
    return pass;
}

bool test_list_set_normal(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    /* list we'll compare results against */
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert into list */
    *a = 12;
    *b = 3;
    
    /* set up first list */
    list_append((void*)a, &list);
    list_append((void*)b, &list);
    list_append((void*)a, &list);
    
    /* set up expected list */
    list_append((void*)a, &expected_list);
    list_append((void*)a, &expected_list);
    list_append((void*)a, &expected_list);
    
    unsigned int res = list_set((void*)a, 1, &list);
    
    /* test equality */
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    list_free(NULL, &list);
    
    free(a);
    free(b);

    return pass;
}

bool test_list_set_null_params(void)
{
    bool pass = false;
 
    unsigned int res = list_set(NULL, 0, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_list_set_out_of_bounds(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    /* list we'll compare results against */
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert into list */
    *a = 12;
    *b = 3;
    
    /* set up first list */
    list_append((void*)a, &list);
    list_append((void*)b, &list);
    list_append((void*)a, &list);
    
    /* set up expected list */
    list_append((void*)a, &expected_list);
    list_append((void*)a, &expected_list);
    list_append((void*)a, &expected_list);
    
    unsigned int res = list_set((void*)a, 3, &list);
    
    /* test equality */
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS && !equal)
    {
        pass = true;
    }
    
    list_free(NULL, &list);
    
    free(a);
    free(b);

    return pass;
}

bool test_list_length_normal(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));

    *a = 12;
    
    list_append((void*)a, &list);
    list_append((void*)a, &list);
    list_append((void*)a, &list);
    
    unsigned int len = 0;
    
    unsigned int res = list_length(&len, &list);
    
    list_free(NULL, &list);
    
    if(res == JCRL_ERR_OK && len == 3)
    {
        pass = true;
    }
    
    free(a);

    return pass;
}

bool test_list_length_null_params(void)
{
    bool pass = false;
    
    unsigned int res = list_length(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_list_length_empty_list(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    unsigned int len = 1;
    
    unsigned int res = list_length(&len, &list);
    
    list_free(NULL, &list);
    
    if(res == JCRL_ERR_OK && len == 0)
    {
        pass = true;
    }
    
    return pass;
}

/* Operations */
bool test_list_insert_normal(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));
    unsigned int* c = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 3;
    *c = 1;
    
    list_append((void*)a, &list);
    list_append((void*)c, &list);
    
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    list_append((void*)c, &expected_list);
    
    unsigned int res = list_insert((void*)b, 1, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    free(a);
    free(b);
    free(c);

    return pass;
}

bool test_list_insert_null_params(void)
{
    bool pass = false;
    
    unsigned int res = list_insert(NULL, 0, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_list_insert_out_of_bounds(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 3;
    
    list_append((void*)a, &list);
    list_append((void*)b, &list);
    
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    
    unsigned int res = list_insert((void*)b, 3, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS && equal)
    {
        pass = true;
    }
    
    free(a);
    free(b);

    return pass;
}

bool test_list_insert_new_head(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 3;
    
    list_append((void*)a, &list);
    list_append((void*)b, &list);
    
    list_append((void*)b, &expected_list);
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    
    unsigned int res = list_insert((void*)b, 0, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    free(a);
    free(b);

    return pass;
}

bool test_list_insert_new_tail(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 3;
    
    list_append((void*)a, &list);
    list_append((void*)b, &list);
    
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    list_append((void*)b, &expected_list);
    
    unsigned int res = list_insert((void*)b, 2, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    free(a);
    free(b);

    return pass;
}

bool test_list_insert_empty_list(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));

    *a = 12; /* arbitrary value to insert */
    
    list_append((void*)a, &expected_list);
    
    unsigned int res = list_insert((void*)a, 0, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    free(a);

    return pass;
}

bool test_list_remove_normal(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));
    unsigned int* c = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 3;
    *c = 1;
    
    list_append((void*)a, &list);
    list_append((void*)b, &list);
    list_append((void*)c, &list);
    
    list_append((void*)a, &expected_list);
    list_append((void*)c, &expected_list);
    
    unsigned int res = list_remove(1, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    free(a);
    free(b);
    free(c);

    return pass;
}

bool test_list_remove_null_params(void)
{
    bool pass = false;
    
    unsigned int res = list_remove(0, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_list_remove_out_of_bounds(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 3;
    
    list_append((void*)a, &list);
    list_append((void*)b, &list);
    
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    
    unsigned int res = list_remove(2, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS && equal)
    {
        pass = true;
    }
    
    free(a);
    free(b);

    return pass;
}

bool test_list_remove_new_head(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));
    unsigned int* c = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 3;
    *c = 1;
    
    list_append((void*)c, &list);
    list_append((void*)a, &list);
    list_append((void*)b, &list);
    
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    
    unsigned int res = list_remove(0, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    free(a);
    free(b);
    free(c);

    return pass;
}

bool test_list_remove_new_tail(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));
    unsigned int* c = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 3;
    *c = 1;
    
    list_append((void*)a, &list);
    list_append((void*)b, &list);
    list_append((void*)c, &list);
    
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    
    unsigned int res = list_remove(2, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }

    free(a);
    free(b);
    free(c);
    
    return pass;
}

bool test_list_traverse_normal(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));

    *a = 12; /* arbitrary value */
    
    list_append((void*)a, &list);
    list_append((void*)a, &list);
    list_append((void*)a, &list);
    
    list_append((void*)a, &expected_list);
    list_append((void*)a, &expected_list);
    list_append((void*)a, &expected_list);
    
    unsigned int res = list_traverse(false, &trav_clbk, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    free(a);

    return pass;
}

bool test_list_traverse_null_params(void)
{
    bool pass = false;
    
    unsigned int res = list_traverse(false, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_list_traverse_empty_list(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int res = list_traverse(false, &trav_clbk, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_list_traverse_reverse(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));

    *a = 12; /* arbitrary value */
    
    list_append((void*)a, &list);
    list_append((void*)a, &list);
    list_append((void*)a, &list);
    
    list_append((void*)a, &expected_list);
    list_append((void*)a, &expected_list);
    list_append((void*)a, &expected_list);
    
    unsigned int res = list_traverse(true, &trav_clbk, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    free(a);

    return pass;
}

/* Utilities */
bool test_list_append_normal(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));

    *a = 12; /* arbitrary value */
    
    list_insert((void*)a, 0, &list);
    
    list_insert((void*)a, 0, &expected_list);
    list_insert((void*)a, 1, &expected_list);
    
    unsigned int res = list_append((void*)a, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    free(a);

    return pass;
}

bool test_list_append_null_params(void)
{
    bool pass = false;
    
    unsigned int res = list_append(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_list_append_empty_list(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));

    *a = 12; /* arbitrary value */
    
    list_insert((void*)a, 0, &expected_list);
    
    unsigned int res = list_append((void*)a, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    free(a);

    return pass;
}

bool test_list_concatenate_normal(void)
{
    bool pass = false;
    
    List list_a;
    list_init(&list_a);
    
    List list_b;
    list_init(&list_b);
    
    /* expected result of concatenation */
    List expected_list_concat;
    list_init(&expected_list_concat);
    
    /* expected state of list_b after concatenation */
    List expected_list_b;
    list_init(&expected_list_b);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 3;
    
    list_append((void*)a, &list_a);
    list_append((void*)b, &list_a);
    
    list_append((void*)b, &list_b);
    list_append((void*)a, &list_b);
    
    list_append((void*)a, &expected_list_concat);
    list_append((void*)b, &expected_list_concat);
    list_append((void*)b, &expected_list_concat);
    list_append((void*)a, &expected_list_concat);

    list_append((void*)b, &expected_list_b);
    list_append((void*)a, &expected_list_b);
    
    unsigned int res = list_concatenate(&list_a, &list_b);
    
    bool equal_a = false;
    list_equal(&equal_a, &list_a, &expected_list_concat);
    
    /* we must check that list_b wasn't modified */
    bool equal_b = false;
    list_equal(&equal_b, &list_b, &expected_list_b);
    
    list_free(NULL, &list_a);
    list_free(NULL, &list_b);
    list_free(NULL, &expected_list_concat);
    list_free(NULL, &expected_list_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b)
    {
        pass = true;
    }
    
    free(a);
    free(b);

    return pass;
}

bool test_list_concatenate_null_params(void)
{
    bool pass = false;
    
    unsigned int res = list_concatenate(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_list_concatenate_empty_lists(void)
{
    bool pass = false;
    
    List list_a;
    list_init(&list_a);
    
    List list_b;
    list_init(&list_b);
    
    /* expected result of concatenation */
    List expected_list;
    list_init(&expected_list);
    
    unsigned int res = list_concatenate(&list_a, &list_b);
    
    bool equal_a = false;
    list_equal(&equal_a, &list_a, &expected_list);
    
    /* we must check that list_b wasn't modified */
    bool equal_b = false;
    list_equal(&equal_b, &list_b, &expected_list);
    
    list_free(NULL, &list_a);
    list_free(NULL, &list_b);
    list_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b)
    {
        pass = true;
    }    
    
    return pass;
}

bool test_list_concatenate_left_empty_list(void)
{
    bool pass = false;
    
    List list_a;
    list_init(&list_a);
    
    List list_b;
    list_init(&list_b);
    
    /* expected result of concatenation */
    List expected_list_concat;
    list_init(&expected_list_concat);
    
    /* expected state of list_b after concatenation */
    List expected_list_b;
    list_init(&expected_list_b);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 3;
    
    list_append((void*)b, &list_b);
    list_append((void*)a, &list_b);
    
    list_append((void*)b, &expected_list_concat);
    list_append((void*)a, &expected_list_concat);

    list_append((void*)b, &expected_list_b);
    list_append((void*)a, &expected_list_b);
    
    unsigned int res = list_concatenate(&list_a, &list_b);
    
    bool equal_a = false;
    list_equal(&equal_a, &list_a, &expected_list_concat);
    
    /* we must check that list_b wasn't modified */
    bool equal_b = false;
    list_equal(&equal_b, &list_b, &expected_list_b);
    
    list_free(NULL, &list_a);
    list_free(NULL, &list_b);
    list_free(NULL, &expected_list_concat);
    list_free(NULL, &expected_list_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b)
    {
        pass = true;
    }

    free(a);
    free(b);
    
    return pass;
}

bool test_list_concatenate_right_empty_list(void)
{
    bool pass = false;
    
    List list_a;
    list_init(&list_a);
    
    List list_b;
    list_init(&list_b);
    
    /* expected result of concatenation */
    List expected_list_concat;
    list_init(&expected_list_concat);
    
    /* expected state of list_b after concatenation */
    List expected_list_b;
    list_init(&expected_list_b);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 3;
    
    list_append((void*)b, &list_a);
    list_append((void*)a, &list_a);
    
    list_append((void*)b, &expected_list_concat);
    list_append((void*)a, &expected_list_concat);
    
    unsigned int res = list_concatenate(&list_a, &list_b);
    
    bool equal_a = false;
    list_equal(&equal_a, &list_a, &expected_list_concat);
    
    /* we must check that list_b wasn't modified */
    bool equal_b = false;
    list_equal(&equal_b, &list_b, &expected_list_b);
    
    list_free(NULL, &list_a);
    list_free(NULL, &list_b);
    list_free(NULL, &expected_list_concat);
    list_free(NULL, &expected_list_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b)
    {
        pass = true;
    }
    
    free(a);
    free(b);

    return pass;
}

bool test_list_swap_normal(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 3;
    
    list_append((void*)a, &list);
    list_append((void*)b, &list);
    list_append((void*)b, &list);
    list_append((void*)a, &list);
    
    /* expected list */
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    
    unsigned int res = list_swap(2, 3, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    free(a);
    free(b);

    return pass;
}

bool test_list_swap_null_params(void)
{
    bool pass = false;
    
    unsigned int res = list_swap(0, 1, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_list_swap_out_of_bounds(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 3;
    
    list_append((void*)a, &list);
    list_append((void*)b, &list);
    list_append((void*)b, &list);
    list_append((void*)a, &list);
    
    /* expected list */
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    
    unsigned int res = list_swap(4, 5, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS && !equal)
    {
        pass = true;
    }
    
    free(a);
    free(b);

    return pass;
}

bool test_list_swap_same_index(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 3;
    
    list_append((void*)a, &list);
    list_append((void*)b, &list);
    list_append((void*)b, &list);
    list_append((void*)a, &list);
    
    /* expected list */
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    list_append((void*)b, &expected_list);
    list_append((void*)a, &expected_list);
    
    unsigned int res = list_swap(0, 0, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    free(a);
    free(b);

    return pass;
}

bool test_list_find_normal(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));
    unsigned int* c = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 33;
    *c = 3;
    
    list_append((void*)a, &list);
    list_append((void*)b, &list);
    list_append((void*)c, &list);
    
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    list_append((void*)c, &expected_list);
    
    unsigned int pos = 0;
    
    unsigned int res = list_find(&pos, (void*)b, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_OK && equal && pos == 1)
    {
        pass = true;
    }
    
    free(a);
    free(b);
    free(c);

    return pass;
}

bool test_list_find_null_params(void)
{
    bool pass = false;
    
    unsigned int res = list_find(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_list_find_not_found(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));
    unsigned int* c = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 33;
    *c = 3;
    
    list_append((void*)a, &list);
    list_append((void*)b, &list);
    
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    
    unsigned int pos = 0;
    
    unsigned int res = list_find(&pos, (void*)c, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_NOT_FOUND && equal && pos == 0)
    {
        pass = true;
    }
    
    free(a);
    free(b);
    free(c);

    return pass;
}

bool test_list_find_empty_list(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int pos = 0;
    
    unsigned int* a = calloc(1, sizeof(unsigned int));

    *a = 12; /* arbitrary value to insert */
    
    unsigned int res = list_find(&pos, (void*)a, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_NOT_FOUND && equal && pos == 0)
    {
        pass = true;
    }
    
    free(a);

    return pass;
}

bool test_list_find_duplicates(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 33;
    
    list_append((void*)a, &list);
    list_append((void*)b, &list);
    list_append((void*)b, &list);
    
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    list_append((void*)b, &expected_list);
    
    unsigned int pos = 0;
    
    unsigned int res = list_find(&pos, (void*)b, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_OK && equal && pos == 1)
    {
        pass = true;
    }
    
    free(a);
    free(b);

    return pass;
}

bool test_list_count_normal(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));
    unsigned int* c = calloc(1, sizeof(unsigned int));
    unsigned int* d = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 33;
    *c = 1;
    *d = 3;
    
    list_append((void*)a, &list);
    list_append((void*)a, &list);
    list_append((void*)b, &list);
    list_append((void*)c, &list);
    list_append((void*)b, &list);
    list_append((void*)d, &list);
    
    list_append((void*)a, &expected_list);
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    list_append((void*)c, &expected_list);
    list_append((void*)b, &expected_list);
    list_append((void*)d, &expected_list);
    
    unsigned int count = 0;
    
    unsigned int res = list_count(&count, (void*)a, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_OK && equal && count == 2)
    {
        pass = true;
    }
    
    free(a);
    free(b);
    free(c);
    free(d);

    return pass;
}

bool test_list_count_null_params(void)
{
    bool pass = false;
    
    unsigned int res = list_count(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_list_count_not_found(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));

    *a = 12; /* arbitrary value */
    
    unsigned int count = 0;
    
    unsigned int res = list_count(&count, (void*)a, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_OK && equal && count == 0)
    {
        pass = true;
    }
    
    free(a);

    return pass;
}

bool test_list_minmax_normal(void)
{
    bool pass = false;

    List list;
    list_init(&list);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    unsigned int d = 24;

    /* populate list */
    list_append(G_INT(a), &list);
    list_append(G_INT(b), &list);
    list_append(G_INT(c), &list);
    list_append(G_INT(d), &list);

    unsigned long actual = 0;
    unsigned int res = list_minmax((void**)&actual, cmp, &list);

    unsigned long expected = b;

    list_free(NULL, &list);

    if(res == JCRL_ERR_OK && actual == expected)
    {
        pass = true;
    }

    return pass;
}

bool test_list_minmax_null_params(void)
{
    bool pass = false;

    unsigned int res = list_minmax(NULL, NULL, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_list_minmax_empty(void)
{
    bool pass = false;

    List list;
    list_init(&list);

    unsigned int actual = 0;
    unsigned int res = list_minmax((void**)&actual, cmp, &list);

    list_free(NULL, &list);

    if(res == JCRL_ERR_IMPOSSIBLE && actual == 0)
    {
        pass = true;
    }

    return pass;
}

bool test_list_argminmax_normal(void)
{
    bool pass = false;

    List list;
    list_init(&list);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    unsigned int d = 24;

    /* populate list */
    list_append(G_INT(a), &list);
    list_append(G_INT(b), &list);
    list_append(G_INT(c), &list);
    list_append(G_INT(d), &list);

    unsigned int actual = 0;
    unsigned int res = list_argminmax(&actual, cmp, &list);

    unsigned int expected = 1;

    list_free(NULL, &list);

    if(res == JCRL_ERR_OK && actual == expected)
    {
        pass = true;
    }

    return pass;
}

bool test_list_argminmax_null_params(void)
{
    bool pass = false;

    unsigned int res = list_argminmax(NULL, NULL, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_list_argminmax_empty(void)
{
    bool pass = false;

    List list;
    list_init(&list);

    unsigned int actual = 0;
    unsigned int res = list_argminmax(&actual, cmp, &list);

    list_free(NULL, &list);

    if(res == JCRL_ERR_IMPOSSIBLE && actual == 0)
    {
        pass = true;
    }

    return pass;
}

