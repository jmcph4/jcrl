/*
 * test_set.c
 * 
 * Test executable for the set implementation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "unit_set.h"

/* test names */
const char* tests[UNIT_SET_NUM_TESTS] = {
                                    "test_set_init_normal",
                                    "test_set_init_null_params",
                                    "test_set_free_normal",
                                    "test_set_free_null_params",
                                    "test_set_equal_normal",
                                    "test_set_equal_null_params",
                                    "test_set_equal_empty_sets",
                                    "test_set_equal_unequal_sets",
                                    "test_set_equal_same_set",
                                    "test_set_in_normal",
                                    "test_set_in_null_params",
                                    "test_set_in_empty_set",
                                    "test_set_in_not_found",
                                    "test_set_subset_normal",
                                    "test_set_subset_null_params",
                                    "test_set_subset_improper_subset",
                                    "test_set_subset_empty_sets",
                                    "test_set_subset_of_empty_set",
                                    "test_set_subset_empty_set_of",
                                    "test_set_subset_same_set",
                                    "test_set_superset_normal",
                                    "test_set_superset_null_params",
                                    "test_set_superset_improper_superset",
                                    "test_set_superset_empty_sets",
                                    "test_set_superset_of_empty_set",
                                    "test_set_superset_empty_set_of",
                                    "test_set_superset_same_set",
                                    "test_set_cardinality_normal",
                                    "test_set_cardinality_null_params",
                                    "test_set_cardinality_empty_set",
                                    "test_set_add_normal",
                                    "test_set_add_null_params",
                                    "test_set_add_duplicates",
                                    "test_set_remove_normal",
                                    "test_set_remove_null_params",
                                    "test_set_remove_empty_set",
                                    "test_set_union_normal",
                                    "test_set_union_null_params",
                                    "test_set_union_empty_sets",
                                    "test_set_union_same_set",
                                    "test_set_intersection_normal",
                                    "test_set_intersection_null_params",
                                    "test_set_intersection_empty_sets",
                                    "test_set_intersection_same_set",
                                    "test_set_difference_normal",
                                    "test_set_difference_null_params",
                                    "test_set_difference_empty_sets",
                                    "test_set_difference_same_set",
                                    "test_set_difference_disjoint_sets",
                                    "test_set_enumerate_normal",
                                    "test_set_enumerate_null_params",
                                    "test_set_enumerate_empty_set"
};

int main(void)
{
    unsigned int t = 0;
    bool results[UNIT_SET_NUM_TESTS];
    memset(results, 0, sizeof(bool) * UNIT_SET_NUM_TESTS);
    
    /* Initialisation */
    results[t] = test_set_init_normal();
    t++;
    results[t] = test_set_init_null_params();
    t++;
    results[t] = test_set_free_normal();
    t++;
    results[t] = test_set_free_null_params();
    t++;
    
    /* Equality */
    results[t] = test_set_equal_normal();
    t++;
    results[t] = test_set_equal_null_params();
    t++;
    results[t] = test_set_equal_empty_sets();
    t++;
    results[t] = test_set_equal_unequal_sets();
    t++;
    results[t] = test_set_equal_same_set();
    t++;
    
    /* Membership */
    results[t] = test_set_in_normal();
    t++;
    results[t] = test_set_in_null_params();
    t++;
    results[t] = test_set_in_empty_set();
    t++;
    results[t] = test_set_in_not_found();
    t++;
    results[t] = test_set_subset_normal();
    t++;
    results[t] = test_set_subset_null_params();
    t++;
    results[t] = test_set_subset_improper_subset();
    t++;
    results[t] = test_set_subset_empty_sets();
    t++;
    results[t] = test_set_subset_of_empty_set();
    t++;
    results[t] = test_set_subset_empty_set_of();
    t++;
    results[t] = test_set_subset_same_set();
    t++;
    results[t] = test_set_superset_normal();
    t++;
    results[t] = test_set_superset_null_params();
    t++;
    results[t] = test_set_superset_improper_superset();
    t++;
    results[t] = test_set_superset_empty_sets();
    t++;
    results[t] = test_set_superset_of_empty_set();
    t++;
    results[t] = test_set_superset_empty_set_of();
    t++;
    results[t] = test_set_superset_same_set();
    t++;

    /* Size */
    results[t] = test_set_cardinality_normal();
    t++;
    results[t] = test_set_cardinality_null_params();
    t++;
    results[t] = test_set_cardinality_empty_set();
    t++;
    
    /* Operations */
    results[t] = test_set_add_normal();
    t++;
    results[t] = test_set_add_null_params();
    t++;
    results[t] = test_set_add_duplicates();
    t++;
    results[t] = test_set_remove_normal();
    t++;
    results[t] = test_set_remove_null_params();
    t++;
    results[t] = test_set_remove_empty_set();
    t++;
    results[t] = test_set_union_normal();
    t++;
    results[t] = test_set_union_null_params();
    t++;
    results[t] = test_set_union_empty_sets();
    t++;
    results[t] = test_set_union_same_set();
    t++;
    results[t] = test_set_intersection_normal();
    t++;
    results[t] = test_set_intersection_null_params();
    t++;
    results[t] = test_set_intersection_empty_sets();
    t++;
    results[t] = test_set_intersection_same_set();
    t++;
    results[t] = test_set_difference_normal();
    t++;
    results[t] = test_set_difference_null_params();
    t++;
    results[t] = test_set_difference_empty_sets();
    t++;
    results[t] = test_set_difference_same_set();
    t++;
    results[t] = test_set_difference_disjoint_sets();
    t++;
    
    /* Utilities */
    results[t] = test_set_enumerate_normal();
    t++;
    results[t] = test_set_enumerate_null_params();
    t++;
    results[t] = test_set_enumerate_empty_set();
    t++;
    
    /* check for test failure */
    for(unsigned int i=0;i<t;i++)
    {
        if(results[i])
        {
            printf("TEST %s: PASS\n", tests[i]);
        }
        else
        {
            printf("!TEST %s: FAIL\n", tests[i]);
        }
    }
    
    return EXIT_SUCCESS;
}
