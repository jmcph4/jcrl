/*
 * unit_multiset.h
 *
 * Declarations of unit tests for the multiset implementation. For unit test 
 * definitions, see unit_multiset.c.
*/
#include "multiset.h"

#define UNIT_MULTISET_NUM_TESTS 67

/* Initialisation */
bool test_multiset_init_normal(void);
bool test_multiset_init_null_params(void);

bool test_multiset_free_normal(void);
bool test_multiset_free_null_params(void);

bool test_multiset_init_list_normal(void);
bool test_multiset_init_list_null_params(void);

/* Operations */
bool test_multiset_add_normal(void);
bool test_multiset_add_null_params(void);

bool test_multiset_remove_normal(void);
bool test_multiset_remove_null_params(void);
bool test_multiset_remove_not_found(void);

bool test_multiset_union_normal(void);
bool test_multiset_union_null_params(void);
bool test_multiset_union_with_empty_set(void);
bool test_multiset_union_empty_set_with(void);
bool test_multiset_union_empty_sets(void);
bool test_multiset_union_commutes(void);
bool test_multiset_union_same_sets(void);

bool test_multiset_intersection_normal(void);
bool test_multiset_intersection_null_params(void);
bool test_multiset_intersection_with_empty_set(void);
bool test_multiset_intersection_empty_set_with(void);
bool test_multiset_intersection_empty_sets(void);
bool test_multiset_intersection_commutes(void);
bool test_multiset_intersection_same_sets(void);

bool test_multiset_difference_normal(void);
bool test_multiset_difference_null_params(void);
bool test_multiset_difference_with_empty_set(void);
bool test_multiset_difference_empty_set_with(void);
bool test_multiset_difference_empty_sets(void);
bool test_multiset_difference_same_sets(void);

bool test_multiset_sum_normal(void);
bool test_multiset_sum_null_params(void);
bool test_multiset_sum_with_empty_set(void);
bool test_multiset_sum_empty_set_with(void);
bool test_multiset_sum_empty_sets(void);
bool test_multiset_sum_commutes(void);
bool test_multiset_sum_same_sets(void);

/* Size */
bool test_multiset_cardinality_normal(void);
bool test_multiset_cardinality_null_params(void);
bool test_multiset_cardinality_empty_set(void);

bool test_multiset_multiplicity_normal(void);
bool test_multiset_multiplicity_null_params(void);
bool test_multiset_multiplicity_not_found(void);

/* Equality */
bool test_multiset_equal_normal(void);
bool test_multiset_equal_null_params(void);
bool test_multiset_equal_same_set(void);

/* Membership */
bool test_multiset_in_normal(void);
bool test_multiset_in_null_params(void);
bool test_multiset_in_not_found(void);

bool test_multiset_subset_normal(void);
bool test_multiset_subset_null_params(void);
bool test_multiset_subset_improper_subset(void);
bool test_multiset_subset_empty_sets(void);
bool test_multiset_subset_of_empty_set(void);
bool test_multiset_subset_empty_set_of(void);
bool test_multiset_subset_same_set(void);

bool test_multiset_superset_normal(void);
bool test_multiset_superset_null_params(void);
bool test_multiset_superset_improper_superset(void);
bool test_multiset_superset_empty_sets(void);
bool test_multiset_superset_of_empty_set(void);
bool test_multiset_superset_empty_set_of(void);
bool test_multiset_superset_same_set(void);

/* Utilities */
bool test_multiset_enumerate_normal(void);
bool test_multiset_enumerate_null_params(void);
bool test_multiset_enumerate_empty_set(void);
