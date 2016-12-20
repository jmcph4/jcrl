#ifndef VERTEX_H_
#define VERTEX_H_

#include <stdbool.h>

#include "dlist.h"

struct _Vertex
{
    void* data;
    DList* neighbours;
};

typedef struct _Vertex Vertex;

/* Initialisation */
unsigned int vertex_init(Vertex* vertex);
unsigned int vertex_free(void (handle_free)(void*), Vertex* vertex);

/* Equality */
unsigned int vertex_equal(bool* equal, Vertex* a, Vertex* b);

/* Access */
unsigned int vertex_get(void** data, Vertex* vertex);
unsigned int vertex_set(void* data, Vertex* vertex);
unsigned int vertex_degree(unsigned int* degree, Vertex* vertex);

/* Operations */
unsigned int vertex_add_neighbour(Vertex* neighbour, Vertex* vertex);
unsigned int vertex_remove_neighbour(Vertex* neighbour, Vertex* vertex);

#endif /* VERTEX_H_ */
