/*
 * test_vertex.c
 * 
 * Test executable for the vertex implementation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "unit_vertex.h"

/* test names */
const char* tests[UNIT_VERTEX_NUM_TESTS] = {
                                    "test_vertex_init_normal",
                                    "test_vertex_init_null_params",
                                    "test_vertex_free_normal",
                                    "test_vertex_free_null_params",
                                    "test_vertex_equal_normal",
                                    "test_vertex_equal_null_params",
                                    "test_vertex_equal_unequal_vertices",
                                    "test_vertex_equal_empty_vertices",
                                    "test_vertex_equal_same_vertex",
                                    "test_vertex_get_normal",
                                    "test_vertex_get_null_params",
                                    "test_vertex_set_normal",
                                    "test_vertex_set_null_params",
                                    "test_vertex_degree_normal",
                                    "test_vertex_degree_null_params",
                                    "test_vertex_add_neighbour_normal",
                                    "test_vertex_add_neighbour_null_params",
                                    "test_vertex_remove_neighbour_normal",
                                    "test_vertex_remove_neighbour_null_params",
                                    "test_vertex_remove_neighbour_not_found"
                                    };

int main(void)
{
    unsigned int t = 0;
    bool results[UNIT_VERTEX_NUM_TESTS];
    memset(results, 0, sizeof(bool) * UNIT_VERTEX_NUM_TESTS);
    
    /* Initialisation */
    results[t] = test_vertex_init_normal();
    t++;
    results[t] = test_vertex_init_null_params();
    t++;
    
    results[t] = test_vertex_free_normal();
    t++;
    results[t] = test_vertex_free_null_params();
    t++;
    
    /* Equality */
    results[t] = test_vertex_equal_normal();
    t++;
    results[t] = test_vertex_equal_null_params();
    t++;
    results[t] = test_vertex_equal_unequal_vertices();
    t++;
    results[t] = test_vertex_equal_empty_vertices();
    t++;
    results[t] = test_vertex_equal_same_vertex();
    t++;
    
    /* Access */
    results[t] = test_vertex_get_normal();
    t++;
    results[t] = test_vertex_get_null_params();
    t++;
    
    results[t] = test_vertex_set_normal();
    t++;
    results[t] = test_vertex_set_null_params();
    t++;
    
    results[t] = test_vertex_degree_normal();
    t++;
    results[t] = test_vertex_degree_null_params();
    t++;
    
    /* Operations */
    results[t] = test_vertex_add_neighbour_normal();
    t++;
    results[t] = test_vertex_add_neighbour_null_params();
    t++;
    
    results[t] = test_vertex_remove_neighbour_normal();
    t++;
    results[t] = test_vertex_remove_neighbour_null_params();
    t++;
    results[t] = test_vertex_remove_neighbour_not_found();
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
