#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "constants.h"
#include "list.h"
#include "stack.h"
#include "macros.h"
#include "digraph.h"

/*****************************************************************************/
/******************PRIVATE ADJACENCY MATRIX SUBIMPLEMENTATION*****************/
/*****************************************************************************/

void init_table(unsigned int*** tab)
{
    if(tab == NULL) /* null guard */
    {
        return;
    }
    
    *tab = calloc(2, sizeof(int*));

    if(*tab == NULL) /* allocation check */
    {
        return;
    }

    (*tab)[0] = calloc(2, sizeof(int));

    if((*tab)[0] == NULL)
    {
        return;
    }
}

void free_table(unsigned int rows, unsigned int cols, unsigned int** tab)
{
    if(tab == NULL) /* null guard */
    {
        return;
    }

    if(rows == 0 || cols == 0) /* bounds check */
    {
        return;
    }

    /* traverse table and free each row */
    for(unsigned int i=0;i<rows;i++)
    {
        free(tab[i]);
    }
}

void add_row(unsigned int rows, unsigned int cols, unsigned int*** tab)
{
    if(tab == NULL) /* null guard */
    {
        return;
    }

    *tab = realloc(*tab, (rows + 1) * sizeof(int*));

    if(*tab == NULL)
    {
        return;
    }

    unsigned int n = 1;

    if(cols > 0)
    {
        n = cols;
    }

    for(unsigned int i=0;i<n;i++)
    {
        (*tab)[rows] = calloc(cols, sizeof(int));
    }
}

void remove_row(unsigned int r, unsigned int rows, unsigned int cols,
        unsigned int*** tab)
{
    if(tab == NULL) /* null guard */
    {
        return;
    }

    if(rows == 0 || cols == 0 || r >= rows) /* bounds check */
    {
        return;
    }

    if(r != (rows - 1))
    {
        /*memmove((*tab)[r], (*tab)[r+1],
                (rows - 1) * sizeof(enum _VertexConnection*));*/

        for(unsigned int i=r;i<(rows-r);i++)
        {
            (*tab)[i] = (*tab)[i+1];
        }
    }

    free((*tab)[rows-1]);
}

void add_col(unsigned int rows, unsigned int cols, unsigned int*** tab)
{
    if(tab == NULL) /* null guard */
    {
        return;
    }

    if(rows == 0 || cols == 0) /* bounds check */
    {
        return;
    }

    /* traverse the table and add to each row */
    for(unsigned int i=0;i<rows;i++)
    {
        (*tab)[i] = realloc((*tab)[i], (cols + 1) * sizeof(int));
    }
}

void remove_col(unsigned int c, unsigned int rows, unsigned int cols,
        unsigned int*** tab)
{
    if(tab == NULL) /* null guard */
    {
        return;
    }

    if(rows == 0 || cols == 0 || c >= cols) /* bounds check */
    {
        return;
    }

    /* traverse the table and left-shift each row */
    for(unsigned int i=0;i<rows;i++)
    {
        if(c != cols - 1)
        {
            /* left shift row by copying each element to the left */
            for(unsigned int j=c;j<(cols-c);j++)
            {
                (*tab)[i][j] = (*tab)[i][j+1];
            }
        }

        (*tab)[i] = realloc((*tab)[i], (cols - 1) * sizeof(int));
    }
}

/*****************************************************************************/

/* Initialisation */
unsigned int digraph_init(Digraph* digraph)
{
    if(digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    /* zero size fields */
    digraph->v = 0;
    digraph->e = 0;
    
    /* initialise vertices list */
    digraph->vertices = calloc(1, sizeof(List));

    if(digraph->vertices == NULL) /* allocation check */
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }

    unsigned int res = list_init(digraph->vertices);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* initialise edges list */
    digraph->edges = calloc(1, sizeof(List));

    if(digraph->edges == NULL)
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }

    res = list_init(digraph->edges);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    init_table(&digraph->adjtab); /* initialise adjacency matrix */
    init_table(&digraph->edgetab); /* initialise edge table */

    return JCRL_ERR_OK;
}

