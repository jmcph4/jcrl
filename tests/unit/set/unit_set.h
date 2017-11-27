/*
 * unit_set.h
 *
 * Declarations of unit tests for the set implementation. For unit test
 * definitions, see unit_set.c.
*/
#include <stdbool.h>

#define UNIT_SET_NUM_TESTS 52

/* Initialisation */
bool test_set_init_normal(void);
bool test_set_init_null_params(void);

bool test_set_free_normal(void);
bool test_set_free_null_params(void);

/* Equality */
bool test_set_equal_normal(void);
bool test_set_equal_null_params(void);
bool test_set_equal_empty_sets(void);
bool test_set_equal_unequal_sets(void);
bool test_set_equal_same_set(void);

/* Membership */
bool test_set_in_normal(void);
bool test_set_in_null_params(void);
bool test_set_in_empty_set(void);
bool test_set_in_not_found(void);

bool test_set_subset_normal(void);
bool test_set_subset_null_params(void);
bool test_set_subset_improper_subset(void);
bool test_set_subset_empty_sets(void);
bool test_set_subset_of_empty_set(void);
bool test_set_subset_empty_set_of(void);
bool test_set_subset_same_set(void);

bool test_set_superset_normal(void);
bool test_set_superset_null_params(void);
bool test_set_superset_improper_superset(void);
bool test_set_superset_empty_sets(void);
bool test_set_superset_of_empty_set(void);
bool test_set_superset_empty_set_of(void);
bool test_set_superset_same_set(void);

/* Size */
bool test_set_cardinality_normal(void);
bool test_set_cardinality_null_params(void);
bool test_set_cardinality_empty_set(void);

/* Operations */
bool test_set_add_normal(void);
bool test_set_add_null_params(void);
bool test_set_add_duplicates(void);

bool test_set_remove_normal(void);
bool test_set_remove_null_params(void);
bool test_set_remove_empty_set(void);

bool test_set_union_normal(void);
bool test_set_union_null_params(void);
bool test_set_union_empty_sets(void);
bool test_set_union_same_set(void);

bool test_set_intersection_normal(void);
bool test_set_intersection_null_params(void);
bool test_set_intersection_empty_sets(void);
bool test_set_intersection_same_set(void);

bool test_set_difference_normal(void);
bool test_set_difference_null_params(void);
bool test_set_difference_empty_sets(void);
bool test_set_difference_same_set(void);
bool test_set_difference_disjoint_sets(void);

/* Utilities */
bool test_set_enumerate_normal(void);
bool test_set_enumerate_null_params(void);
bool test_set_enumerate_empty_set(void);
