#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "constants.h"
#include "digraph.h"
#include "set.h"
#include "graph.h"

void remove_odd(Set* set)
{
    if(set == NULL)
    {
        return;
    }

    List list;
    list_init(&list);

    set_enumerate(&list, set);

    for(struct _LNode* ptr=list.head;ptr!=NULL;ptr=ptr->next)
    {
        if((uintmax_t)(ptr->data) % 2 != 0)
        {
            set_remove(ptr->data, set);
        }
    }

    list_free(NULL, &list);
}

/* Initialisation */
unsigned int graph_init(Graph* graph)
{
    if(graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    graph->digraph = calloc(1, sizeof(Digraph));

    if(graph->digraph == NULL)
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }

    unsigned int res = digraph_init(graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    graph->e = 0;

    return JCRL_ERR_OK;
}

unsigned int graph_free(void (handle_free)(void*), Graph* graph)
{
    if(graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = digraph_free(handle_free, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

/* Access */
unsigned int graph_vertex_get(void** data, unsigned int vertex, Graph* graph)
{
    if(data == NULL || graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = digraph_vertex_get(data, vertex, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

unsigned int graph_vertex_set(void* data, unsigned int vertex, Graph* graph)
{
    if(graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = digraph_vertex_set(data, vertex, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

unsigned int graph_edge_get(void** data, unsigned int edge, Graph* graph)
{ 
    if(data == NULL || graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    if(edge % 2 != 0) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    unsigned int res = digraph_edge_get(data, edge, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

unsigned int graph_edge_set(void* data, unsigned int edge, Graph* graph)
{
    if(graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    if(edge % 2 != 0) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }
    
    unsigned int res = digraph_edge_set(data, edge, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

/* Membership */
unsigned int graph_vertex_in(bool* in, void* data, Graph* graph)
{
    if(in == NULL || graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = digraph_vertex_in(in, data, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

unsigned int graph_edge_in(bool* in, void* data, Graph* graph)
{
    if(in == NULL || graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = digraph_edge_in(in, data, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

/* Equality */
unsigned int graph_equal(bool* equal, Graph* a, Graph* b)
{
    if(equal == NULL || a == NULL || b == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = digraph_equal(equal, a->digraph, b->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

/* Size */
unsigned int graph_order(unsigned int* order, Graph* graph)
{
    if(order == NULL || graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = digraph_order(order, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

unsigned int graph_size(unsigned int* size, Graph* graph)
{
    if(size == NULL || graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    *size = graph->e;

    return JCRL_ERR_OK;
}

/* Operations */
unsigned int graph_vertex_insert(void* data, unsigned int* vertex, Graph* graph)
{
    if(vertex == NULL || graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = digraph_vertex_insert(data, vertex, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

unsigned int graph_vertex_remove(unsigned int vertex, Graph* graph)
{
    if(graph == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = digraph_vertex_remove(vertex, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

unsigned int graph_connect(void* data, unsigned int a, unsigned int b,
        unsigned int* edge, Graph* graph)
{
    if(edge == NULL || graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    /* a -> b */
    unsigned int res = digraph_connect(data, a, b, edge, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    unsigned int reported_edge = *edge;

    /* b -> a */
    res = digraph_connect(data, b, a, edge, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    graph->e = graph->digraph->e / 2;

    *edge = reported_edge;

    return JCRL_ERR_OK;
}

unsigned int graph_disconnect(unsigned int edge, Graph* graph)
{
    if(graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    if(edge % 2 != 0) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    /* b -> a */
    unsigned int res = digraph_disconnect(edge + 1, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* a -> b */
    res = digraph_disconnect(edge, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    graph->e = graph->digraph->e / 2;

    return JCRL_ERR_OK;
}

unsigned int graph_neighbours(Set* neighbours, unsigned int vertex,
        Graph* graph)
{
    if(neighbours == NULL || graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    Set in_neighbours;
    Set out_neighbours;

    /* initialise inbound neighbours set */
    unsigned int res = set_init(&in_neighbours);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* initialise outbound neighbours set */
    res = set_init(&out_neighbours);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* inbound neighbours */
    res = digraph_in_neighbours(&in_neighbours, vertex, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* outbound neighbours */
    res = digraph_out_neighbours(&out_neighbours, vertex, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }
   
    /* combine */
    res = set_union(&in_neighbours, &out_neighbours, neighbours);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }
   
    /* free inbound neighbours set */
    res = set_free(NULL, &in_neighbours);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* free outbound neighbours set */
    res = set_free(NULL, &out_neighbours);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

unsigned int graph_adjacent(bool* adjacent, unsigned int a, unsigned int b,
        Graph* graph)
{
    if(adjacent == NULL || graph == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }

    bool a_b_adjacent = false;
    bool b_a_adjacent = false;

    unsigned int res = digraph_adjacent(&a_b_adjacent, a, b, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    res = digraph_adjacent(&b_a_adjacent, b, a, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    *adjacent = a_b_adjacent || b_a_adjacent;

    return JCRL_ERR_OK;
}

unsigned int graph_adjacent_via(Set* edges, unsigned int a,
        unsigned int b, Graph* graph)
{
    if(edges == NULL || graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = digraph_adjacent_via(edges, a, b, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    remove_odd(edges);

    return JCRL_ERR_OK;
}

unsigned int graph_incident(bool* incident, unsigned int edge,
        unsigned int vertex, Graph* graph)
{
    if(incident == NULL || graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = digraph_incident(incident, edge, vertex, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    } 

    return JCRL_ERR_OK;
}

unsigned int graph_endpoints(unsigned int* a, unsigned int* b,
        unsigned int edge, Graph* graph)
{
    if(a == NULL || b == NULL || graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    if(edge % 2 != 0) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    unsigned int res = digraph_endpoints(a, b, (edge) ? edge - 1 : edge, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

unsigned int graph_degree(unsigned int* degree, unsigned int vertex,
        Graph* graph)
{
    if(degree == NULL || graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    Set edges;

    unsigned int res = set_init(&edges);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    res = digraph_incident_edges(&edges, vertex, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    List edges_list;

    res = list_init(&edges_list);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    res = set_enumerate(&edges_list, &edges);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    unsigned int num_incident_edges = 0;

    res = set_cardinality(&num_incident_edges, &edges);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    *degree = num_incident_edges / 2;

    return JCRL_ERR_OK;
}

unsigned int graph_incident_edges(Set* edges, unsigned int vertex,
        Graph* graph)
{
    if(edges == NULL || graph == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = digraph_incident_edges(edges, vertex, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    remove_odd(edges);

    return JCRL_ERR_OK;
}

/* Search */
unsigned int graph_find_vertices(Set* vertices, void* data, Graph* graph)
{
    if(vertices == NULL || graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = digraph_find_vertices(vertices, data, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

unsigned int graph_find_edges(Set* edges, void* data, Graph* graph)
{
    if(edges == NULL || graph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = digraph_find_edges(edges, data, graph->digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }
   
    remove_odd(edges); /* filter dual edges */

    return JCRL_ERR_OK;
}

