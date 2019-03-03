#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdbool.h>

#include "set.h"
#include "digraph.h"
#include "graph.h"

typedef struct
{
    Digraph* digraph;
    unsigned int e;
} Graph;

/* Initialisation */
unsigned int graph_init(Graph* graph);
unsigned int graph_free(void (handle_free)(void*), Graph* graph);

/* Access */
unsigned int graph_vertex_get(void** data, unsigned int vertex,
        Graph* graph);
unsigned int graph_vertex_set(void* data, unsigned int vertex,
        Graph* graph);

unsigned int graph_edge_get(void** data, unsigned int edge, Graph* graph);
unsigned int graph_edge_set(void* data, unsigned int edge, Graph* graph);

/* Size */
unsigned int graph_order(unsigned int* order, Graph* graph);
unsigned int graph_size(unsigned int* size, Graph* graph);

/* Equality */
unsigned int graph_equal(bool* equal, Graph* a, Graph* b);

/* Membership */
unsigned int graph_vertex_in(bool* in, void* data, Graph* graph);
unsigned int graph_edge_in(bool* in, void* data, Graph* graph);

/* Operations */
unsigned int graph_vertex_insert(void* data, unsigned int* vertex,
        Graph* graph);
unsigned int graph_vertex_remove(unsigned int vertex, Graph* graph);

unsigned int graph_connect(void* data, unsigned int a, unsigned int b,
        unsigned int* edge, Graph* graph);
unsigned int graph_disconnect(unsigned int edge, Graph* graph);

unsigned int graph_neighbours(Set* neighbours, unsigned int vertex,
        Graph* graph);

unsigned int graph_adjacent(bool* adjacent, unsigned int a, unsigned int b,
        Graph* graph);
unsigned int graph_adjacent_via(Set* edges, unsigned int a,
        unsigned int b, Graph* graph);

unsigned int graph_incident(bool* incident, unsigned int edge,
        unsigned int vertex, Graph* graph);
unsigned int graph_endpoints(unsigned int* a, unsigned int* b,
        unsigned int edge, Graph* graph);

unsigned int graph_degree(unsigned int* degree, unsigned int vertex,
        Graph* graph);

unsigned int graph_incident_edges(Set* edges, unsigned int vertex,
        Graph* graph);

/* Search */
unsigned int graph_find_vertices(Set* vertices, void* data, Graph* graph);
unsigned int graph_find_edges(Set* edges, void* data, Graph* graph);

#endif /* GRAPH_H_ */

