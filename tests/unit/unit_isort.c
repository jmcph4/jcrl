/*
 * unit_isort.c
 * 
 * Unit tests for the isort implementation. For test declarations, see 
 * unit_isort.h.
 */
#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"
#include "isort.h"
#include "unit_isort.h"

bool cmp_clbk(void* a, void* b)
{
    if((unsigned int)a >= (unsigned int)b)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool test_isort_slist_normal(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 1;
    unsigned int b = 2;
    unsigned int c = 3;
    unsigned int d = 4;
    
    slist_append((void*)b, &list);
    slist_append((void*)a, &list);
    slist_append((void*)d, &list);
    slist_append((void*)c, &list);
    
    slist_append((void*)a, &expected_list);
    slist_append((void*)b, &expected_list);
    slist_append((void*)c, &expected_list);
    slist_append((void*)d, &expected_list);
    
    unsigned int res = isort_slist(&cmp_clbk, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    slist_free(NULL, &list);
    slist_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_isort_slist_null_params(void)
{
    bool pass = false;
    
    unsigned int res = isort_slist(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_isort_slist_empty_list(void)
{
    bool pass = false;
    
    SList list;
    slist_init(&list);
    
    SList expected_list;
    slist_init(&expected_list);
    
    unsigned int res = isort_slist(&cmp_clbk, &list);
    
    bool equal = false;
    slist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    slist_free(NULL, &list);
    slist_free(NULL, &expected_list);
    
    return pass;
}

bool test_isort_dlist_normal(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 1;
    unsigned int b = 2;
    unsigned int c = 3;
    unsigned int d = 4;
    
    dlist_append((void*)b, &list);
    dlist_append((void*)a, &list);
    dlist_append((void*)d, &list);
    dlist_append((void*)c, &list);
    
    dlist_append((void*)a, &expected_list);
    dlist_append((void*)b, &expected_list);
    dlist_append((void*)c, &expected_list);
    dlist_append((void*)d, &expected_list);
    
    unsigned int res = isort_dlist(&cmp_clbk, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    dlist_free(NULL, &list);
    dlist_free(NULL, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_isort_dlist_null_params(void)
{
    bool pass = false;
    
    unsigned int res = isort_dlist(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_isort_dlist_empty_list(void)
{
    bool pass = false;
    
    DList list;
    dlist_init(&list);
    
    DList expected_list;
    dlist_init(&expected_list);
    
    unsigned int res = isort_dlist(&cmp_clbk, &list);
    
    bool equal = false;
    dlist_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    dlist_free(NULL, &list);
    dlist_free(NULL, &expected_list);
    
    return pass;
}
