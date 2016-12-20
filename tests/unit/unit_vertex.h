/*
 * unit_vertex.h
 * 
 * Declarations of unit tests for the vertex implementation. For unit test
 * definitions, see unit_vertex.c.
 */
#include "vertex.h"

#define UNIT_VERTEX_NUM_TESTS 20

/* Initialisation */
bool test_vertex_init_normal(void);
bool test_vertex_init_null_params(void);

bool test_vertex_free_normal(void);
bool test_vertex_free_null_params(void);

/* Equality */
bool test_vertex_equal_normal(void);
bool test_vertex_equal_null_params(void);
bool test_vertex_equal_unequal_vertices(void);
bool test_vertex_equal_empty_vertices(void);
bool test_vertex_equal_same_vertex(void);

/* Access */
bool test_vertex_get_normal(void);
bool test_vertex_get_null_params(void);

bool test_vertex_set_normal(void);
bool test_vertex_set_null_params(void);

bool test_vertex_degree_normal(void);
bool test_vertex_degree_null_params(void);

/* Operations */
bool test_vertex_add_neighbour_normal(void);
bool test_vertex_add_neighbour_null_params(void);

bool test_vertex_remove_neighbour_normal(void);
bool test_vertex_remove_neighbour_null_params(void);
bool test_vertex_remove_neighbour_not_found(void);
