#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unit_digraph.h"

/* test names */
const char* tests[UNIT_DIGRAPH_NUM_TESTS] = {
    "test_digraph_init_normal",
    "test_digraph_init_null_params",
    "test_digraph_free_normal",
    "test_digraph_free_null_params",
    "test_digraph_vertex_get_normal",
    "test_digraph_vertex_get_null_params",
    "test_digraph_vertex_get_out_of_bounds",
    "test_digraph_vertex_set_normal",
    "test_digraph_vertex_set_null_params",
    "test_digraph_vertex_set_out_of_bounds",
    "test_digraph_edge_get_normal",
    "test_digraph_edge_get_null_params",
    "test_digraph_edge_get_out_of_bounds",
    "test_digraph_edge_set_normal",
    "test_digraph_edge_set_null_params",
    "test_digraph_edge_set_out_of_bounds",
    "test_digraph_order_normal",
    "test_digraph_order_null_params",
    "test_digraph_order_empty",
    "test_digraph_size_normal",
    "test_digraph_size_null_params",
    "test_digraph_size_empty",
    "test_digraph_equal_normal",
    "test_digraph_equal_null_params",
    "test_digraph_equal_empty_graphs",
    "test_digraph_equal_not_equal",
    "test_digraph_equal_reordered",
    "test_digraph_vertex_in_normal",
    "test_digraph_vertex_in_null_params",
    "test_digraph_vertex_in_not_found",
    "test_digraph_edge_in_normal",
    "test_digraph_edge_in_null_params",
    "test_digraph_edge_in_not_found",
    "test_digraph_vertex_insert_normal",
    "test_digraph_vertex_insert_null_params",
    "test_digraph_vertex_insert_empty",
    "test_digraph_vertex_remove_normal",
    "test_digraph_vertex_remove_null_params",
    "test_digraph_vertex_remove_out_of_bounds",
    "test_digraph_vertex_remove_empty",
    "test_digraph_connect_normal",
    "test_digraph_connect_null_params",
    "test_digraph_connect_out_of_bounds",
    "test_digraph_connect_loop_edge",
    "test_digraph_connect_multiple_edge",
    "test_digraph_disconnect_normal",
    "test_digraph_disconnect_null_params",
    "test_digraph_disconnect_out_of_bounds",
    "test_digraph_disconnect_empty",
    "test_digraph_in_neighbours_normal",
    "test_digraph_in_neighbours_null_params",
    "test_digraph_in_neighbours_out_of_bounds",
    "test_digraph_out_neighbours_normal",
    "test_digraph_out_neighbours_null_params",
    "test_digraph_out_neighbours_out_of_bounds",
    "test_digraph_adjacent_normal",
    "test_digraph_adjacent_null_params",
    "test_digraph_adjacent_out_of_bounds",
    "test_digraph_adjacent_nonadjacent",
    "test_digraph_adjacent_via_normal",
    "test_digraph_adjacent_via_null_params",
    "test_digraph_adjacent_via_out_of_bounds",
    "test_digraph_adjacent_via_nonadjacent",
    "test_digraph_adjacent_via_loop_edge",
    "test_digraph_adjacent_via_multiple_edge",
    "test_digraph_incident_normal",
    "test_digraph_incident_null_params",
    "test_digraph_incident_out_of_bounds",
    "test_digraph_incident_nonincident",
    "test_digraph_incident_loop_edge",
    "test_digraph_endpoints_normal",
    "test_digraph_endpoints_null_params",
    "test_digraph_endpoints_out_of_bounds",
    "test_digraph_endpoints_loop_edge",
    "test_digraph_in_degree_normal",
    "test_digraph_in_degree_null_params",
    "test_digraph_in_degree_out_of_bounds",
    "test_digraph_in_degree_zero",
    "test_digraph_in_degree_loop_edge",
    "test_digraph_in_degree_multiple_edge",
    "test_digraph_out_degree_normal",
    "test_digraph_out_degree_null_params",
    "test_digraph_out_degree_out_of_bounds",
    "test_digraph_out_degree_zero",
    "test_digraph_out_degree_loop_edge",
    "test_digraph_out_degree_multiple_edge",
    "test_digraph_incident_edges_normal",
    "test_digraph_incident_edges_null_params",
    "test_digraph_incident_edges_out_of_bounds",
    "test_digraph_incident_edges_zero",
    "test_digraph_incident_edges_loop_edge",
    "test_digraph_incident_edges_multiple_edge",
    "test_digraph_find_vertices_normal",
    "test_digraph_find_vertices_null_params",
    "test_digraph_find_vertices_not_found",
    "test_digraph_find_edges_normal",
    "test_digraph_find_edges_null_params",
    "test_digraph_find_edges_not_found"
};

