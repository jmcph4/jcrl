/*
 * unit_set.c
 * 
 * Unit tests for the set implementation. For test declarations, see
 * unit_set.h.
 */
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include "constants.h"
#include "macros.h"
#include "set.h"
#include "list.h"

#include "unit_set.h"

/* Initialisation */
bool test_set_init_normal(void)
{
    bool pass = false;
    
    Set set;
    
    unsigned int res = set_init(&set);
    
    set_free(NULL, &set);
    
    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_init_null_params(void)
{
    bool pass = false;
    
    unsigned int res = set_init(NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_free_normal(void)
{
    bool pass = false;
    
    Set set;
    set_init(&set);
    
    unsigned int res = set_free(NULL, &set);
    
    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_free_null_params(void)
{
    bool pass = false;
    
    unsigned int res = set_free(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

/* Equality */
bool test_set_equal_normal(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    set_add(G_INT(a), &set_a);
    set_add(G_INT(b), &set_a);
    
    set_add(G_INT(b), &set_b);
    set_add(G_INT(a), &set_b);
    
    bool equal = false;
    unsigned int res = set_equal(&equal, &set_a, &set_b);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_equal_null_params(void)
{
    bool pass = false;
    
    unsigned int res = set_equal(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_equal_empty_sets(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    bool equal = false;
    
    unsigned int res = set_equal(&equal, &set_a, &set_b);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_equal_unequal_sets(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    unsigned int c = 1;
    
    set_add(G_INT(a), &set_a);
    set_add(G_INT(b), &set_a);
    
    set_add(G_INT(c), &set_b);
    set_add(G_INT(b), &set_b);
    
    bool equal = false;
    unsigned int res = set_equal(&equal, &set_a, &set_b);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    
    if(res == JCRL_ERR_OK && !equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_equal_same_set(void)
{
    bool pass = false;
    
    Set set;
    set_init(&set);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    set_add(G_INT(a), &set);
    set_add(G_INT(b), &set);
    
    bool equal = false;
    unsigned int res = set_equal(&equal, &set, &set);
    
    set_free(NULL, &set);

    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

/* Membership */
bool test_set_in_normal(void)
{
    bool pass = false;
    
    Set set;
    set_init(&set);
    
    Set expected_set;
    set_init(&expected_set);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    
    set_add(G_INT(a), &set);
    set_add(G_INT(b), &set);
    
    set_add(G_INT(a), &expected_set);
    set_add(G_INT(b), &expected_set);
    
    bool in = false;
    
    unsigned int res = set_in(&in, G_INT(a), &set);
    
    bool equal = false;
    set_equal(&equal, &set, &expected_set);
    
    set_free(NULL, &set);
    set_free(NULL, &expected_set);
    
    if(res == JCRL_ERR_OK && equal && in)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_in_null_params(void)
{
    bool pass = false;
    
    unsigned int res = set_in(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_in_empty_set(void)
{
    bool pass = false;
    
    Set set;
    set_init(&set);
    
    Set expected_set;
    set_init(&expected_set);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    bool in = false;
    
    unsigned int res = set_in(&in, G_INT(a), &set);
    
    bool equal = false;
    set_equal(&equal, &set, &expected_set);
    
    set_free(NULL, &set);
    set_free(NULL, &expected_set);
    
    if(res == JCRL_ERR_OK && equal && !in)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_in_not_found(void)
{
    bool pass = false;
    
    Set set;
    set_init(&set);
    
    Set expected_set;
    set_init(&expected_set);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    
    set_add(G_INT(a), &set);
    set_add(G_INT(a), &expected_set);
    
    bool in = false;
    
    unsigned int res = set_in(&in, G_INT(b), &set);
    
    bool equal = false;
    set_equal(&equal, &set, &expected_set);
    
    set_free(NULL, &set);
    set_free(NULL, &expected_set);
    
    if(res == JCRL_ERR_OK && equal && !in)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_subset_normal(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    
    set_add(G_INT(a), &set_a);
    set_add(G_INT(b), &set_a);
    set_add(G_INT(c), &set_a);
    
    set_add(G_INT(a), &set_b);
    set_add(G_INT(b), &set_b);
    
    set_add(G_INT(a), &expected_set_a);
    set_add(G_INT(b), &expected_set_a);
    set_add(G_INT(c), &expected_set_a);
    
    set_add(G_INT(a), &expected_set_b);
    set_add(G_INT(b), &expected_set_b);
    
    bool subset = false;
    
    /* is b a subset of a? */
    unsigned int res = set_subset(&subset, &set_a, &set_b);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && subset)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_subset_null_params(void)
{
    bool pass = false;
    
    unsigned int res = set_subset(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_subset_improper_subset(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    
    set_add(G_INT(a), &set_a);
    set_add(G_INT(b), &set_a);
    set_add(G_INT(c), &set_a);
    
    set_add(G_INT(a), &set_b);
    set_add(G_INT(b), &set_b);
    set_add(G_INT(c), &set_b);
    
    set_add(G_INT(a), &expected_set_a);
    set_add(G_INT(b), &expected_set_a);
    set_add(G_INT(c), &expected_set_a);
    
    set_add(G_INT(a), &expected_set_b);
    set_add(G_INT(b), &expected_set_b);
    set_add(G_INT(c), &expected_set_b);
    
    bool subset = false;
    
    /* is b a subset of a? */
    unsigned int res = set_subset(&subset, &set_a, &set_b);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && subset)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_subset_empty_sets(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    bool subset = false;
    
    /* is b a subset of a? */
    unsigned int res = set_subset(&subset, &set_a, &set_b);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && subset)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_subset_of_empty_set(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    
    set_add(G_INT(a), &set_b);
    set_add(G_INT(b), &set_b);
    
    set_add(G_INT(a), &expected_set_b);
    set_add(G_INT(b), &expected_set_b);
    
    bool subset = false;
    
    /* is b a subset of a? */
    unsigned int res = set_subset(&subset, &set_a, &set_b);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && !subset)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_subset_empty_set_of(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    
    set_add(G_INT(a), &set_a);
    set_add(G_INT(b), &set_a);
    set_add(G_INT(c), &set_a);
    
    set_add(G_INT(a), &expected_set_a);
    set_add(G_INT(b), &expected_set_a);
    set_add(G_INT(c), &expected_set_a);
    
    bool subset = false;
    
    /* is b a subset of a? */
    unsigned int res = set_subset(&subset, &set_a, &set_b);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && subset)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_subset_same_set(void)
{
    bool pass = false;
    
    Set set;
    set_init(&set);
    
    Set expected_set;
    set_init(&expected_set);

    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    
    set_add(G_INT(a), &set);
    set_add(G_INT(b), &set);
    set_add(G_INT(c), &set);
    
    set_add(G_INT(a), &expected_set);
    set_add(G_INT(b), &expected_set);
    set_add(G_INT(c), &expected_set);

    bool subset = false;
    
    /* is set a subset of itself? */
    unsigned int res = set_subset(&subset, &set, &set);
    
    bool equal = false;
    set_equal(&equal, &set, &expected_set);
    
    set_free(NULL, &set);
    set_free(NULL, &expected_set);
    
    if(res == JCRL_ERR_OK && equal && subset)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_superset_normal(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    
    set_add(G_INT(a), &set_a);
    set_add(G_INT(b), &set_a);
    
    set_add(G_INT(a), &set_b);
    set_add(G_INT(b), &set_b);
    set_add(G_INT(c), &set_b);
    
    set_add(G_INT(a), &expected_set_a);
    set_add(G_INT(b), &expected_set_a);
    
    set_add(G_INT(a), &expected_set_b);
    set_add(G_INT(b), &expected_set_b);
    set_add(G_INT(c), &expected_set_b);
    
    bool superset = false;
    
    /* is b a superset of a? */
    unsigned int res = set_superset(&superset, &set_a, &set_b);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && superset)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_superset_null_params(void)
{
    bool pass = false;
    
    unsigned int res = set_superset(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_superset_improper_superset(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    
    set_add(G_INT(a), &set_a);
    set_add(G_INT(b), &set_a);
    set_add(G_INT(c), &set_a);
    
    set_add(G_INT(a), &set_b);
    set_add(G_INT(b), &set_b);
    set_add(G_INT(c), &set_b);
    
    set_add(G_INT(a), &expected_set_a);
    set_add(G_INT(b), &expected_set_a);
    set_add(G_INT(c), &expected_set_a);
    
    set_add(G_INT(a), &expected_set_b);
    set_add(G_INT(b), &expected_set_b);
    set_add(G_INT(c), &expected_set_b);
    
    bool superset = false;
    
    /* is b a superset of a? */
    unsigned int res = set_superset(&superset, &set_a, &set_b);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && superset)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_superset_empty_sets(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    bool superset = false;
    
    /* is b a superset of a? */
    unsigned int res = set_superset(&superset, &set_a, &set_b);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && superset)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_superset_of_empty_set(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    
    set_add(G_INT(a), &set_b);
    set_add(G_INT(b), &set_b);
    
    set_add(G_INT(a), &expected_set_b);
    set_add(G_INT(b), &expected_set_b);
    
    bool superset = false;
    
    /* is b a superset of a? */
    unsigned int res = set_superset(&superset, &set_a, &set_b);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && superset)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_superset_empty_set_of(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    
    set_add(G_INT(a), &set_a);
    set_add(G_INT(b), &set_a);
    set_add(G_INT(c), &set_a);
    
    set_add(G_INT(a), &expected_set_a);
    set_add(G_INT(b), &expected_set_a);
    set_add(G_INT(c), &expected_set_a);
    
    bool superset = false;
    
    /* is b a superset of a? */
    unsigned int res = set_superset(&superset, &set_a, &set_b);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && !superset)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_superset_same_set(void)
{
    bool pass = false;
    
    Set set;
    set_init(&set);
    
    Set expected_set;
    set_init(&expected_set);

    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    
    set_add(G_INT(a), &set);
    set_add(G_INT(b), &set);
    set_add(G_INT(c), &set);
    
    set_add(G_INT(a), &expected_set);
    set_add(G_INT(b), &expected_set);
    set_add(G_INT(c), &expected_set);

    bool superset = false;
    
    /* is set a superset of itself? */
    unsigned int res = set_superset(&superset, &set, &set);
    
    bool equal = false;
    set_equal(&equal, &set, &expected_set);
    
    set_free(NULL, &set);
    set_free(NULL, &expected_set);
    
    if(res == JCRL_ERR_OK && equal && superset)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_cardinality_normal(void)
{
    bool pass = false;
    
    Set set;
    set_init(&set);
    
    Set expected_set;
    set_init(&expected_set);
    
    unsigned int* a = calloc(1, sizeof(unsigned int));
    unsigned int* b = calloc(1, sizeof(unsigned int));

    /* arbitrary values to insert */
    *a = 12;
    *b = 33;
    
    set_add((void*)a, &set);
    set_add((void*)b, &set);
    
    set_add((void*)a, &expected_set);
    set_add((void*)b, &expected_set);
    
    unsigned int card = 0;
    
    unsigned int res = set_cardinality(&card, &set);
    
    bool equal = false;
    set_equal(&equal, &set, &expected_set);
    
    set_free(NULL, &set);
    set_free(NULL, &expected_set);
    
    if(res == JCRL_ERR_OK && equal && card == 2)
    {
        pass = true;
    }
    
    free(a);
    free(b);

    return pass;
}

bool test_set_cardinality_null_params(void)
{
    bool pass = false;
    
    unsigned int res = set_cardinality(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_cardinality_empty_set(void)
{
    bool pass = false;
    
    Set set;
    set_init(&set);
    
    Set expected_set;
    set_init(&expected_set);
    
    unsigned int card = 1; /* different from expected value */
    
    unsigned int res = set_cardinality(&card, &set);
    
    bool equal = false;
    set_equal(&equal, &set, &expected_set);
    
    set_free(NULL, &set);
    set_free(NULL, &expected_set);
    
    if(res == JCRL_ERR_OK && equal && card == 0)
    {
        pass = true;
    }
    
    return pass;
}

/* Operations */
bool test_set_add_normal(void)
{
    bool pass = false;
    
    Set set;
    set_init(&set);
    
    Set expected_set;
    set_init(&expected_set);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    unsigned int res = set_add(G_INT(a), &set);
    
    set_add(G_INT(a), &expected_set);
    
    bool equal = false;
    set_equal(&equal, &set, &expected_set);
    
    set_free(NULL, &set);
    set_free(NULL, &expected_set);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_add_null_params(void)
{
    bool pass = false;
    
    unsigned int res = set_add(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_add_duplicates(void)
{
    bool pass = false;
    
    Set set;
    set_init(&set);
    
    Set expected_set;
    set_init(&expected_set);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    set_add(G_INT(a), &set);
    
    unsigned int res = set_add(G_INT(a), &set);
    
    set_add(G_INT(a), &expected_set);
    
    bool equal = false;
    set_equal(&equal, &set, &expected_set);
    
    set_free(NULL, &set);
    set_free(NULL, &expected_set);
    
    if(res == JCRL_ERR_IMPOSSIBLE && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_remove_normal(void)
{
    bool pass = false;
    
    Set set;
    set_init(&set);
    
    Set expected_set;
    set_init(&expected_set);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    
    set_add(G_INT(a), &set);
    set_add(G_INT(b), &set);
    
    set_add(G_INT(a), &expected_set);
    
    unsigned int res = set_remove(G_INT(b), &set);
    
    bool equal = false;
    set_equal(&equal, &set, &expected_set);
    
    set_free(NULL, &set);
    set_free(NULL, &expected_set);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_remove_null_params(void)
{
    bool pass = false;
    
    unsigned int res = set_remove(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_remove_empty_set(void)
{
    bool pass = false;
    
    Set set;
    set_init(&set);
    
    Set expected_set;
    set_init(&expected_set);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    unsigned int res = set_remove(G_INT(a), &set);
    
    bool equal = false;
    set_equal(&equal, &set, &expected_set);
    
    set_free(NULL, &set);
    set_free(NULL, &expected_set);
    
    if(res == JCRL_ERR_NOT_FOUND && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_union_normal(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    Set set_c;
    set_init(&set_c);
    
    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    Set expected_set_c;
    set_init(&expected_set_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    unsigned int d = 2;
    
    set_add(G_INT(a), &set_a);
    set_add(G_INT(b), &set_a);
    
    set_add(G_INT(a), &expected_set_a);
    set_add(G_INT(b), &expected_set_a);
    
    set_add(G_INT(c), &set_b);
    set_add(G_INT(d), &set_b);
    
    set_add(G_INT(c), &expected_set_b);
    set_add(G_INT(d), &expected_set_b);
    
    set_add(G_INT(a), &expected_set_c);
    set_add(G_INT(b), &expected_set_c);
    set_add(G_INT(c), &expected_set_c);
    set_add(G_INT(d), &expected_set_c);
    
    unsigned int res = set_union(&set_a, &set_b, &set_c);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    bool equal_c = false;
    set_equal(&equal_c, &set_c, &expected_set_c);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &set_c);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    set_free(NULL, &expected_set_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_union_null_params(void)
{
    bool pass = false;
    
    unsigned int res = set_union(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_union_empty_sets(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    Set set_c;
    set_init(&set_c);
    
    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    Set expected_set_c;
    set_init(&expected_set_c);
    
    unsigned int res = set_union(&set_a, &set_b, &set_c);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    bool equal_c = false;
    set_equal(&equal_c, &set_c, &expected_set_c);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &set_c);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    set_free(NULL, &expected_set_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_union_same_set(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);

    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
        
    set_add(G_INT(a), &set_a);
    set_add(G_INT(b), &set_a);
    
    set_add(G_INT(a), &expected_set_a);
    set_add(G_INT(b), &expected_set_a);
    
    set_add(G_INT(a), &expected_set_b);
    set_add(G_INT(b), &expected_set_b);
    
    unsigned int res = set_union(&set_a, &set_a, &set_b);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_intersection_normal(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    Set set_c;
    set_init(&set_c);
    
    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    Set expected_set_c;
    set_init(&expected_set_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    
    set_add(G_INT(a), &set_a);
    set_add(G_INT(b), &set_a);
    
    set_add(G_INT(a), &expected_set_a);
    set_add(G_INT(b), &expected_set_a);
    
    set_add(G_INT(a), &set_b);
    set_add(G_INT(c), &set_b);
    
    set_add(G_INT(a), &expected_set_b);
    set_add(G_INT(c), &expected_set_b);
    
    set_add(G_INT(a), &expected_set_c);
    
    unsigned int res = set_intersection(&set_a, &set_b, &set_c);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    bool equal_c = false;
    set_equal(&equal_c, &set_c, &expected_set_c);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &set_c);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    set_free(NULL, &expected_set_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_intersection_null_params(void)
{
    bool pass = false;
    
    unsigned int res = set_intersection(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_intersection_empty_sets(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    Set set_c;
    set_init(&set_c);
    
    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    Set expected_set_c;
    set_init(&expected_set_c);
    
    unsigned int res = set_intersection(&set_a, &set_b, &set_c);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    bool equal_c = false;
    set_equal(&equal_c, &set_c, &expected_set_c);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &set_c);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    set_free(NULL, &expected_set_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_intersection_same_set(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);

    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
        
    set_add(G_INT(a), &set_a);
    set_add(G_INT(b), &set_a);
    
    set_add(G_INT(a), &expected_set_a);
    set_add(G_INT(b), &expected_set_a);
    
    set_add(G_INT(a), &expected_set_b);
    set_add(G_INT(b), &expected_set_b);
    
    unsigned int res = set_intersection(&set_a, &set_a, &set_b);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_difference_normal(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    Set set_c;
    set_init(&set_c);
    
    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    Set expected_set_c;
    set_init(&expected_set_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    
    set_add(G_INT(a), &set_a);
    set_add(G_INT(b), &set_a);
    set_add(G_INT(c), &set_a);
    
    set_add(G_INT(a), &expected_set_a);
    set_add(G_INT(b), &expected_set_a);
    set_add(G_INT(c), &expected_set_a);
    
    set_add(G_INT(b), &set_b);
    
    set_add(G_INT(b), &expected_set_b);
    
    set_add(G_INT(a), &expected_set_c);
    set_add(G_INT(c), &expected_set_c);
    
    unsigned int res = set_difference(&set_a, &set_b, &set_c);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    bool equal_c = false;
    set_equal(&equal_c, &set_c, &expected_set_c);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &set_c);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    set_free(NULL, &expected_set_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_difference_null_params(void)
{
    bool pass = false;
    
    unsigned int res = set_difference(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_difference_empty_sets(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    Set set_c;
    set_init(&set_c);
    
    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    Set expected_set_c;
    set_init(&expected_set_c);
    
    unsigned int res = set_difference(&set_a, &set_b, &set_c);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    bool equal_c = false;
    set_equal(&equal_c, &set_c, &expected_set_c);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &set_c);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    set_free(NULL, &expected_set_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_difference_same_set(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);

    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
        
    set_add(G_INT(a), &set_a);
    set_add(G_INT(b), &set_a);
    
    set_add(G_INT(a), &expected_set_a);
    set_add(G_INT(b), &expected_set_a);
    
    unsigned int res = set_difference(&set_a, &set_a, &set_b);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_difference_disjoint_sets(void)
{
    bool pass = false;
    
    Set set_a;
    set_init(&set_a);
    
    Set set_b;
    set_init(&set_b);
    
    Set set_c;
    set_init(&set_c);
    
    Set expected_set_a;
    set_init(&expected_set_a);
    
    Set expected_set_b;
    set_init(&expected_set_b);
    
    Set expected_set_c;
    set_init(&expected_set_c);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    
    set_add(G_INT(a), &set_a);
    
    set_add(G_INT(a), &expected_set_a);
    
    set_add(G_INT(b), &set_b);
    
    set_add(G_INT(b), &expected_set_b);
    
    set_add(G_INT(a), &expected_set_c);
    
    unsigned int res = set_difference(&set_a, &set_b, &set_c);
    
    bool equal_a = false;
    set_equal(&equal_a, &set_a, &expected_set_a);
    
    bool equal_b = false;
    set_equal(&equal_b, &set_b, &expected_set_b);
    
    bool equal_c = false;
    set_equal(&equal_c, &set_c, &expected_set_c);
    
    set_free(NULL, &set_a);
    set_free(NULL, &set_b);
    set_free(NULL, &set_c);
    set_free(NULL, &expected_set_a);
    set_free(NULL, &expected_set_b);
    set_free(NULL, &expected_set_c);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b && equal_c)
    {
        pass = true;
    }
    
    return pass;
}

/* Utilities */
bool test_set_enumerate_normal(void)
{
    bool pass = false;
    
    Set set;
    set_init(&set);
    
    Set expected_set;
    set_init(&expected_set);
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    
    set_add(G_INT(a), &set);
    set_add(G_INT(b), &set);
    set_add(G_INT(c), &set);
    
    set_add(G_INT(a), &expected_set);
    set_add(G_INT(b), &expected_set);
    set_add(G_INT(c), &expected_set);
    
    list_append(G_INT(a), &expected_list);
    list_append(G_INT(b), &expected_list);
    list_append(G_INT(c), &expected_list);
    
    unsigned int res = set_enumerate(&list, &set);
    
    bool equal_set = false;
    set_equal(&equal_set, &set, &expected_set);
    
    bool equal_list = false;
    list_equal(&equal_list, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    set_free(NULL, &set);
    set_free(NULL, &expected_set);
    
    if(res == JCRL_ERR_OK && equal_set && equal_list)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_enumerate_null_params(void)
{
    bool pass = false;
    
    unsigned int res = set_enumerate(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_set_enumerate_empty_set(void)
{
    bool pass = false;
    
    Set set;
    set_init(&set);
    
    Set expected_set;
    set_init(&expected_set);
    
    List list;
    list_init(&list);
    
    List expected_list;
    list_init(&expected_list);
    
    unsigned int res = set_enumerate(&list, &set);
    
    bool equal_set = false;
    set_equal(&equal_set, &set, &expected_set);
    
    bool equal_list = false;
    list_equal(&equal_list, &list, &expected_list);
    
    list_free(NULL, &list);
    list_free(NULL, &expected_list);
    
    set_free(NULL, &set);
    set_free(NULL, &expected_set);
    
    if(res == JCRL_ERR_OK && equal_set && equal_list)
    {
        pass = true;
    }
    
    return pass;
}
