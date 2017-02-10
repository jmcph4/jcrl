#include <stdlib.h>

#include "constants.h"
#include "multiset.h"

bool test_multiset_init_normal(void)
{
    bool pass = false;
    
    Multiset multiset;
    
    unsigned int res = multiset_init(&multiset);
    
    multiset_free(NULL, &multiset);
    
    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_init_null_params(void)
{
    bool pass = false;
    
    unsigned int res = multiset_init(NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_free_normal(void)
{
    bool pass = false;
    
    Multiset multiset;
    multiset_init(&multiset);
    
    unsigned int res = multiset_free(NULL, &multiset);
    
    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_free_null_params(void)
{
    bool pass = false;
    
    unsigned int res = multiset_free(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_init_list_normal(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    Multiset multiset;
    
    Multiset expected_multiset;
    multiset_init(&expected_multiset);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    
    list_append((void*)a, &list);
    list_append((void*)a, &list);
    list_append((void*)b, &list);
    list_append((void*)c, &list);
    
    list_append((void*)a, &expected_list);
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    list_append((void*)c, &expected_list);
    
    multiset_add((void*)a, &expected_multiset);
    multiset_add((void*)a, &expected_multiset);
    multiset_add((void*)b, &expected_multiset);
    multiset_add((void*)c, &expected_multiset);
    
    unsigned int res = multiset_init_list(&list, &multiset);
    
    bool equal_multiset = false;
    multiset_equal(&equal_multiset, &multiset, &expected_multiset);
    
    bool equal_list = false;
    list_equal(&equal_list, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    multiset_free(NULL, &multiset);
    multiset_free(NULL, &expected_multiset);
    
    if(res == JCRL_ERR_OK && equal_list && equal_multiset)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_init_list_null_params(void)
{
    bool pass = false;
    
    unsigned int res = multiset_init_list(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

/* Operations */
bool test_multiset_add_normal(void)
{
    bool pass = false;
    
    Multiset multiset;
    multiset_init(&multiset);
    
    Multiset expected_multiset;
    multiset_init(&expected_multiset);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    unsigned int res = multiset_add((void*)a, &multiset);
    
    multiset_add((void*)a, &expected_multiset);
    
    bool equal = false;
    multiset_equal(&equal, &multiset, &expected_multiset);
    
    multiset_free(NULL, &multiset);
    multiset_free(NULL, &expected_multiset);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_add_null_params(void)
{
    bool pass = false;
    
    unsigned int res = multiset_add(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_remove_normal(void)
{
    bool pass = false;
    
    Multiset multiset;
    multiset_init(&multiset);
    
    Multiset expected_multiset;
    multiset_init(&expected_multiset);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    multiset_add((void*)a, &multiset);
    multiset_add((void*)a, &multiset);
    multiset_add((void*)b, &multiset);
    
    multiset_add((void*)a, &expected_multiset);
    multiset_add((void*)a, &expected_multiset);
    
    unsigned int res = multiset_remove((void*)b, &multiset);
    
    bool equal = false;
    multiset_equal(&equal, &multiset, &expected_multiset);
    
    multiset_free(NULL, &multiset);
    multiset_free(NULL, &expected_multiset);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_remove_null_params(void)
{
    bool pass = false;
    
    unsigned int res = multiset_remove(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_remove_not_found(void)
{
    bool pass = false;
    
    Multiset multiset;
    multiset_init(&multiset);
    
    Multiset expected_multiset;
    multiset_init(&expected_multiset);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    multiset_add((void*)a, &multiset);
    multiset_add((void*)a, &multiset);
    
    multiset_add((void*)a, &expected_multiset);
    multiset_add((void*)a, &expected_multiset);
    
    unsigned int res = multiset_remove((void*)b, &multiset);
    
    bool equal = false;
    multiset_equal(&equal, &multiset, &expected_multiset);
    
    multiset_free(NULL, &multiset);
    multiset_free(NULL, &expected_multiset);
    
    if(res == JCRL_ERR_NOT_FOUND && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_union_normal(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    unsigned int e = 512;
    
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)c, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)c, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)e, &multiset_b);
    
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)e, &expected_multiset_b);
    
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)e, &expected_multiset_c);
    
    unsigned int res = multiset_union(&multiset_a, &multiset_b, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_union_null_params(void)
{
    bool pass = false;
    
    unsigned int res = multiset_union(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_union_with_empty_set(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)c, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)c, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    
    unsigned int res = multiset_union(&multiset_a, &multiset_b, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_union_empty_set_with(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    unsigned int e = 512;
    
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)e, &multiset_b);
    
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)e, &expected_multiset_b);
    
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)e, &expected_multiset_c);
    
    unsigned int res = multiset_union(&multiset_a, &multiset_b, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_union_empty_sets(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    unsigned int res = multiset_union(&multiset_a, &multiset_b, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_union_commutes(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    unsigned int e = 512;
    
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)c, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)c, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)e, &multiset_b);
    
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)e, &expected_multiset_b);
    
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)e, &expected_multiset_c);
    
    unsigned int res = multiset_union(&multiset_b, &multiset_a, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_union_same_sets(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)c, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)c, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    
    unsigned int res = multiset_union(&multiset_a, &multiset_a, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_intersection_normal(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    unsigned int e = 512;
    
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)c, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)c, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)e, &multiset_b);
    
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)e, &expected_multiset_b);
    
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    
    unsigned int res = multiset_intersection(&multiset_a, &multiset_b, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_intersection_null_params(void)
{
    bool pass = false;
    
    unsigned int res = multiset_intersection(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_intersection_with_empty_set(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)c, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)c, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    
    unsigned int res = multiset_intersection(&multiset_a, &multiset_b, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_intersection_empty_set_with(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    unsigned int e = 512;
    
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)e, &multiset_b);
    
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)e, &expected_multiset_b);
    
    unsigned int res = multiset_intersection(&multiset_a, &multiset_b, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_intersection_empty_sets(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    unsigned int res = multiset_intersection(&multiset_a, &multiset_b, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_intersection_commutes(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    unsigned int e = 512;
    
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)c, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)c, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)e, &multiset_b);
    
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)e, &expected_multiset_b);
    
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    
    unsigned int res = multiset_intersection(&multiset_b, &multiset_a, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_intersection_same_sets(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)c, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)c, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    
    unsigned int res = multiset_intersection(&multiset_a, &multiset_a, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_difference_normal(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    unsigned int e = 512;
    
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)c, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)c, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)e, &multiset_b);
    
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)e, &expected_multiset_b);
    
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    
    unsigned int res = multiset_difference(&multiset_a, &multiset_b, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_difference_null_params(void)
{
    bool pass = false;
    
    unsigned int res = multiset_difference(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_difference_with_empty_set(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)c, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)c, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    
    unsigned int res = multiset_difference(&multiset_a, &multiset_b, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_difference_empty_set_with(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    unsigned int e = 512;
    
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)e, &multiset_b);
    
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)e, &expected_multiset_b);
    
    unsigned int res = multiset_difference(&multiset_a, &multiset_b, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_difference_empty_sets(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    unsigned int res = multiset_difference(&multiset_a, &multiset_b, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_difference_same_sets(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)c, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)c, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    
    unsigned int res = multiset_difference(&multiset_a, &multiset_a, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_sum_normal(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    unsigned int e = 512;
    
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)c, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)c, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)e, &multiset_b);
    
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)e, &expected_multiset_b);
    
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)e, &expected_multiset_c);
    
    unsigned int res = multiset_sum(&multiset_a, &multiset_b, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_sum_null_params(void)
{
    bool pass = false;
    
    unsigned int res = multiset_sum(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_sum_with_empty_set(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)c, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)c, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    
    unsigned int res = multiset_sum(&multiset_a, &multiset_b, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_sum_empty_set_with(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    unsigned int e = 512;
    
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)e, &multiset_b);
    
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)e, &expected_multiset_b);
    
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)e, &expected_multiset_c);
    
    unsigned int res = multiset_sum(&multiset_a, &multiset_b, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_sum_empty_sets(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    unsigned int res = multiset_sum(&multiset_a, &multiset_b, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_sum_commutes(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_b;
    multiset_init(&expected_multiset_b);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    unsigned int e = 512;
    
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)c, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)c, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)c, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)d, &multiset_b);
    multiset_add((void*)e, &multiset_b);
    
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)b, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)c, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)d, &expected_multiset_b);
    multiset_add((void*)e, &expected_multiset_b);
    
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)e, &expected_multiset_c);
    
    unsigned int res = multiset_sum(&multiset_b, &multiset_a, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_b = false;
    multiset_equal(&equal_b, &multiset_b, &expected_multiset_b);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_b);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_sum_same_sets(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_c;
    multiset_init(&multiset_c);
    
    Multiset expected_multiset_a;
    multiset_init(&expected_multiset_a);
    
    Multiset expected_multiset_c;
    multiset_init(&expected_multiset_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    unsigned int d = 8;
    
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    multiset_add((void*)c, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    multiset_add((void*)d, &multiset_a);
    
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)a, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)b, &expected_multiset_a);
    multiset_add((void*)c, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    multiset_add((void*)d, &expected_multiset_a);
    
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)a, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)b, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)c, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    multiset_add((void*)d, &expected_multiset_c);
    
    unsigned int res = multiset_sum(&multiset_a, &multiset_a, &multiset_c);
    
    bool equal_a = false;
    multiset_equal(&equal_a, &multiset_a, &expected_multiset_a);
    
    bool equal_c = false;
    multiset_equal(&equal_c, &multiset_c, &expected_multiset_c);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_c);
    multiset_free(NULL, &expected_multiset_a);
    multiset_free(NULL, &expected_multiset_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_cardinality_normal(void)
{
    bool pass = false;
    
    Multiset multiset;
    multiset_init(&multiset);
    
    Multiset expected_multiset;
    multiset_init(&expected_multiset);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    
    multiset_add((void*)a, &multiset);
    multiset_add((void*)a, &multiset);
    multiset_add((void*)b, &multiset);
    
    multiset_add((void*)a, &expected_multiset);
    multiset_add((void*)a, &expected_multiset);
    multiset_add((void*)b, &expected_multiset);
    
    unsigned int card = 0;
    
    unsigned int res = multiset_cardinality(&card, &multiset);
    
    bool equal = false;
    multiset_equal(&equal, &multiset, &expected_multiset);
    
    multiset_free(NULL, &multiset);
    multiset_free(NULL, &expected_multiset);
    
    if(res == JCRL_ERR_OK && equal && card == 3)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_cardinality_null_params(void)
{
    bool pass = false;
    
    unsigned int res = multiset_cardinality(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_cardinality_empty_set(void)
{
    bool pass = false;
    
    Multiset multiset;
    multiset_init(&multiset);
    
    Multiset expected_multiset;
    multiset_init(&expected_multiset);
    
    unsigned int card = 1; /* different from expected value */
    
    unsigned int res = multiset_cardinality(&card, &multiset);
    
    bool equal = false;
    multiset_equal(&equal, &multiset, &expected_multiset);
    
    multiset_free(NULL, &multiset);
    multiset_free(NULL, &expected_multiset);
    
    if(res == JCRL_ERR_OK && equal && card == 0)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_multiplicity_normal(void)
{
    bool pass = false;
    
    Multiset multiset;
    multiset_init(&multiset);
    
    Multiset expected_multiset;
    multiset_init(&expected_multiset);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    
    multiset_add((void*)a, &multiset);
    multiset_add((void*)a, &multiset);
    multiset_add((void*)b, &multiset);
    
    multiset_add((void*)a, &expected_multiset);
    multiset_add((void*)a, &expected_multiset);
    multiset_add((void*)b, &expected_multiset);
    
    unsigned int mult = 0;
    
    unsigned int res = multiset_multiplicity(&mult, (void*)a, &multiset);
    
    bool equal = false;
    multiset_equal(&equal, &multiset, &expected_multiset);
    
    multiset_free(NULL, &multiset);
    multiset_free(NULL, &expected_multiset);
    
    if(res == JCRL_ERR_OK && equal && mult == 2)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_multiplicity_null_params(void)
{
    bool pass = false;
    
    unsigned int res = multiset_multiplicity(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_multiplicity_not_found(void)
{
    bool pass = false;
    
    Multiset multiset;
    multiset_init(&multiset);
    
    Multiset expected_multiset;
    multiset_init(&expected_multiset);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    
    multiset_add((void*)a, &multiset);
    multiset_add((void*)a, &multiset);
    multiset_add((void*)b, &multiset);
    
    multiset_add((void*)a, &expected_multiset);
    multiset_add((void*)a, &expected_multiset);
    multiset_add((void*)b, &expected_multiset);
    
    unsigned int mult = 0;
    
    unsigned int res = multiset_multiplicity(&mult, (void*)c, &multiset);
    
    bool equal = false;
    multiset_equal(&equal, &multiset, &expected_multiset);
    
    multiset_free(NULL, &multiset);
    multiset_free(NULL, &expected_multiset);
    
    if(res == JCRL_ERR_OK && equal && mult == 0)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_equal_normal(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    Multiset multiset_b;
    multiset_init(&multiset_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    
    multiset_add((void*)a, &multiset_b);
    multiset_add((void*)b, &multiset_b);
    multiset_add((void*)a, &multiset_b);
    
    bool equal = false;
    
    unsigned int res = multiset_equal(&equal, &multiset_a, &multiset_b);
    
    multiset_free(NULL, &multiset_a);
    multiset_free(NULL, &multiset_b);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_equal_null_params(void)
{
    bool pass = false;
    
    unsigned int res = multiset_equal(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_equal_same_set(void)
{
    bool pass = false;
    
    Multiset multiset_a;
    multiset_init(&multiset_a);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)a, &multiset_a);
    multiset_add((void*)b, &multiset_a);
    
    bool equal = false;
    
    unsigned int res = multiset_equal(&equal, &multiset_a, &multiset_a);
    
    multiset_free(NULL, &multiset_a);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_in_normal(void)
{
    bool pass = false;
    
    Multiset multiset;
    multiset_init(&multiset);
    
    Multiset expected_multiset;
    multiset_init(&expected_multiset);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    
    multiset_add((void*)a, &multiset);
    multiset_add((void*)b, &multiset);
    multiset_add((void*)a, &multiset);
    
    multiset_add((void*)a, &expected_multiset);
    multiset_add((void*)b, &expected_multiset);
    multiset_add((void*)a, &expected_multiset);
    
    bool in = false;
    
    unsigned int res = multiset_in(&in, (void*)a, &multiset);
    
    bool equal = false;
    multiset_equal(&equal, &multiset, &expected_multiset);
    
    multiset_free(NULL, &multiset);
    multiset_free(NULL, &expected_multiset);
    
    if(res == JCRL_ERR_OK && in && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_in_null_params(void)
{
    bool pass = false;
    
    unsigned int res = multiset_in(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_in_not_found(void)
{
    bool pass = false;
    
    Multiset multiset;
    multiset_init(&multiset);
    
    Multiset expected_multiset;
    multiset_init(&expected_multiset);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    
    multiset_add((void*)a, &multiset);
    multiset_add((void*)a, &multiset);
    
    multiset_add((void*)a, &expected_multiset);
    multiset_add((void*)a, &expected_multiset);
    
    bool in = false;
    
    unsigned int res = multiset_in(&in, (void*)b, &multiset);
    
    bool equal = false;
    multiset_equal(&equal, &multiset, &expected_multiset);
    
    multiset_free(NULL, &multiset);
    multiset_free(NULL, &expected_multiset);
    
    if(res == JCRL_ERR_OK && equal && !in)
    {
        pass = true;
    }
    
    return pass;
}

/* Utilities */
bool test_multiset_enumerate_normal(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    Multiset multiset;
    multiset_init(&multiset);
    
    Multiset expected_multiset;
    multiset_init(&expected_multiset);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    unsigned int d = 8;
    
    multiset_add((void*)a, &multiset);
    multiset_add((void*)b, &multiset);
    multiset_add((void*)c, &multiset);
    multiset_add((void*)d, &multiset);
    
    multiset_add((void*)a, &expected_multiset);
    multiset_add((void*)b, &expected_multiset);
    multiset_add((void*)c, &expected_multiset);
    multiset_add((void*)d, &expected_multiset);
    
    list_append((void*)a, &expected_list);
    list_append((void*)b, &expected_list);
    list_append((void*)c, &expected_list);
    list_append((void*)d, &expected_list);
    
    unsigned int res = multiset_enumerate(&list, &multiset);
    
    bool equal_list = false;
    list_equal(&equal_list, &list, &expected_list);
    
    bool equal_multiset = false;
    multiset_equal(&equal_multiset, &multiset, &expected_multiset);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    multiset_free(NULL, &multiset);
    multiset_free(NULL, &expected_multiset);
    
    if(res == JCRL_ERR_OK && equal_list && equal_multiset)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_enumerate_null_params(void)
{
    bool pass = false;
    
    unsigned int res = multiset_enumerate(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_multiset_enumerate_empty_set(void)
{
    bool pass = false;
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    Multiset multiset;
    multiset_init(&multiset);
    
    Multiset expected_multiset;
    multiset_init(&expected_multiset);
    
    unsigned int res = multiset_enumerate(&list, &multiset);
    
    bool equal_list = false;
    list_equal(&equal_list, &list, &expected_list);
    
    bool equal_multiset = false;
    multiset_equal(&equal_multiset, &multiset, &expected_multiset);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    multiset_free(NULL, &multiset);
    multiset_free(NULL, &expected_multiset);
    
    if(res == JCRL_ERR_OK && equal_list && equal_multiset)
    {
        pass = true;
    }
    
    return pass;
}
