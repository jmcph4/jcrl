/*
 * test_multiset.c
 * 
 * Test executable for the multiset implementation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "unit_multiset.h"

/* test names */
const char* tests[UNIT_MULTISET_NUM_TESTS] = {
                                "test_multiset_init_normal",
                                "test_multiset_init_null_params",
                                "test_multiset_free_normal",
                                "test_multiset_free_null_params",
                                "test_multiset_init_list_normal",
                                "test_multiset_init_list_null_params",
                                "test_multiset_add_normal",
                                "test_multiset_add_null_params",
                                "test_multiset_remove_normal",
                                "test_multiset_remove_null_params",
                                "test_multiset_remove_not_found",
                                "test_multiset_union_normal",
                                "test_multiset_union_null_params",
                                "test_multiset_union_with_empty_set",
                                "test_multiset_union_empty_set_with",
                                "test_multiset_union_empty_sets",
                                "test_multiset_union_commutes",
                                "test_multiset_union_same_sets",
                                "test_multiset_intersection_normal",
                                "test_multiset_intersection_null_params",
                                "test_multiset_intersection_with_empty_set",
                                "test_multiset_intersection_empty_set_with",
                                "test_multiset_intersection_empty_sets",
                                "test_multiset_intersection_commutes",
                                "test_multiset_intersection_same_sets",
                                "test_multiset_difference_normal",
                                "test_multiset_difference_null_params",
                                "test_multiset_difference_with_empty_set",
                                "test_multiset_difference_empty_set_with",
                                "test_multiset_difference_empty_sets",
                                "test_multiset_difference_same_sets",
                                "test_multiset_sum_normal",
                                "test_multiset_sum_null_params",
                                "test_multiset_sum_with_empty_set",
                                "test_multiset_sum_empty_set_with",
                                "test_multiset_sum_empty_sets",
                                "test_multiset_sum_commutes",
                                "test_multiset_sum_same_sets",
                                "test_multiset_cardinality_normal",
                                "test_multiset_cardinality_null_params",
                                "test_multiset_cardinality_empty_set",
                                "test_multiset_multiplicity_normal",
                                "test_multiset_multiplicity_null_params",
                                "test_multiset_multiplicity_not_found",
                                "test_multiset_equal_normal",
                                "test_multiset_equal_null_params",
                                "test_multiset_equal_same_set",
                                "test_multiset_in_normal",
                                "test_multiset_in_null_params",
                                "test_multiset_in_not_found",
                                "test_multiset_subset_normal",
                                "test_multiset_subset_null_params",
                                "test_multiset_subset_improper_subset",
                                "test_multiset_subset_empty_sets",
                                "test_multiset_subset_of_empty_set",
                                "test_multiset_subset_empty_set_of",
                                "test_multiset_subset_same_set",
                                "test_multiset_superset_normal",
                                "test_multiset_superset_null_params",
                                "test_multiset_superset_improper_superset",
                                "test_multiset_superset_empty_sets",
                                "test_multiset_superset_of_empty_set",
                                "test_multiset_superset_empty_set_of",
                                "test_multiset_superset_same_set",
                                "test_multiset_enumerate_normal",
                                "test_multiset_enumerate_null_params",
                                "test_multiset_enumerate_empty_set"
                                };

