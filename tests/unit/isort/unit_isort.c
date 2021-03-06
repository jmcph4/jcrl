/*
 * unit_isort.c
 * 
 * Unit tests for the isort implementation. For test declarations, see 
 * unit_isort.h.
 */
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "constants.h"
#include "macros.h"
#include "isort.h"
#include "unit_isort.h"

bool cmp_clbk(void* a, void* b)
{
    if((intptr_t)a >= (intptr_t)b)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool test_isort_normal(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 1;
    unsigned int b = 2;
    unsigned int c = 3;
    unsigned int d = 4;
    
    list_append(G_INT(b), &list);
    list_append(G_INT(a), &list);
    list_append(G_INT(d), &list);
    list_append(G_INT(c), &list);
    
    list_append(G_INT(a), &expected_list);
    list_append(G_INT(b), &expected_list);
    list_append(G_INT(c), &expected_list);
    list_append(G_INT(d), &expected_list);
    
    unsigned int res = isort(&cmp_clbk, &list);
    
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

bool test_isort_null_params(void)
{
    bool pass = false;
    
    unsigned int res = isort(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_isort_empty_list(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int res = isort(&cmp_clbk, &list);
    
    bool equal = false;
    list_equal(&equal, &list, &expected_list);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    return pass;
}
