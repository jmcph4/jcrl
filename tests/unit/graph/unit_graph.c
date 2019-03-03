#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "constants.h"
#include "macros.h"
#include "set.h"
#include "graph.h"

#include "unit_graph.h"

/* Initialisation */
bool test_graph_init_normal(void)
{
    bool pass = false;

    Graph graph;
    unsigned int res = graph_init(&graph);

    graph_free(NULL, &graph);

    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_init_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_free(NULL, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_free_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    unsigned int res = graph_free(NULL, &d);

    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_free_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_free(NULL, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

/* Access */
bool test_graph_vertex_get_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    unsigned int a = 12; /* arbitrary data for insertion */
    unsigned int vertex = 0;
    graph_vertex_insert(G_INT(a), &vertex, &d);

    unsigned int val = 0;
    unsigned int res = graph_vertex_get((void**)&val, vertex, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && val == a)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_vertex_get_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_vertex_get(NULL, 0, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_vertex_get_out_of_bounds(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* insert vertex into graph */
    unsigned int a = 12; /* arbitrary data for insertion */
    unsigned int vertex = 0;
    graph_vertex_insert(G_INT(a), &vertex, &d);

    void* val = NULL;
    unsigned int res = graph_vertex_get(&val, vertex + 1, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OUT_OF_BOUNDS)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_vertex_set_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;

    /* add vertex */
    unsigned int vertex = 0;
    graph_vertex_insert(G_INT(a), &vertex, &d);

    /* set vertex label to b */
    unsigned int res = graph_vertex_set(G_INT(b), vertex, &d);

    /* see if our changes got saved */
    unsigned int val = 0;
    graph_vertex_get((void**)&val, vertex, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && val == b)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_vertex_set_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_vertex_set(NULL, 0, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_vertex_set_out_of_bounds(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;

    /* insert vertex into graph */
    unsigned int vertex = 0;
    graph_vertex_insert(G_INT(a), &vertex, &d);

    unsigned int res = graph_vertex_set(G_INT(b), vertex + 1, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OUT_OF_BOUNDS)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_edge_get_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int vertex_a = 0;
    unsigned int vertex_b = 0;
    unsigned int edge = 0;

    /* insert vertices */
    graph_vertex_insert(G_INT(a), &vertex_a, &d);
    graph_vertex_insert(G_INT(b), &vertex_a, &d);

    /* insert edge */
    graph_connect(G_INT(c), vertex_a, vertex_b, &edge, &d);

    /* get data out from edge */
    unsigned int val = 0;
    unsigned int res = graph_edge_get((void**)&val, edge, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && val == c)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_edge_get_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_edge_get(NULL, 0, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_edge_get_out_of_bounds(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    
    unsigned int vertex_a = 0;
    unsigned int vertex_b = 0;
    unsigned int edge = 0;

    /* insert vertices into graph */
    graph_vertex_insert(G_INT(a), &vertex_a, &d);
    graph_vertex_insert(G_INT(b), &vertex_b, &d);

    /* add a single edge */
    graph_connect(G_INT(c), vertex_a, vertex_b, &edge, &d);

    /* perform out of bounds access */
    unsigned int val = 0;
    unsigned int res = graph_edge_get((void**)&val, edge + 1, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OUT_OF_BOUNDS)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_edge_set_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    
    unsigned int vertex_a = 0;
    unsigned int vertex_b = 0;
    unsigned int edge = 0;

    /* insert vertices into graph */
    graph_vertex_insert(G_INT(a), &vertex_a, &d);
    graph_vertex_insert(G_INT(b), &vertex_b, &d);

    /* add a single edge */
    graph_connect(G_INT(c), vertex_a, vertex_b, &edge, &d);

    /* change edge label */
    graph_edge_set(G_INT(b), edge, &d);

    /* see if our changes took effect */
    unsigned int val = 0;
    unsigned int res = graph_edge_get((void**)&val, edge, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && val == b)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_edge_set_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_edge_get(NULL, 0, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_edge_set_out_of_bounds(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int vertex_a = 0;
    unsigned int vertex_b = 0;
    unsigned int edge = 0;

    /* insert vertices */
    graph_vertex_insert(G_INT(a), &vertex_a, &d);
    graph_vertex_insert(G_INT(b), &vertex_b, &d);

    /* insert a single edge */
    graph_connect(G_INT(c), vertex_a, vertex_b, &edge, &d);

    unsigned int res = graph_edge_set(G_INT(b), edge + 1, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OUT_OF_BOUNDS)
    {
        pass = true;
    }

    return pass;
}

/* Size */
bool test_graph_order_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int vertex_a = 0;
    unsigned int vertex_b = 0;
    unsigned int vertex_c = 0;
    unsigned int edge = 0;

    /* insert vertices */
    graph_vertex_insert(G_INT(a), &vertex_a, &d);
    graph_vertex_insert(G_INT(b), &vertex_b, &d);
    graph_vertex_insert(G_INT(c), &vertex_c, &d);
    
    /* insert some edges */
    graph_connect(G_INT(b), vertex_a, vertex_b, &edge, &d);

    /* query graph as to size */
    unsigned int order = 0;
    unsigned int res = graph_order(&order, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && order == 3)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_order_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_order(NULL, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_order_empty(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    unsigned int order = 0;
    unsigned int res = graph_order(&order, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && order == 0)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_size_normal(void)
{
    bool pass = false;
 
    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int vertex_a = 0;
    unsigned int vertex_b = 0;
    unsigned int vertex_c = 0;
    unsigned int edge = 0;

    /* insert vertices */
    graph_vertex_insert(G_INT(a), &vertex_a, &d);
    graph_vertex_insert(G_INT(b), &vertex_b, &d);
    graph_vertex_insert(G_INT(c), &vertex_c, &d);
    
    /* insert some edges */
    graph_connect(G_INT(b), vertex_a, vertex_b, &edge, &d);

    /* query graph as to size */
    unsigned int size = 0;
    unsigned int res = graph_size(&size, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && size == 1)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_size_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_size(NULL, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_size_empty(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    unsigned int size = 0;
    unsigned int res = graph_size(&size, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && size == 0)
    {
        pass = true;
    }

    return pass;
}

/* Equality */
bool test_graph_equal_normal(void)
{
    bool pass = false;

    Graph graph_a;
    graph_init(&graph_a);

    Graph graph_b;
    graph_init(&graph_b);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    unsigned int d = 3;

    /* vertex and edge numbers */
    unsigned int v = 0;
    unsigned int e = 0;

    /* perform operations on graph_a */
    graph_vertex_insert(G_INT(a), &v, &graph_a);
    graph_vertex_insert(G_INT(b), &v, &graph_a);
    graph_connect(G_INT(c), 0, 1, &e, &graph_a);

    /* perform operations on graph_b */
    graph_vertex_insert(G_INT(a), &v, &graph_b);
    graph_vertex_insert(G_INT(b), &v, &graph_b);
    graph_connect(G_INT(c), 0, 1, &e, &graph_b);
    graph_connect(G_INT(d), 0, 1, &e, &graph_b);
    graph_disconnect(2, &graph_b);

    bool equal = false;
    unsigned int res = graph_equal(&equal, &graph_a, &graph_b);

    graph_free(NULL, &graph_a);
    graph_free(NULL, &graph_b);

    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_equal_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_equal(NULL, NULL, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_equal_empty_graphs(void)
{
    bool pass = false;
 
    Graph graph_a;
    graph_init(&graph_a);

    Graph graph_b;
    graph_init(&graph_b);

    bool equal = false;
    unsigned int res = graph_equal(&equal, &graph_a, &graph_b);

    graph_free(NULL, &graph_a);
    graph_free(NULL, &graph_b);

    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_equal_not_equal(void)
{
    bool pass = false;
 
    Graph graph_a;
    graph_init(&graph_a);

    Graph graph_b;
    graph_init(&graph_b);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    unsigned int d = 3;

    /* vertex and edge numbers */
    unsigned int v = 0;
    unsigned int e = 0;

    /* perform operations on graph_a */
    graph_vertex_insert(G_INT(a), &v, &graph_a);
    graph_vertex_insert(G_INT(b), &v, &graph_a);
    graph_connect(G_INT(c), 0, 1, &e, &graph_a);

    /* perform operations on graph_b */
    graph_vertex_insert(G_INT(a), &v, &graph_b);
    graph_vertex_insert(G_INT(b), &v, &graph_b);
    graph_connect(G_INT(c), 0, 1, &e, &graph_b);
    graph_connect(G_INT(d), 0, 1, &e, &graph_b);

    bool equal = false;
    unsigned int res = graph_equal(&equal, &graph_a, &graph_b);

    graph_free(NULL, &graph_a);
    graph_free(NULL, &graph_b);

    if(res == JCRL_ERR_OK && !equal)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_equal_reordered(void)
{
    bool pass = false;
 
    Graph graph_a;
    graph_init(&graph_a);

    Graph graph_b;
    graph_init(&graph_b);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    unsigned int d = 3;

    /* vertex and edge numbers */
    unsigned int v = 0;
    unsigned int e = 0;

    /* perform operations on graph_a */
    graph_vertex_insert(G_INT(b), &v, &graph_a);
    graph_vertex_insert(G_INT(a), &v, &graph_a);
    graph_connect(G_INT(d), 0, 1, &e, &graph_a);

    /* perform operations on graph_b */
    graph_vertex_insert(G_INT(a), &v, &graph_b);
    graph_vertex_insert(G_INT(b), &v, &graph_b);
    graph_connect(G_INT(d), 0, 1, &e, &graph_b);
    graph_connect(G_INT(c), 0, 1, &e, &graph_b);
    graph_disconnect(2, &graph_b);

    bool equal = false;
    unsigned int res = graph_equal(&equal, &graph_a, &graph_b);

    graph_free(NULL, &graph_a);
    graph_free(NULL, &graph_b);

    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }

    return pass;
}

/* Membership */
bool test_graph_vertex_in_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);    

    /* arbitrary data for insertion */
    unsigned int a = 12;

    unsigned int v = 0;

    graph_vertex_insert(G_INT(a), &v, &d);

    bool in = false;
    unsigned int res = graph_vertex_in(&in, G_INT(a), &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && in)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_vertex_in_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_vertex_in(NULL, NULL, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_vertex_in_not_found(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);    

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;

    unsigned int v = 0;

    graph_vertex_insert(G_INT(a), &v, &d);

    bool in = false;
    unsigned int res = graph_vertex_in(&in, G_INT(b), &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && !in)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_edge_in_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);    

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;

    unsigned int v = 0;
    unsigned int e = 0;

    graph_vertex_insert(G_INT(a), &v, &d);
    graph_vertex_insert(G_INT(b), &v, &d);

    graph_connect(G_INT(a), 0, 1, &e, &d);

    bool in = false;
    unsigned int res = graph_edge_in(&in, G_INT(a), &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && in)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_edge_in_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_edge_in(NULL, NULL, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_edge_in_not_found(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);    

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;

    unsigned int v = 0;
    unsigned int e = 0;

    graph_vertex_insert(G_INT(a), &v, &d);
    graph_vertex_insert(G_INT(b), &v, &d);

    graph_connect(G_INT(a), 0, 1, &e, &d);

    bool in = false;
    unsigned int res = graph_edge_in(&in, G_INT(b), &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && !in)
    {
        pass = true;
    }

    return pass;
}

/* Operations */
bool test_graph_vertex_insert_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int v = 0;
    unsigned int val = 0;

    graph_vertex_insert(G_INT(a), &v, &d);
    graph_vertex_insert(G_INT(b), &v, &d);

    unsigned int res = graph_vertex_insert(G_INT(c), &v, &d);

    graph_vertex_get((void**)&val, v, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && val == c)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_vertex_insert_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_vertex_insert(NULL, NULL, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_vertex_insert_empty(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;

    unsigned int v = 0;
    unsigned int val = 0;

    unsigned int res = graph_vertex_insert(G_INT(a), &v, &d);

    graph_vertex_get((void**)&val, v, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && val == a)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_vertex_remove_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;

    unsigned int v = 0; /* store vertex number */

    /* insert some vertices */
    graph_vertex_insert(G_INT(a), &v, &d);
    graph_vertex_insert(G_INT(b), &v, &d);

    unsigned int res = graph_vertex_remove(v, &d);

    /* get number of vertices in graph */
    unsigned int num_vertices = 0;
    graph_order(&num_vertices, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && num_vertices == 1)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_vertex_remove_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_vertex_remove(0, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_vertex_remove_out_of_bounds(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;

    unsigned int v = 0; /* store vertex number */

    /* insert some vertices */
    graph_vertex_insert(G_INT(a), &v, &d);
    graph_vertex_insert(G_INT(b), &v, &d);

    /* attempt to remove nonexistant vertex */
    unsigned int res = graph_vertex_remove(v + 1, &d);

    /* get number of vertices in graph */
    unsigned int num_vertices = 0;
    graph_order(&num_vertices, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OUT_OF_BOUNDS && num_vertices == 2)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_vertex_remove_empty(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    unsigned int res = graph_vertex_remove(0, &d);

    /* get number of vertices in graph */
    unsigned int num_vertices = 0;
    graph_order(&num_vertices, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OUT_OF_BOUNDS && num_vertices == 0)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_connect_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    /* store vertices */
    unsigned int v_1 = 0;
    unsigned int v_2 = 0;
    unsigned int e = 0;

    /* insert some vertices */
    graph_vertex_insert(G_INT(a), &v_1, &d);
    graph_vertex_insert(G_INT(b), &v_2, &d);

    unsigned int res = graph_connect(G_INT(c), v_1, v_2, &e, &d);

    /* get edge label */
    unsigned int val = 0;
    graph_edge_get((void**)&val, e, &d);

    /* get number of edges in graph */
    unsigned int num_edges = 0;
    graph_size(&num_edges, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && val == c && num_edges == 1)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_connect_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_connect(0, 0, 0, NULL, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_connect_out_of_bounds(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    /* store vertices */
    unsigned int v_1 = 0;
    unsigned int v_2 = 0;
    unsigned int e = 0;

    /* insert some vertices */
    graph_vertex_insert(G_INT(a), &v_1, &d);
    graph_vertex_insert(G_INT(b), &v_2, &d);

    unsigned int res = graph_connect(G_INT(c), v_1, v_2 + 1, &e, &d);

    /* get number of edges in graph */
    unsigned int num_edges = 0;
    graph_size(&num_edges, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OUT_OF_BOUNDS && num_edges == 0)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_connect_loop_edge(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data to insert */
    unsigned int a = 12;
    unsigned int b = 33;

    unsigned int v = 0;
    unsigned int e = 0;

    graph_vertex_insert(G_INT(a), &v, &d);

    unsigned int res = graph_connect(G_INT(b), v, v, &e, &d);

    /* get edge label value */
    unsigned int val = 0;
    graph_edge_get((void**)&val, e, &d);

    /* get number of edges in graph */
    unsigned int num_edges = 0;
    graph_size(&num_edges, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && val == b && num_edges == 1)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_connect_multiple_edge(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int v1 = 0;
    unsigned int v2 = 0;
    unsigned int e_1 = 0;
    unsigned int e_2 = 0;

    graph_vertex_insert(G_INT(a), &v1, &d);

    graph_connect(G_INT(b), v1, v2, &e_1, &d);
    unsigned int res = graph_connect(G_INT(c), v1, v2, &e_2, &d);

    /* get edge label values */
    unsigned long val_1 = 0;
    unsigned long val_2 = 0;
    graph_edge_get((void**)&val_1, e_1, &d);
    graph_edge_get((void**)&val_2, e_2, &d);

    /* get number of edges in graph */
    unsigned int num_edges = 0;
    graph_size(&num_edges, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && val_1 == b && val_2 == c && num_edges == 2)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_disconnect_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    /* store vertices */
    unsigned int v_1 = 0;
    unsigned int v_2 = 0;
    unsigned int e = 0;

    /* insert some vertices */
    graph_vertex_insert(G_INT(a), &v_1, &d);
    graph_vertex_insert(G_INT(b), &v_2, &d);

    graph_connect(G_INT(c), v_1, v_2, &e, &d);

    unsigned int res = graph_disconnect(e, &d);

    /* get number of edges in graph */
    unsigned int num_edges = 0;
    graph_size(&num_edges, &d);

    graph_free(NULL, &d);
    
    if(res == JCRL_ERR_OK && num_edges == 0)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_disconnect_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_disconnect(0, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_disconnect_out_of_bounds(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    /* store vertices */
    unsigned int v_1 = 0;
    unsigned int v_2 = 0;
    unsigned int e = 0;

    /* insert some vertices */
    graph_vertex_insert(G_INT(a), &v_1, &d);
    graph_vertex_insert(G_INT(b), &v_2, &d);

    graph_connect(G_INT(c), v_1, v_2, &e, &d);

    unsigned int res = graph_disconnect(e + 1, &d);

    /* get number of edges in graph */
    unsigned int num_edges = 0;
    graph_size(&num_edges, &d);

    graph_free(NULL, &d);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS && num_edges == 1)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_disconnect_empty(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    unsigned int res = graph_disconnect(0, &d);

    /* get number of edges in graph */
    unsigned int num_edges = 0;
    graph_size(&num_edges, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OUT_OF_BOUNDS && num_edges == 0)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_neighbours_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 33;
    unsigned int b = 12;
    unsigned int c = 1;

    unsigned int v1 = 0;
    unsigned int v2 = 0;
    unsigned int v3 = 0;
    unsigned int v4 = 0;
    unsigned int e = 0;

    /* insert vertices */
    graph_vertex_insert(G_INT(a), &v1, &d);
    graph_vertex_insert(G_INT(b), &v2, &d);
    graph_vertex_insert(G_INT(c), &v3, &d);
    graph_vertex_insert(G_INT(a), &v4, &d);

    /* connect vertices */
    graph_connect(G_INT(a), v2, v1, &e, &d);
    graph_connect(G_INT(a), v3, v1, &e, &d);
    graph_connect(G_INT(a), v4, v1, &e, &d);

    Set actual_neighbours;
    set_init(&actual_neighbours);

    unsigned int res = graph_neighbours(&actual_neighbours, v1, &d);

    Set expected_neighbours;
    set_init(&expected_neighbours);
    set_add(G_INT(v2), &expected_neighbours);
    set_add(G_INT(v3), &expected_neighbours);
    set_add(G_INT(v4), &expected_neighbours); 

    bool equal = false;
    set_equal(&equal, &actual_neighbours, &expected_neighbours);

    set_free(NULL, &actual_neighbours);
    set_free(NULL, &expected_neighbours);
    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_neighbours_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_neighbours(NULL, 0, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_neighbours_out_of_bounds(void)
{
    bool pass = false;
    
    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 33;
    unsigned int b = 12;
    unsigned int c = 1;

    unsigned int v1 = 0;
    unsigned int v2 = 0;
    unsigned int v3 = 0;
    unsigned int v4 = 0;
    unsigned int e = 0;

    /* insert vertices */
    graph_vertex_insert(G_INT(a), &v1, &d);
    graph_vertex_insert(G_INT(b), &v2, &d);
    graph_vertex_insert(G_INT(c), &v3, &d);
    graph_vertex_insert(G_INT(a), &v4, &d);

    /* connect vertices */
    graph_connect(G_INT(a), v1, v2, &e, &d);
    graph_connect(G_INT(a), v1, v3, &e, &d);
    graph_connect(G_INT(a), v1, v4, &e, &d);

    Set actual_neighbours;
    set_init(&actual_neighbours);

    unsigned int res = graph_neighbours(&actual_neighbours, v1 + 10, &d);

    Set expected_neighbours;
    set_init(&expected_neighbours);

    bool equal = false;
    set_equal(&equal, &actual_neighbours, &expected_neighbours);

    set_free(NULL, &actual_neighbours);
    set_free(NULL, &expected_neighbours);
    graph_free(NULL, &d);

    if(res == JCRL_ERR_OUT_OF_BOUNDS && equal)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_adjacent_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);
    
    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int c = 1;

    unsigned int v_1 = 0;
    unsigned int v_2 = 0;
    unsigned int e = 0;

    /* insert vertices and edges */
    graph_vertex_insert(G_INT(a), &v_1, &d);
    graph_vertex_insert(G_INT(a), &v_2, &d);
    graph_connect(G_INT(c), v_1, v_2, &e, &d);

    /* test for adjacency */
    bool adjacent = false;
    unsigned int res = graph_adjacent(&adjacent, v_1, v_2, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && adjacent)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_adjacent_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_adjacent(NULL, 0, 0, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_adjacent_out_of_bounds(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);
    
    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int c = 1;

    unsigned int v_1 = 0;
    unsigned int v_2 = 0;
    unsigned int e = 0;

    /* insert vertices and edges */
    graph_vertex_insert(G_INT(a), &v_1, &d);
    graph_vertex_insert(G_INT(a), &v_2, &d);
    graph_connect(G_INT(c), v_1, v_2, &e, &d);

    /* test for adjacency */
    bool adjacent = false;
    unsigned int res = graph_adjacent(&adjacent, v_1, v_2 + 1, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OUT_OF_BOUNDS)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_adjacent_nonadjacent(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);
    
    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int v_1 = 0;
    unsigned int v_2 = 0;
    unsigned int v_3 = 0;
    unsigned int e = 0;

    /* insert vertices and edges */
    graph_vertex_insert(G_INT(a), &v_1, &d);
    graph_vertex_insert(G_INT(b), &v_2, &d);
    graph_vertex_insert(G_INT(c), &v_3, &d);
    graph_connect(G_INT(c), v_1, v_2, &e, &d);

    /* test for adjacency */
    bool adjacent = false;
    unsigned int res = graph_adjacent(&adjacent, v_1, v_3, &d);

    graph_free(NULL, &d);
    
    if(res == JCRL_ERR_OK && !adjacent)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_adjacent_via_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    /* vertex and edge numbers */
    unsigned int v_1 = 0;
    unsigned int v_2 = 0;
    unsigned int e_1 = 0;
    unsigned int e_2 = 0;
    unsigned int e_3 = 0;

    graph_vertex_insert(G_INT(a), &v_1, &d);
    graph_vertex_insert(G_INT(b), &v_2, &d);

    /* connect vertices */
    graph_connect(G_INT(c), v_1, v_2, &e_1, &d);
    graph_connect(G_INT(b), v_1, v_2, &e_2, &d);
    graph_connect(G_INT(a), v_1, v_2, &e_3, &d);

    /* populate expected answer set */
    Set expected;
    set_init(&expected);
    set_add(G_INT(e_1), &expected);
    set_add(G_INT(e_2), &expected);
    set_add(G_INT(e_3), &expected);

    Set via;
    set_init(&via);

    unsigned int res = graph_adjacent_via(&via, v_1, v_2, &d);

    bool equal = false;
    set_equal(&equal, &via, &expected);

    set_free(NULL, &expected);
    set_free(NULL, &via);
    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_adjacent_via_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_adjacent_via(NULL, 0, 0, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_adjacent_via_out_of_bounds(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    /* vertex and edge numbers */
    unsigned int v_1 = 0;
    unsigned int v_2 = 0;
    unsigned int e_1 = 0;
    unsigned int e_2 = 0;
    unsigned int e_3 = 0;

    graph_vertex_insert(G_INT(a), &v_1, &d);
    graph_vertex_insert(G_INT(b), &v_2, &d);

    /* connect vertices */
    graph_connect(G_INT(c), v_1, v_2, &e_1, &d);
    graph_connect(G_INT(b), v_1, v_2, &e_2, &d);
    graph_connect(G_INT(a), v_1, v_2, &e_3, &d);
    
    Set via;
    set_init(&via);

    unsigned int res = graph_adjacent_via(&via, v_1, v_2 + 2, &d);

    set_free(NULL, &via);
    graph_free(NULL, &d);

    if(res == JCRL_ERR_OUT_OF_BOUNDS)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_adjacent_via_nonadjacent(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int v = 0;
    unsigned int e = 0;

    graph_vertex_insert(G_INT(a), &v, &d);
    graph_vertex_insert(G_INT(b), &v, &d);
    graph_vertex_insert(G_INT(c), &v, &d);

    graph_connect(G_INT(c), v, v - 1, &e, &d);

    Set via;
    set_init(&via);
    unsigned int res = graph_adjacent_via(&via, v - 2, v, &d);

    set_free(NULL, &via);
    graph_free(NULL, &d);

    if(res == JCRL_ERR_IMPOSSIBLE)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_adjacent_via_loop_edge(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    
    unsigned int v = 0;
    unsigned int e = 0;

    graph_vertex_insert(G_INT(a), &v, &d);
    
    graph_connect(G_INT(b), v, v, &e, &d);
    graph_connect(G_INT(c), v, v, &e, &d);

    Set expected;
    set_init(&expected);

    set_add(G_INT(0), &expected);
    set_add(G_INT(2), &expected);

    Set via;
    set_init(&via);

    unsigned int res = graph_adjacent_via(&via, v, v, &d);

    bool equal = false;
    set_equal(&equal, &via, &expected);

    set_free(NULL, &via);
    set_free(NULL, &expected);
    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_adjacent_via_multiple_edge(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int v = 0;
    unsigned int e = 0;

    graph_vertex_insert(G_INT(a), &v, &d);
    graph_vertex_insert(G_INT(a), &v, &d);
    
    graph_connect(G_INT(b), v - 1, v, &e, &d);
    graph_connect(G_INT(c), v - 1, v, &e, &d);

    Set expected;
    set_init(&expected);

    set_add(G_INT(0), &expected);
    set_add(G_INT(1), &expected);

    Set via;
    set_init(&via);

    unsigned int res = graph_adjacent_via(&via, v - 1, v, &d);

    bool equal = false;
    set_equal(&equal, &via, &expected);

    set_free(NULL, &via);
    set_free(NULL, &expected);
    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_incident_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int vertex_a = 0;
    unsigned int vertex_b = 0;
    unsigned int edge = 0;

    graph_vertex_insert(G_INT(a), &vertex_a, &d);
    graph_vertex_insert(G_INT(b), &vertex_b, &d);
    graph_connect(G_INT(c), vertex_a, vertex_b, &edge, &d);

    bool incident = false;
    unsigned int res = graph_incident(&incident, vertex_a, edge, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && incident)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_incident_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_incident(NULL, 0, 0, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_incident_out_of_bounds(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int vertex_a = 0;
    unsigned int vertex_b = 0;
    unsigned int edge = 0;

    graph_vertex_insert(G_INT(a), &vertex_a, &d);
    graph_vertex_insert(G_INT(b), &vertex_b, &d);
    graph_connect(G_INT(c), vertex_a, vertex_b, &edge, &d);

    bool incident = false;
    unsigned int res = graph_incident(&incident, vertex_a + 5, edge, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OUT_OF_BOUNDS &&!incident)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_incident_nonincident(void)
{
    bool pass = false;
 
    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;

    unsigned int vertex_a = 0;
    unsigned int vertex_b = 0;
    unsigned int edge = 0;

    graph_vertex_insert(G_INT(a), &vertex_a, &d);
    graph_vertex_insert(G_INT(b), &vertex_b, &d);
    graph_connect(G_INT(a), vertex_a, vertex_a, &edge, &d); /* loop */

    bool incident = false;
    unsigned int res = graph_incident(&incident, edge, vertex_b, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && !incident)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_incident_loop_edge(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int vertex_a = 0;
    unsigned int vertex_b = 0;
    unsigned int edge = 0;

    graph_vertex_insert(G_INT(a), &vertex_a, &d);
    graph_vertex_insert(G_INT(b), &vertex_b, &d);
    graph_connect(G_INT(c), vertex_a, vertex_a, &edge, &d);

    bool incident = false;
    unsigned int res = graph_incident(&incident, vertex_a, edge, &d);

    graph_free(NULL, &d);
    
    if(res == JCRL_ERR_OK && incident)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_endpoints_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int v1 = 0;
    unsigned int v2 = 0;
    unsigned int e = 0;

    graph_vertex_insert(G_INT(a), &v1, &d);
    graph_vertex_insert(G_INT(b), &v2, &d);
    graph_connect(G_INT(c), v1, v2, &e, &d);

    unsigned int vertex_a = 0;
    unsigned int vertex_b = 0;
    
    unsigned int res = graph_endpoints(&vertex_a, &vertex_b, e, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && vertex_a == v1 && vertex_b == v2)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_endpoints_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_endpoints(NULL, NULL, 0, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_endpoints_out_of_bounds(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int v1 = 0;
    unsigned int v2 = 0;
    unsigned int e = 0;

    graph_vertex_insert(G_INT(a), &v1, &d);
    graph_vertex_insert(G_INT(b), &v2, &d);
    graph_connect(G_INT(c), v1, v2, &e, &d);

    unsigned int vertex_a = 0;
    unsigned int vertex_b = 0;
    
    unsigned int res = graph_endpoints(&vertex_a, &vertex_b, e + 1, &d);

    graph_free(NULL, &d);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS && vertex_a == 0 && vertex_b == 0)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_endpoints_loop_edge(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int c = 1;

    unsigned int v1 = 0;
    unsigned int e = 0;

    graph_vertex_insert(G_INT(a), &v1, &d);
    graph_connect(G_INT(c), v1, v1, &e, &d);

    unsigned int vertex_a = 0;
    unsigned int vertex_b = 0;
    
    unsigned int res = graph_endpoints(&vertex_a, &vertex_b, e, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && vertex_a == v1 && vertex_b == v1)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_degree_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int v1 = 0;
    unsigned int v2 = 0;
    unsigned int v3 = 0;
    unsigned int v4 = 0;
    unsigned int v5 = 0;
    unsigned int e = 0;

    /* insert vertices */
    graph_vertex_insert(G_INT(a), &v1, &d);
    graph_vertex_insert(G_INT(b), &v2, &d);
    graph_vertex_insert(G_INT(b), &v3, &d);
    graph_vertex_insert(G_INT(b), &v4, &d);
    graph_vertex_insert(G_INT(b), &v5, &d);
    
    /* connect vertices */
    graph_connect(G_INT(c), v2, v1, &e, &d);
    graph_connect(G_INT(c), v3, v1, &e, &d);
    graph_connect(G_INT(c), v4, v1, &e, &d);
    graph_connect(G_INT(c), v5, v1, &e, &d);

    unsigned int degree = 0;
    unsigned int res = graph_degree(&degree, v1, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && degree == 4)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_degree_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_degree(NULL, 0, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_degree_out_of_bounds(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int v1 = 0;
    unsigned int v2 = 0;
    unsigned int v3 = 0;
    unsigned int v4 = 0;
    unsigned int v5 = 0;
    unsigned int e = 0;

    /* insert vertices */
    graph_vertex_insert(G_INT(a), &v1, &d);
    graph_vertex_insert(G_INT(b), &v2, &d);
    graph_vertex_insert(G_INT(b), &v3, &d);
    graph_vertex_insert(G_INT(b), &v4, &d);
    graph_vertex_insert(G_INT(b), &v5, &d);
    
    /* connect vertices */
    graph_connect(G_INT(c), v2, v1, &e, &d);
    graph_connect(G_INT(c), v3, v1, &e, &d);
    graph_connect(G_INT(c), v4, v1, &e, &d);
    graph_connect(G_INT(c), v5, v1, &e, &d);

    unsigned int degree = 0;
    unsigned int res = graph_degree(&degree, v1 + 10, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OUT_OF_BOUNDS && degree == 0)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_degree_zero(void)
{
    bool pass = false;
    
    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int v1 = 0;
    unsigned int v2 = 0;
    unsigned int v3 = 0;
    unsigned int v4 = 0;
    unsigned int v5 = 0;
    unsigned int e = 0;

    /* insert vertices */
    graph_vertex_insert(G_INT(a), &v1, &d);
    graph_vertex_insert(G_INT(b), &v2, &d);
    graph_vertex_insert(G_INT(b), &v3, &d);
    graph_vertex_insert(G_INT(b), &v4, &d);
    graph_vertex_insert(G_INT(b), &v5, &d);
    
    /* connect vertices */
    graph_connect(G_INT(c), v3, v1, &e, &d);
    graph_connect(G_INT(c), v4, v1, &e, &d);
    graph_connect(G_INT(c), v5, v1, &e, &d);

    unsigned int degree = 0;
    unsigned int res = graph_degree(&degree, v2, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && degree == 0)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_degree_loop_edge(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int c = 1;

    unsigned int v1 = 0;
    unsigned int e = 0;

    /* insert vertices */
    graph_vertex_insert(G_INT(a), &v1, &d);
    
    /* connect vertices */
    graph_connect(G_INT(c), v1, v1, &e, &d);
    graph_connect(G_INT(c), v1, v1, &e, &d);
    graph_connect(G_INT(c), v1, v1, &e, &d);
    graph_connect(G_INT(c), v1, v1, &e, &d);

    unsigned int degree = 0;
    unsigned int res = graph_degree(&degree, v1, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && degree == 4)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_degree_multiple_edge(void)
{
    bool pass = false;
    
    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int v1 = 0;
    unsigned int v2 = 0;
    unsigned int e = 0;

    /* insert vertices */
    graph_vertex_insert(G_INT(a), &v1, &d);
    graph_vertex_insert(G_INT(b), &v2, &d);
    
    /* connect vertices */
    graph_connect(G_INT(c), v2, v1, &e, &d);
    graph_connect(G_INT(c), v2, v1, &e, &d);
    graph_connect(G_INT(c), v2, v1, &e, &d);
    graph_connect(G_INT(c), v2, v1, &e, &d);

    unsigned int degree = 0;
    unsigned int res = graph_degree(&degree, v1, &d);

    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && degree == 4)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_incident_edges_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int v1 = 0;
    unsigned int v2 = 0;
    unsigned int e1 = 0;
    unsigned int e2 = 0;
    unsigned int e3 = 0;

    graph_vertex_insert(G_INT(a), &v1, &d);
    graph_vertex_insert(G_INT(b), &v2, &d);

    graph_connect(G_INT(a), v1, v2, &e1, &d);
    graph_connect(G_INT(b), v1, v2, &e2, &d);
    graph_connect(G_INT(c), v2, v1, &e3, &d);

    Set actual_edges;
    set_init(&actual_edges);

    unsigned int res = graph_incident_edges(&actual_edges, v1, &d);

    Set expected_edges;
    set_init(&expected_edges);
    set_add(G_INT(e1), &expected_edges);
    set_add(G_INT(e2), &expected_edges);
    set_add(G_INT(e3), &expected_edges);

    bool equal = false;
    set_equal(&equal, &actual_edges, &expected_edges);

    set_free(NULL, &expected_edges);
    set_free(NULL, &actual_edges);
    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_incident_edges_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_incident_edges(NULL, 0, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_incident_edges_out_of_bounds(void)
{
    bool pass = false;
    
    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int v1 = 0;
    unsigned int v2 = 0;
    unsigned int e1 = 0;
    unsigned int e2 = 0;
    unsigned int e3 = 0;

    graph_vertex_insert(G_INT(a), &v1, &d);
    graph_vertex_insert(G_INT(b), &v2, &d);

    graph_connect(G_INT(a), v1, v2, &e1, &d);
    graph_connect(G_INT(b), v1, v2, &e2, &d);
    graph_connect(G_INT(c), v2, v1, &e3, &d);

    Set actual_edges;
    set_init(&actual_edges);

    unsigned int res = graph_incident_edges(&actual_edges, v1 + 10, &d);

    Set expected_edges;
    set_init(&expected_edges);

    bool equal = false;
    set_equal(&equal, &actual_edges, &expected_edges);

    set_free(NULL, &expected_edges);
    set_free(NULL, &actual_edges);
    graph_free(NULL, &d);

    if(res == JCRL_ERR_OUT_OF_BOUNDS && equal)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_incident_edges_zero(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;

    unsigned int v1 = 0;

    graph_vertex_insert(G_INT(a), &v1, &d);

    Set actual_edges;
    set_init(&actual_edges);

    unsigned int res = graph_incident_edges(&actual_edges, v1, &d);

    Set expected_edges;
    set_init(&expected_edges);

    bool equal = false;
    res = set_equal(&equal, &actual_edges, &expected_edges);

    set_free(NULL, &expected_edges);
    set_free(NULL, &actual_edges);
    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_incident_edges_loop_edge(void)
{
    bool pass = false;
    
    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int v1 = 0;
    unsigned int e1 = 0;
    unsigned int e2 = 0;
    unsigned int e3 = 0;

    graph_vertex_insert(G_INT(a), &v1, &d);

    graph_connect(G_INT(a), v1, v1, &e1, &d);
    graph_connect(G_INT(b), v1, v1, &e2, &d);
    graph_connect(G_INT(c), v1, v1, &e3, &d);

    Set actual_edges;
    set_init(&actual_edges);

    unsigned int res = graph_incident_edges(&actual_edges, v1, &d);

    Set expected_edges;
    set_init(&expected_edges);
    set_add(G_INT(e1), &expected_edges);
    set_add(G_INT(e2), &expected_edges);
    set_add(G_INT(e3), &expected_edges);

    bool equal = false;
    set_equal(&equal, &actual_edges, &expected_edges);

    set_free(NULL, &expected_edges);
    set_free(NULL, &actual_edges);
    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_incident_edges_multiple_edge(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;

    unsigned int v1 = 0;
    unsigned int v2 = 0;
    unsigned int e1 = 0;
    unsigned int e2 = 0;

    graph_vertex_insert(G_INT(a), &v1, &d);
    graph_vertex_insert(G_INT(b), &v2, &d);

    graph_connect(G_INT(a), v1, v2, &e1, &d);
    graph_connect(G_INT(b), v1, v2, &e2, &d);

    Set actual_edges;
    set_init(&actual_edges);

    unsigned int res = graph_incident_edges(&actual_edges, v1, &d);

    Set expected_edges;
    set_init(&expected_edges);
    set_add(G_INT(e1), &expected_edges);
    set_add(G_INT(e2), &expected_edges);

    bool equal = false;
    set_equal(&equal, &actual_edges, &expected_edges);

    set_free(NULL, &expected_edges);
    set_free(NULL, &actual_edges);
    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }

    return pass;
}

/* Search */
bool test_graph_find_vertices_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;

    unsigned int v1 = 0;
    unsigned int v2 = 0;
    unsigned int v3 = 0;

    graph_vertex_insert(G_INT(a), &v1, &d);
    graph_vertex_insert(G_INT(a), &v2, &d);
    graph_vertex_insert(G_INT(b), &v3, &d);

    Set actual_vertices;
    set_init(&actual_vertices);

    unsigned int res = graph_find_vertices(&actual_vertices, G_INT(a), &d);

    Set expected_vertices;
    set_init(&expected_vertices);

    set_add(G_INT(v1), &expected_vertices);
    set_add(G_INT(v2), &expected_vertices);

    bool equal = false;
    set_equal(&equal, &actual_vertices, &expected_vertices);

    set_free(NULL, &actual_vertices);
    set_free(NULL, &expected_vertices);
    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_find_vertices_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_find_vertices(NULL, 0, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_find_vertices_not_found(void)
{
    bool pass = false;
    
    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int v1 = 0;
    unsigned int v2 = 0;
    unsigned int v3 = 0;

    graph_vertex_insert(G_INT(a), &v1, &d);
    graph_vertex_insert(G_INT(a), &v2, &d);
    graph_vertex_insert(G_INT(b), &v3, &d);

    Set actual_vertices;
    set_init(&actual_vertices);

    unsigned int res = graph_find_vertices(&actual_vertices, G_INT(c), &d);

    Set expected_vertices;
    set_init(&expected_vertices);

    bool equal = false;
    set_equal(&equal, &actual_vertices, &expected_vertices);

    set_free(NULL, &actual_vertices);
    set_free(NULL, &expected_vertices);
    graph_free(NULL, &d);

    if(res == JCRL_ERR_NOT_FOUND && equal)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_find_edges_normal(void)
{
    bool pass = false;

    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int v1 = 0;
    unsigned int v2 = 0;
    unsigned int e1 = 0;
    unsigned int e2 = 0;
    unsigned int e3 = 0;

    graph_vertex_insert(G_INT(a), &v1, &d);
    graph_vertex_insert(G_INT(b), &v2, &d);

    graph_connect(G_INT(a), v1, v2, &e1, &d);
    graph_connect(G_INT(c), v1, v2, &e2, &d);
    graph_connect(G_INT(c), v1, v2, &e3, &d);

    Set actual_edges;
    set_init(&actual_edges);

    unsigned int res = graph_find_edges(&actual_edges, G_INT(c), &d);

    Set expected_edges;
    set_init(&expected_edges);
    set_add(G_INT(e2), &expected_edges);
    set_add(G_INT(e3), &expected_edges);

    bool equal = false;
    set_equal(&equal, &actual_edges, &expected_edges);

    set_free(NULL, &expected_edges);
    set_free(NULL, &actual_edges);
    graph_free(NULL, &d);

    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_find_edges_null_params(void)
{
    bool pass = false;

    unsigned int res = graph_find_edges(NULL, 0, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_graph_find_edges_not_found(void)
{
    bool pass = false;
    
    Graph d;
    graph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;

    unsigned int v1 = 0;
    unsigned int v2 = 0;
    unsigned int e1 = 0;
    unsigned int e2 = 0;
    unsigned int e3 = 0;

    graph_vertex_insert(G_INT(a), &v1, &d);
    graph_vertex_insert(G_INT(b), &v2, &d);

    graph_connect(G_INT(a), v1, v2, &e1, &d);
    graph_connect(G_INT(c), v1, v2, &e2, &d);
    graph_connect(G_INT(c), v1, v2, &e3, &d);

    Set actual_edges;
    set_init(&actual_edges);

    unsigned int res = graph_find_edges(&actual_edges, G_INT(b), &d);

    Set expected_edges;
    set_init(&expected_edges);

    bool equal = false;
    set_equal(&equal, &actual_edges, &expected_edges);

    set_free(NULL, &expected_edges);
    set_free(NULL, &actual_edges);
    graph_free(NULL, &d);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }

    return pass;
}