unsigned int digraph_free(void (handle_free)(void*), Digraph* digraph)
{
    if(digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    /* free vertices list */
    unsigned int res = list_free(handle_free, digraph->vertices);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* free edges list */
    res = list_free(handle_free, digraph->edges);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    free_table(digraph->v, digraph->v, digraph->adjtab);
    free_table(digraph->e, 2, digraph->edgetab);

    return JCRL_ERR_OK;
}

/* Size */
unsigned int digraph_order(unsigned int* order, Digraph* digraph)
{
    if(order == NULL || digraph == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }

    *order = digraph->v;

    return JCRL_ERR_OK;
}

unsigned int digraph_size(unsigned int* size, Digraph* digraph)
{
    if(size == NULL || digraph == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }

    *size = digraph->e;

    return JCRL_ERR_OK;
}

/* Access */
unsigned int digraph_vertex_get(void** data, unsigned int vertex,
        Digraph* digraph)
{
    if(digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = list_get(data, vertex, digraph->vertices);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

unsigned int digraph_vertex_set(void* data, unsigned int vertex,
        Digraph* digraph)
{
    if(digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = list_set(data, vertex, digraph->vertices);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}


unsigned int digraph_edge_get(void** data, unsigned int edge, Digraph* digraph)
{
    if(digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = list_get(data, edge, digraph->edges);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

unsigned int digraph_edge_set(void* data, unsigned int edge, Digraph* digraph)
{
    if(digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = list_set(data, edge, digraph->edges);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

/* Membership */
unsigned int digraph_vertex_in(bool* in, void* data, Digraph* digraph)
{
    if(in == NULL || digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = list_in(in, data, digraph->vertices);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

unsigned int digraph_edge_in(bool* in, void* data, Digraph* digraph)
{
    if(in == NULL || digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = list_in(in, data, digraph->edges);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

/* Equality */
unsigned int digraph_equal(bool* equal, Digraph* a, Digraph* b)
{
    if(equal == NULL || a == NULL || b == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }

    /* check the dimensions of both graphs */
    if(a->v != b->v || a->e != b->e)
    {
        *equal = false;
        return JCRL_ERR_OK;
    }

    unsigned int res = JCRL_ERR_OK;

    Multiset multiset_a;

    res = multiset_init(&multiset_a);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    Multiset multiset_b;
    
    res = multiset_init(&multiset_b);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    void* tmp = NULL;

    /* convert a's vertex labels to multiset */
    for(unsigned int i=0;i<a->v;i++)
    {
        res = list_get((void**)&tmp, i, a->vertices);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        res = multiset_add(G_INT(tmp), &multiset_a);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }
    }

    /* convert b's vertex labels to multiset */
    for(unsigned int i=0;i<b->v;i++)
    {
        res = list_get((void**)&tmp, i, b->vertices);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        res = multiset_add(G_INT(tmp), &multiset_b);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }
    }

    /* test for multiset equality */
    res = multiset_equal(equal, &multiset_a, &multiset_b);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    res = multiset_free(NULL, &multiset_a);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }
 
    res = multiset_free(NULL, &multiset_b);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

/* Operations */
unsigned int digraph_vertex_insert(void* data, unsigned int* vertex,
        Digraph* digraph)
{
    if(vertex == NULL || digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    /* append vertex to vertices list */
    unsigned int res = list_append(data, digraph->vertices);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* expand adjacency matrix */
    add_row(digraph->v, digraph->v, &digraph->adjtab);
    add_col(digraph->v, digraph->v, &digraph->adjtab);

    digraph->v++; /* increment counter in digraph struct */
    *vertex = digraph->v - 1; /* inform caller of their vertex number */

    return JCRL_ERR_OK;
}

unsigned int digraph_vertex_remove(unsigned int vertex, Digraph* digraph)
{
    if(digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    if(vertex >= digraph->v) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    /* remove vertex label from vertices list */
    unsigned int res = list_remove(vertex, digraph->vertices);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* contract adjacency matrix */
    remove_row(vertex, digraph->v, digraph->v, &digraph->adjtab);
    remove_col(vertex, digraph->v, digraph->v, &digraph->adjtab);

    digraph->v--; /* decrement our vertex counter */

    return JCRL_ERR_OK;
}

unsigned int digraph_connect(void* data, unsigned int a, unsigned int b,
        unsigned int* edge, Digraph* digraph)
{
    if(edge == NULL || digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    if(a >= digraph->v || b >= digraph->v) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    /* append edge label to list of edge labels */
    unsigned int res = list_append(data, digraph->edges);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* add column to adjacency matrix */
    add_col(digraph->v, digraph->e, &digraph->adjtab);

    /* connect vertices in our adjacency matrix */
    digraph->adjtab[a][b]++;

    /* add row to edge table */
    add_row(digraph->e, 2, &digraph->edgetab);

    /* add vertex pair to edge table */
    digraph->edgetab[digraph->e][0] = a;
    digraph->edgetab[digraph->e][1] = b;

    digraph->e++; /* increment our edge counter */
    *edge = digraph->e - 1; /* inform caller of their edge number */

    return JCRL_ERR_OK;
}

unsigned int digraph_disconnect(unsigned int edge, Digraph* digraph)
{
    if(digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    if(edge >= digraph->e) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    unsigned int res = list_remove(edge, digraph->edges);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    unsigned int target = digraph->edgetab[edge][1];

    /* disconnect vertices in our adjacency matrix */
    digraph->adjtab[edge][target]--;

    /* remove entry from edge table */
    remove_row(edge, digraph->e, 2, &digraph->edgetab);

    digraph->e--; /* decrement our edge counter */

    return JCRL_ERR_OK;
}

unsigned int digraph_in_neighbours(Set* neighbours, unsigned int vertex,
        Digraph* digraph)
{
    if(neighbours == NULL || digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    if(vertex >= digraph->v) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    unsigned int res = JCRL_ERR_OK;

    for(unsigned int i=0;i<digraph->v;i++)
    {
        if(digraph->adjtab[i][vertex] > 0)
        {
            res = set_add(G_INT(i), neighbours);

            if(res != JCRL_ERR_OK)
            {
                return res;
            }
        }
    }

    return JCRL_ERR_OK;
}

unsigned int digraph_out_neighbours(Set* neighbours, unsigned int vertex,
        Digraph* digraph)
{
    if(neighbours == NULL || digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    if(vertex >= digraph->v) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    unsigned int res = JCRL_ERR_OK;

    for(unsigned int i=0;i<digraph->v;i++)
    {
        if(digraph->adjtab[vertex][i] > 0)
        {
            res = set_add(G_INT(i), neighbours);

            if(res != JCRL_ERR_OK)
            {
                return res;
            }
        }
    }

    return JCRL_ERR_OK;
}

unsigned int digraph_adjacent(bool* adjacent, unsigned int a, unsigned int b,
        Digraph* digraph)
{
    if(adjacent == NULL || digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    if(a >= digraph->v || b >= digraph->v) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    /* perform lookup against adjacency matrix */
    if(digraph->adjtab[a][b])
    {
        *adjacent = true;
    }
    else
    {
        *adjacent = false;
    }

    return JCRL_ERR_OK;
}

unsigned int digraph_adjacent_via(Set* edges, unsigned int a,
        unsigned int b, Digraph* digraph)
{
    if(edges == NULL || digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    bool adjacent = false;
    unsigned int res = digraph_adjacent(&adjacent, a, b, digraph);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    if(!adjacent) /* if vertices aren't adjacent, don't bother */
    {
        return JCRL_ERR_IMPOSSIBLE;
    }

    unsigned int* current_edge = NULL;

    /* search each column for matching pairs */
    for(unsigned int i=0;i<digraph->e;i++)
    {
        current_edge = digraph->edgetab[i];

        if(current_edge[0] == a && current_edge[1] == b)
        {
            /* add edge number to set of adjacent edges */
            res = set_add(G_INT(i), edges);

            if(res != JCRL_ERR_OK)
            {
                return res;
            }
        }
    }

    return JCRL_ERR_OK;
}

unsigned int digraph_incident(bool* incident, unsigned int edge,
        unsigned int vertex, Digraph* digraph)
{
    if(incident == NULL || digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    if(edge >= digraph->e || vertex >= digraph->v) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }
    
    /* endpoints */
    unsigned int a = digraph->edgetab[edge][0];
    unsigned int b = digraph->edgetab[edge][1];

    if(vertex == a || vertex == b)
    {
        *incident = true;
    }
    else
    {
        *incident = false;
    }

    return JCRL_ERR_OK;
}

unsigned int digraph_endpoints(unsigned int* a, unsigned int* b,
        unsigned int edge, Digraph* digraph)
{
    if(a == NULL || b == NULL || digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    if(edge >= digraph->e) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    /* lookup endpoints in edge table */
    *a = digraph->edgetab[edge][0];
    *b = digraph->edgetab[edge][1];

    return JCRL_ERR_OK;
}

unsigned int digraph_in_degree(unsigned int* in_degree, unsigned int vertex,
        Digraph* digraph)
{
    if(in_degree == NULL || digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    if(vertex >= digraph->v) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    unsigned int col_sum = 0;

    /* sum column of adjacency matrix */
    for(unsigned int i=0;i<digraph->v;i++)
    {
        col_sum += digraph->adjtab[i][vertex];
    }

    *in_degree = col_sum; /* return value */

    return JCRL_ERR_OK;
}

unsigned int digraph_out_degree(unsigned int* out_degree, unsigned int vertex,
        Digraph* digraph)
{
    if(out_degree == NULL || digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    if(vertex >= digraph->v) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    unsigned int row_sum = 0;

    /* sum row of adjacency matrix */
    for(unsigned int i=0;i<digraph->v;i++)
    {
        row_sum += digraph->adjtab[vertex][i];
    }

    *out_degree = row_sum; /* return value */

    return JCRL_ERR_OK;
}

unsigned int digraph_incident_edges(Set* edges, unsigned int vertex,
        Digraph* digraph)
{
    if(edges == NULL || digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }
  
    if(vertex >= digraph->v) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    unsigned int res = JCRL_ERR_OK;

    for(unsigned int i=0;i<digraph->e;i++)
    {
        if(digraph->edgetab[i][0] == vertex || digraph->edgetab[i][1] == vertex)
        {
            res = set_add(G_INT(i), edges);

            if(res != JCRL_ERR_OK)
            {
                return res;
            }
        }
    }
    
    return JCRL_ERR_OK;
}

/* Search */
unsigned int digraph_find_vertices(Set* vertices, void* data, Digraph* digraph)
{
    if(vertices == NULL || digraph == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }

    bool list_contains_vertex = false;
    unsigned int res = list_in(&list_contains_vertex, data, digraph->vertices);
   
    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    if(!list_contains_vertex)
    {
        return JCRL_ERR_NOT_FOUND;
    }

    void* val = NULL;

    /* traverse vertex label list looking for matches */
    for(unsigned int i=0;i<digraph->v;i++)
    {
        res = list_get(&val, i, digraph->vertices);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        if(val == data)
        {
            res = set_add(G_INT(i), vertices);
        }
    }

    return JCRL_ERR_OK;
}

unsigned int digraph_find_edges(Set* edges, void* data, Digraph* digraph)
{
    if(edges == NULL || digraph == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }

    bool list_contains_edge = false;
    unsigned int res = list_in(&list_contains_edge, data, digraph->edges);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    if(!list_contains_edge)
    {
        return JCRL_ERR_NOT_FOUND;
    }

    void* val = NULL;

    /* travserse edge label list looking for matches */
    for(unsigned int i=0;i<digraph->e;i++)
    {
        res = list_get(&val, i, digraph->edges);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        if(val == data)
        {
            res = set_add(G_INT(i), edges);

            if(res != JCRL_ERR_OK)
            {
                return res;
            }
        }
    }

    return JCRL_ERR_OK;
}

