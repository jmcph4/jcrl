#ifndef DIGRAPH_H_
#define DIGRAPH_H_

#include <stdbool.h>

#include "list.h"
#include "set.h"

struct _Digraph
{
    unsigned int v;             /* number of vertices */
    unsigned int e;             /* number of edges */
    List* vertices;             /* vertex labels */
    List* edges;                /* edge labels */
    unsigned int** adjtab;      /* adjacency matrix */
    unsigned int** edgetab;     /* edge table */
};

typedef struct _Digraph Digraph;

/* Initialisation */
unsigned int digraph_init(Digraph* digraph);
unsigned int digraph_free(void (handle_free)(void*), Digraph* digraph);

/* Access */
unsigned int digraph_vertex_get(void** data, unsigned int vertex,
        Digraph* digraph);
unsigned int digraph_vertex_set(void* data, unsigned int vertex,
        Digraph* digraph);

unsigned int digraph_edge_get(void** data, unsigned int edge, Digraph* digraph);
unsigned int digraph_edge_set(void* data, unsigned int edge, Digraph* digraph);

/* Size */
unsigned int digraph_order(unsigned int* order, Digraph* digraph);
unsigned int digraph_size(unsigned int* size, Digraph* digraph);

/* Equality */
unsigned int digraph_equal(bool* equal, Digraph* a, Digraph* b);

/* Membership */
unsigned int digraph_vertex_in(bool* in, void* data, Digraph* digraph);
unsigned int digraph_edge_in(bool* in, void* data, Digraph* digraph);

/* Operations */
unsigned int digraph_vertex_insert(void* data, unsigned int* vertex,
        Digraph* digraph);
unsigned int digraph_vertex_remove(unsigned int vertex, Digraph* digraph);

unsigned int digraph_connect(void* data, unsigned int a, unsigned int b,
        unsigned int* edge, Digraph* digraph);
unsigned int digraph_disconnect(unsigned int edge, Digraph* digraph);

unsigned int digraph_in_neighbours(Set* neighbours, unsigned int vertex,
        Digraph* digraph);
unsigned int digraph_out_neighbours(Set* neighbours, unsigned int vertex,
        Digraph* digraph);

unsigned int digraph_adjacent(bool* adjacent, unsigned int a, unsigned int b,
        Digraph* digraph);
unsigned int digraph_adjacent_via(Set* edges, unsigned int a,
        unsigned int b, Digraph* digraph);

unsigned int digraph_incident(bool* incident, unsigned int edge,
        unsigned int vertex, Digraph* digraph);
unsigned int digraph_endpoints(unsigned int* a, unsigned int* b,
        unsigned int edge, Digraph* digraph);

unsigned int digraph_in_degree(unsigned int* in_degree, unsigned int vertex,
        Digraph* digraph);
unsigned int digraph_out_degree(unsigned int* out_degree, unsigned int vertex,
        Digraph* digraph);

unsigned int digraph_incident_edges(Set* edges, unsigned int vertex,
        Digraph* digraph);

/* Search */
unsigned int digraph_find_vertices(Set* vertices, void* data, Digraph* digraph);
unsigned int digraph_find_edges(Set* edges, void* data, Digraph* digraph);

#endif /* DIGRAPH_H_ */