int main(void)
{
    unsigned int t = 0;
    bool results[UNIT_DIGRAPH_NUM_TESTS];
    memset(results, 0, sizeof(bool) * UNIT_DIGRAPH_NUM_TESTS);

    results[t] = test_digraph_init_normal();
    t++;
    results[t] = test_digraph_init_null_params();
    t++;

    results[t] = test_digraph_free_normal();
    t++;
    results[t] = test_digraph_free_null_params();
    t++;

    results[t] = test_digraph_vertex_get_normal();
    t++;
    results[t] = test_digraph_vertex_get_null_params();
    t++;
    results[t] = test_digraph_vertex_get_out_of_bounds();
    t++;

    results[t] = test_digraph_vertex_set_normal();
    t++;
    results[t] = test_digraph_vertex_set_null_params();
    t++;
    results[t] = test_digraph_vertex_set_out_of_bounds();
    t++;

    results[t] = test_digraph_edge_get_normal();
    t++;
    results[t] = test_digraph_edge_get_null_params();
    t++;
    results[t] = test_digraph_edge_get_out_of_bounds();
    t++;

    results[t] = test_digraph_edge_set_normal();
    t++;
    results[t] = test_digraph_edge_set_null_params();
    t++;
    results[t] = test_digraph_edge_set_out_of_bounds();
    t++;

    results[t] = test_digraph_order_normal();
    t++;
    results[t] = test_digraph_order_null_params();
    t++;
    results[t] = test_digraph_order_empty();
    t++;

    results[t] = test_digraph_size_normal();
    t++;
    results[t] = test_digraph_size_null_params();
    t++;
    results[t] = test_digraph_size_empty();
    t++;

    results[t] = test_digraph_equal_normal();
    t++;
    results[t] = test_digraph_equal_null_params();
    t++;
    results[t] = test_digraph_equal_empty_graphs();
    t++;
    results[t] = test_digraph_equal_not_equal();
    t++;
    results[t] = test_digraph_equal_reordered();
    t++;

    results[t] = test_digraph_vertex_in_normal();
    t++;
    results[t] = test_digraph_vertex_in_null_params();
    t++;
    results[t] = test_digraph_vertex_in_not_found();
    t++;

    results[t] = test_digraph_edge_in_normal();
    t++;
    results[t] = test_digraph_edge_in_null_params();
    t++;
    results[t] = test_digraph_edge_in_not_found();
    t++;

    results[t] = test_digraph_vertex_insert_normal();
    t++;
    results[t] = test_digraph_vertex_insert_null_params();
    t++;
    results[t] = test_digraph_vertex_insert_empty();
    t++;

    results[t] = test_digraph_vertex_remove_normal();
    t++;
    results[t] = test_digraph_vertex_remove_null_params();
    t++;
    results[t] = test_digraph_vertex_remove_out_of_bounds();
    t++;
    results[t] = test_digraph_vertex_remove_empty();
    t++;

    results[t] = test_digraph_connect_normal();
    t++;
    results[t] = test_digraph_connect_null_params();
    t++;
    results[t] = test_digraph_connect_out_of_bounds();
    t++;
    results[t] = test_digraph_connect_loop_edge();
    t++;
    results[t] = test_digraph_connect_multiple_edge();
    t++;

    results[t] = test_digraph_disconnect_normal();
    t++;
    results[t] = test_digraph_disconnect_null_params();
    t++;
    results[t] = test_digraph_disconnect_out_of_bounds();
    t++;
    results[t] = test_digraph_disconnect_empty();
    t++;

    results[t] = test_digraph_in_neighbours_normal();
    t++;
    results[t] = test_digraph_in_neighbours_null_params();
    t++;
    results[t] = test_digraph_in_neighbours_out_of_bounds();
    t++;
 
    results[t] = test_digraph_out_neighbours_normal();
    t++;
    results[t] = test_digraph_out_neighbours_null_params();
    t++;
    results[t] = test_digraph_out_neighbours_out_of_bounds();
    t++;

    results[t] = test_digraph_adjacent_normal();
    t++;
    results[t] = test_digraph_adjacent_null_params();
    t++;
    results[t] = test_digraph_adjacent_out_of_bounds();
    t++;
    results[t] = test_digraph_adjacent_nonadjacent();
    t++;

    results[t] = test_digraph_adjacent_via_normal();
    t++;
    results[t] = test_digraph_adjacent_via_null_params();
    t++;
    results[t] = test_digraph_adjacent_via_out_of_bounds();
    t++;
    results[t] = test_digraph_adjacent_via_nonadjacent();
    t++;
    results[t] = test_digraph_adjacent_via_loop_edge();
    t++;
    results[t] = test_digraph_adjacent_via_multiple_edge();
    t++;

    results[t] = test_digraph_incident_normal();
    t++;
    results[t] = test_digraph_incident_null_params();
    t++;
    results[t] = test_digraph_incident_out_of_bounds();
    t++;
    results[t] = test_digraph_incident_nonincident();
    t++;
    results[t] = test_digraph_incident_loop_edge();
    t++;

    results[t] = test_digraph_endpoints_normal();
    t++;
    results[t] = test_digraph_endpoints_null_params();
    t++;
    results[t] = test_digraph_endpoints_out_of_bounds();
    t++;
    results[t] = test_digraph_endpoints_loop_edge();
    t++;

    results[t] = test_digraph_in_degree_normal();
    t++;
    results[t] = test_digraph_in_degree_null_params();
    t++;
    results[t] = test_digraph_in_degree_out_of_bounds();
    t++;
    results[t] = test_digraph_in_degree_zero();
    t++;
    results[t] = test_digraph_in_degree_loop_edge();
    t++;
    results[t] = test_digraph_in_degree_multiple_edge();
    t++;

    results[t] = test_digraph_out_degree_normal();
    t++;
    results[t] = test_digraph_out_degree_null_params();
    t++;
    results[t] = test_digraph_out_degree_out_of_bounds();
    t++;
    results[t] = test_digraph_out_degree_zero();
    t++;
    results[t] = test_digraph_out_degree_loop_edge();
    t++;
    results[t] = test_digraph_out_degree_multiple_edge();
    t++;

    results[t] = test_digraph_incident_edges_normal();
    t++;
    results[t] = test_digraph_incident_edges_null_params();
    t++;
    results[t] = test_digraph_incident_edges_out_of_bounds();
    t++;
    results[t] = test_digraph_incident_edges_zero();
    t++;
    results[t] = test_digraph_incident_edges_loop_edge();
    t++;
    results[t] = test_digraph_incident_edges_multiple_edge();
    t++;

    results[t] = test_digraph_find_vertices_normal();
    t++;
    results[t] = test_digraph_find_vertices_null_params();
    t++;
    results[t] = test_digraph_find_vertices_not_found();
    t++;

    results[t] = test_digraph_find_edges_normal();
    t++;
    results[t] = test_digraph_find_edges_null_params();
    t++;
    results[t] = test_digraph_find_edges_not_found();

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
