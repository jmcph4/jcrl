#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "constants.h"
#include "map.h"
#include "stack.h"
#include "macros.h"
#include "digraph.h"

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
    digraph->vertices = calloc(1, sizeof(Map));

    if(digraph->vertices == NULL) /* allocation check */
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }

    unsigned int res = map_init(digraph->vertices);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* initialise edges list */
    digraph->edges = calloc(1, sizeof(Map));

    if(digraph->edges == NULL)
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }

    res = map_init(digraph->edges);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    digraph->adjtab = calloc(1, sizeof(List));

    if(digraph->adjtab == NULL) /* allocation check */
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }

    res = list_init(digraph->adjtab);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    digraph->edgetab = calloc(1, sizeof(List));

    if(digraph->edgetab == NULL) /* allocation check */
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }

    res = list_init(digraph->edgetab);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    return JCRL_ERR_OK;
}

unsigned int digraph_free(void (handle_free)(void*), Digraph* digraph)
{
    if(digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    /* free vertices list */
    unsigned int res = map_free(handle_free, digraph->vertices);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* free edges list */
    res = map_free(handle_free, digraph->edges);
    return res;
    if(res != JCRL_ERR_OK)
    {
        return res;
    }

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

    if(vertex != 0 && vertex >= digraph->v) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }
    
    unsigned int res = map_get(G_INT(vertex), data, digraph->vertices);

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

    if(vertex != 0 && vertex >= digraph->v) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    unsigned int res = map_set(G_INT(vertex), data, digraph->vertices);

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

    if(edge != 0 && edge >= digraph->e) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }
    
    unsigned int res = map_get(G_INT(edge), data, digraph->edges);

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

    if(edge != 0 && edge >= digraph->e) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    unsigned int res = map_set(G_INT(edge), data, digraph->edges);

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

    unsigned int res = map_value_in(in, data, digraph->vertices);

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

    unsigned int res = map_value_in(in, data, digraph->edges);

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
        res = map_get(G_INT(i), (void**)&tmp, a->vertices);

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
        res = map_get(G_INT(i), (void**)&tmp, b->vertices);

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
    unsigned int res = map_set(G_INT(digraph->v), data, digraph->vertices);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    List* curr_adjtab_row = NULL;

    /* expand existing adjacency table entries */
    for(unsigned int i=0;i<digraph->v;i++)
    {
        res = list_get((void**)&curr_adjtab_row, i, digraph->adjtab);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        res = list_append(G_INT(0), curr_adjtab_row);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }
    }

    /* add new (already-expanded entry) */
    List* new_adjtab_row = calloc(1, sizeof(List));

    if(new_adjtab_row == NULL) /* allocation check */
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }

    for(unsigned int i=0;i<=digraph->v;i++)
    {
        res = list_append(G_INT(0), new_adjtab_row);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }
    }

    res = list_append(new_adjtab_row, digraph->adjtab);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

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

    if(vertex != 0 && vertex >= digraph->v) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    /* remove vertex label from vertices list */
    unsigned int res = map_remove(G_INT(vertex), digraph->vertices);

    if(res != JCRL_ERR_OK)
    {
        if(res == JCRL_ERR_NOT_FOUND && digraph->v == 0)
        {
            return JCRL_ERR_OUT_OF_BOUNDS;
        }
        else
        {
            return res;
        }
    }

    /* contract adjacency matrix */
    res = list_remove(vertex, digraph->adjtab);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    List* curr_adjtab_row = NULL;

    for(unsigned int i=0;i<digraph->v-1;i++)
    {
        res = list_get((void**)&curr_adjtab_row, i, digraph->adjtab);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        res = list_remove(vertex, curr_adjtab_row);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }
    }

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

    /* bounds check */
    if((a != 0 && a >= digraph->v) || (b != 0 && b >= digraph->v))
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    /* append edge label to list of edge labels */
    unsigned int res = map_set(G_INT(digraph->e), data, digraph->edges);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* expand adjacency matrix */
    List* new_adjtab_col = calloc(1, sizeof(List));

    if(new_adjtab_col == NULL) /* allocation check */
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }

    res = list_init(new_adjtab_col);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* connect vertices in our adjacency matrix */
    List* adjtab_entry = NULL;

    res = list_get((void**)&adjtab_entry, a, digraph->adjtab);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    uintptr_t degree = 0;

    res = list_get((void**)&degree, b, adjtab_entry);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    res = list_set(G_INT(degree + 1), b, adjtab_entry);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    List* edge_pair = calloc(1, sizeof(List));

    if(edge_pair == NULL)
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }

    res = list_init(edge_pair);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* set up new edge pair entry */
    res = list_insert(G_INT(a), 0, edge_pair);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    res = list_insert(G_INT(b), 1, edge_pair);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    res = list_append(edge_pair, digraph->edgetab);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

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

    if(edge != 0 && edge >= digraph->e) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    unsigned int res = map_remove(G_INT(edge), digraph->edges);

    if(res != JCRL_ERR_OK)
    {
        if(res == JCRL_ERR_NOT_FOUND && digraph->e == 0)
        {
            return JCRL_ERR_OUT_OF_BOUNDS;
        }
        else
        {
            return res;
        }
    }
    
    List* edge_pair = NULL;

    res = list_get((void**)&edge_pair, edge, digraph->edgetab);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    uintptr_t target = 0;

    res = list_get((void**)&target, 1, edge_pair);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    uintptr_t degree = 0;
    
    res = list_get((void**)&degree, target, edge_pair);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    res = list_set(G_INT(degree - 1), target, edge_pair);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    /* remove entry from edge table */
    res = list_remove(edge, digraph->edgetab);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

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

    if(vertex != 0 && vertex >= digraph->v) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    unsigned int res = JCRL_ERR_OK;
    uintptr_t degree = 0;
    List* adjtab_entry = NULL;

    for(unsigned int i=0;i<digraph->v;i++)
    {
        res = list_get((void**)&adjtab_entry, i, digraph->adjtab);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        res = list_get((void**)&degree, vertex, adjtab_entry);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        if(degree > 0)
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

    if(vertex != 0 && vertex >= digraph->v) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    unsigned int res = JCRL_ERR_OK;
    uintptr_t degree = 0;
    List* adjtab_entry = NULL;

    res = list_get((void**)&adjtab_entry, vertex, digraph->adjtab);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    for(unsigned int i=0;i<digraph->v;i++)
    {
        res = list_get((void**)&degree, i, adjtab_entry);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        if(degree > 0)
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

    /* bounds check */
    if((a != 0 && a >= digraph->v) || (b != 0 && b >= digraph->v))
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    List* row = NULL;

    unsigned int res = list_get((void**)&row, a, digraph->adjtab);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    uintptr_t degree = 0;

    res = list_get((void**)&degree, b, row);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* perform lookup against adjacency matrix */
    if(degree != 0)
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

    uintptr_t endpoint_a = 0;
    uintptr_t endpoint_b = 0;
    List* current_edge = NULL;
    
    /* search each column for matching pairs */
    for(unsigned int i=0;i<digraph->e;i++)
    {
        res = list_get((void**)&current_edge, i, digraph->edgetab);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        res = list_get((void**)&endpoint_a, 0, current_edge);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        res = list_get((void**)&endpoint_b, 1, current_edge);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        if(endpoint_a == a && endpoint_b == b)
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

    /* bounds check */
    if((edge != 0 && edge >= digraph->e) ||
            (vertex != 0 && vertex >= digraph->v))
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }
    
    List* row = NULL;

    unsigned int res = list_get((void**)&row, edge, digraph->edgetab);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* endpoints */
    uintptr_t a = 0;
    uintptr_t b = 0;

    res = list_get((void**)&a, 0, row);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    res = list_get((void**)&b, 1, row);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

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

    if(edge != 0 && edge >= digraph->e) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    List* row = NULL;

    unsigned int res = list_get((void**)&row, edge, digraph->edgetab);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* lookup endpoints in edge table */
    res = list_get((void**)a, 0, row);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    res = list_get((void**)b, 1, row);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    return JCRL_ERR_OK;
}

unsigned int digraph_in_degree(unsigned int* in_degree, unsigned int vertex,
        Digraph* digraph)
{
    if(in_degree == NULL || digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    if(vertex !=0 && vertex >= digraph->v) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    unsigned int res = JCRL_ERR_OK;
    unsigned int col_sum = 0;
    List* curr_row = NULL;
    uintptr_t curr_in_degree = 0;

    /* sum column of adjacency matrix */
    for(unsigned int i=0;i<digraph->v;i++)
    {
        res = list_get((void**)&curr_row, i, digraph->adjtab);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        res = list_get((void**)&curr_in_degree, vertex, curr_row);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        col_sum += curr_in_degree;
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

    if(vertex != 0 && vertex >= digraph->v) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    unsigned int row_sum = 0;
    uintptr_t curr_out_degree = 0;
    List* row = NULL;

    unsigned int res = list_get((void**)&row, vertex, digraph->adjtab);

    if(res != JCRL_ERR_OK)
    {
       return res;
    }
    
    /* sum column of adjacency matrix */
    for(unsigned int i=0;i<digraph->v;i++)
    {
        res = list_get((void**)&curr_out_degree, i, row);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        row_sum += curr_out_degree;
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
  
    if(vertex != 0 && vertex >= digraph->v) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    uintptr_t endpoint_a = 0;
    uintptr_t endpoint_b = 0;
    List* curr_edge_pair = NULL;

    unsigned int res = JCRL_ERR_OK;

    for(unsigned int i=0;i<digraph->e;i++)
    {
        /* get current edge table entry */
        res = list_get((void**)&curr_edge_pair, i, digraph->edgetab);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        /* extract first endpoint */
        res = list_get((void**)&endpoint_a, 0, curr_edge_pair);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        /* extract second endpoint */
        res = list_get((void**)&endpoint_b, 1, curr_edge_pair);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }
       
        /* check for match */ 
        if(endpoint_a == vertex || endpoint_b == vertex)
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

    bool map_contains_vertex = false;
    unsigned int res = map_value_in(&map_contains_vertex, data,
            digraph->vertices);
   
    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    if(!map_contains_vertex)
    {
        return JCRL_ERR_NOT_FOUND;
    }

    void* curr_label = NULL;

    for(unsigned int i=0;i<digraph->v;i++)
    {
        res = map_get(G_INT(i), &curr_label, digraph->vertices);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        if(curr_label == data)
        {
            res = set_add(G_INT(i), vertices);

            if(res != JCRL_ERR_OK)
            {
                return res;
            }
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

    bool map_contains_edge = false;
    unsigned int res = map_value_in(&map_contains_edge, data, digraph->edges);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    if(!map_contains_edge)
    {
        return JCRL_ERR_NOT_FOUND;
    }

    void* curr_label = NULL;

    for(unsigned int i=0;i<digraph->e;i++)
    {
        res = map_get(G_INT(i), &curr_label, digraph->edges);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        if(curr_label == data)
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