int main(void)
{
    unsigned int t = 0;
    bool results[UNIT_MULTISET_NUM_TESTS];
    memset(results, 0, sizeof(bool) * UNIT_MULTISET_NUM_TESTS);
    
    /* Initialisation */
    results[t] = test_multiset_init_normal();
    t++;
    results[t] = test_multiset_init_null_params();
    t++;
    
    results[t] = test_multiset_free_normal();
    t++;
    results[t] = test_multiset_free_null_params();
    t++;
    
    results[t] = test_multiset_init_list_normal();
    t++;
    results[t] = test_multiset_init_list_null_params();
    t++;
    
    /* Operations */
    results[t] = test_multiset_add_normal();
    t++;
    results[t] = test_multiset_add_null_params();
    t++;
    
    results[t] = test_multiset_remove_normal();
    t++;
    results[t] = test_multiset_remove_null_params();
    t++;
    results[t] = test_multiset_remove_not_found();
    t++;
    
    results[t] = test_multiset_union_normal();
    t++;
    results[t] = test_multiset_union_null_params();
    t++;
    results[t] = test_multiset_union_with_empty_set();
    t++;
    results[t] = test_multiset_union_empty_set_with();
    t++;
    results[t] = test_multiset_union_empty_sets();
    t++;
    results[t] = test_multiset_union_commutes();
    t++;
    results[t] = test_multiset_union_same_sets();
    t++;
    
    results[t] = test_multiset_intersection_normal();
    t++;
    results[t] = test_multiset_intersection_null_params();
    t++;
    results[t] = test_multiset_intersection_with_empty_set();
    t++;
    results[t] = test_multiset_intersection_empty_set_with();
    t++;
    results[t] = test_multiset_intersection_empty_sets();
    t++;
    results[t] = test_multiset_intersection_commutes();
    t++;
    results[t] = test_multiset_intersection_same_sets();
    t++;
    
    results[t] = test_multiset_difference_normal();
    t++;
    results[t] = test_multiset_difference_null_params();
    t++;
    results[t] = test_multiset_difference_with_empty_set();
    t++;
    results[t] = test_multiset_difference_empty_set_with();
    t++;
    results[t] = test_multiset_difference_empty_sets();
    t++;
    results[t] = test_multiset_difference_same_sets();
    t++;
    
    results[t] = test_multiset_sum_normal();
    t++;
    results[t] = test_multiset_sum_null_params();
    t++;
    results[t] = test_multiset_sum_with_empty_set();
    t++;
    results[t] = test_multiset_sum_empty_set_with();
    t++;
    results[t] = test_multiset_sum_empty_sets();
    t++;
    results[t] = test_multiset_sum_commutes();
    t++;
    results[t] = test_multiset_sum_same_sets();
    t++;
    
    /* Size */
    results[t] = test_multiset_cardinality_normal();
    t++;
    results[t] = test_multiset_cardinality_null_params();
    t++;
    results[t] = test_multiset_cardinality_empty_set();
    t++;
    results[t] = test_multiset_multiplicity_normal();
    t++;
    results[t] = test_multiset_multiplicity_null_params();
    t++;
    results[t] = test_multiset_multiplicity_not_found();
    t++;
    
    results[t] = test_multiset_equal_normal();
    t++;
    results[t] = test_multiset_equal_null_params();
    t++;
    results[t] = test_multiset_equal_same_set();
    t++;
    
    /* Membership */
    results[t] = test_multiset_in_normal();
    t++;
    results[t] = test_multiset_in_null_params();
    t++;
    results[t] = test_multiset_in_not_found();
    t++;
    
    results[t] = test_multiset_subset_normal();
    t++;
    results[t] = test_multiset_subset_null_params();
    t++;
    results[t] = test_multiset_subset_improper_subset();
    t++;
    results[t] = test_multiset_subset_empty_sets();
    t++;
    results[t] = test_multiset_subset_of_empty_set();
    t++;
    results[t] = test_multiset_subset_empty_set_of();
    t++;
    results[t] = test_multiset_subset_same_set();
    t++;

    results[t] = test_multiset_superset_normal();
    t++;
    results[t] = test_multiset_superset_null_params();
    t++;
    results[t] = test_multiset_superset_improper_superset();
    t++;
    results[t] = test_multiset_superset_empty_sets();
    t++;
    results[t] = test_multiset_superset_of_empty_set();
    t++;
    results[t] = test_multiset_superset_empty_set_of();
    t++;
    results[t] = test_multiset_superset_same_set();
    t++;

    /* Utilities */
    results[t] = test_multiset_enumerate_normal();
    t++;
    results[t] = test_multiset_enumerate_null_params();
    t++;
    results[t] = test_multiset_enumerate_empty_set();
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
