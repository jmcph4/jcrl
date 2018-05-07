#include <stdbool.h>

#define UNIT_DIGRAPH_NUM_TESTS 98

bool test_digraph_init_normal(void);
bool test_digraph_init_null_params(void);

bool test_digraph_free_normal(void);
bool test_digraph_free_null_params(void);

bool test_digraph_vertex_get_normal(void);
bool test_digraph_vertex_get_null_params(void);
bool test_digraph_vertex_get_out_of_bounds(void);

bool test_digraph_vertex_set_normal(void);
bool test_digraph_vertex_set_null_params(void);
bool test_digraph_vertex_set_out_of_bounds(void);

bool test_digraph_edge_get_normal(void);
bool test_digraph_edge_get_null_params(void);
bool test_digraph_edge_get_out_of_bounds(void);

bool test_digraph_edge_set_normal(void);
bool test_digraph_edge_set_null_params(void);
bool test_digraph_edge_set_out_of_bounds(void);

bool test_digraph_order_normal(void);
bool test_digraph_order_null_params(void);
bool test_digraph_order_empty(void);

bool test_digraph_size_normal(void);
bool test_digraph_size_null_params(void);
bool test_digraph_size_empty(void);

bool test_digraph_equal_normal(void);
bool test_digraph_equal_null_params(void);
bool test_digraph_equal_empty_graphs(void);
bool test_digraph_equal_not_equal(void);
bool test_digraph_equal_reordered(void);

bool test_digraph_vertex_in_normal(void);
bool test_digraph_vertex_in_null_params(void);
bool test_digraph_vertex_in_not_found(void);

bool test_digraph_edge_in_normal(void);
bool test_digraph_edge_in_null_params(void);
bool test_digraph_edge_in_not_found(void);

bool test_digraph_vertex_insert_normal(void);
bool test_digraph_vertex_insert_null_params(void);
bool test_digraph_vertex_insert_empty(void);

bool test_digraph_vertex_remove_normal(void);
bool test_digraph_vertex_remove_null_params(void);
bool test_digraph_vertex_remove_out_of_bounds(void);
bool test_digraph_vertex_remove_empty(void);

bool test_digraph_connect_normal(void);
bool test_digraph_connect_null_params(void);
bool test_digraph_connect_out_of_bounds(void);
bool test_digraph_connect_loop_edge(void);
bool test_digraph_connect_multiple_edge(void);

bool test_digraph_disconnect_normal(void);
bool test_digraph_disconnect_null_params(void);
bool test_digraph_disconnect_out_of_bounds(void);
bool test_digraph_disconnect_empty(void);

bool test_digraph_in_neighbours_normal(void);
bool test_digraph_in_neighbours_null_params(void);
bool test_digraph_in_neighbours_out_of_bounds(void);

bool test_digraph_out_neighbours_normal(void);
bool test_digraph_out_neighbours_null_params(void);
bool test_digraph_out_neighbours_out_of_bounds(void);

bool test_digraph_adjacent_normal(void);
bool test_digraph_adjacent_null_params(void);
bool test_digraph_adjacent_out_of_bounds(void);
bool test_digraph_adjacent_nonadjacent(void);

bool test_digraph_adjacent_via_normal(void);
bool test_digraph_adjacent_via_null_params(void);
bool test_digraph_adjacent_via_out_of_bounds(void);
bool test_digraph_adjacent_via_nonadjacent(void);
bool test_digraph_adjacent_via_loop_edge(void);
bool test_digraph_adjacent_via_multiple_edge(void);

bool test_digraph_incident_normal(void);
bool test_digraph_incident_null_params(void);
bool test_digraph_incident_out_of_bounds(void);
bool test_digraph_incident_nonincident(void);
bool test_digraph_incident_loop_edge(void);

bool test_digraph_endpoints_normal(void);
bool test_digraph_endpoints_null_params(void);
bool test_digraph_endpoints_out_of_bounds(void);
bool test_digraph_endpoints_loop_edge(void);

bool test_digraph_in_degree_normal(void);
bool test_digraph_in_degree_null_params(void);
bool test_digraph_in_degree_out_of_bounds(void);
bool test_digraph_in_degree_zero(void);
bool test_digraph_in_degree_loop_edge(void);
bool test_digraph_in_degree_multiple_edge(void);

bool test_digraph_out_degree_normal(void);
bool test_digraph_out_degree_null_params(void);
bool test_digraph_out_degree_out_of_bounds(void);
bool test_digraph_out_degree_zero(void);
bool test_digraph_out_degree_loop_edge(void);
bool test_digraph_out_degree_multiple_edge(void);

bool test_digraph_incident_edges_normal(void);
bool test_digraph_incident_edges_null_params(void);
bool test_digraph_incident_edges_out_of_bounds(void);
bool test_digraph_incident_edges_zero(void);
bool test_digraph_incident_edges_loop_edge(void);
bool test_digraph_incident_edges_multiple_edge(void);

bool test_digraph_find_vertices_normal(void);
bool test_digraph_find_vertices_null_params(void);
bool test_digraph_find_vertices_not_found(void);

bool test_digraph_find_edges_normal(void);
bool test_digraph_find_edges_null_params(void);
bool test_digraph_find_edges_not_found(void);

