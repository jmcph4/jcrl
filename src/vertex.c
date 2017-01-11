#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"
#include "list.h"
#include "vertex.h"

/* Initialisation */
unsigned int vertex_init(Vertex* vertex)
{
    if(vertex == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    vertex->data = NULL;
    
    vertex->neighbours = calloc(1, sizeof(List));
    
    if(vertex->neighbours == NULL)
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }
    
    unsigned int res = list_init(vertex->neighbours);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    return JCRL_ERR_OK;
}

unsigned int vertex_free(void (handle_free)(void*), Vertex* vertex)
{
    if(vertex == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = list_free(NULL, vertex->neighbours);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    if(handle_free != NULL)
    {
        handle_free(vertex->data);
    }
    else
    {
        free(vertex->data);
    }
    
    return JCRL_ERR_OK;
}

/* Equality */
unsigned int vertex_equal(bool* equal, Vertex* a, Vertex* b)
{
    if(equal == NULL || a == NULL || b == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    *equal = false;
    
    bool equal_lists = false;
    
    unsigned int res = list_equal(&equal_lists, a->neighbours, b->neighbours);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    if(a->data == b->data && equal_lists)
    {
        *equal = true;
    }
    
    return JCRL_ERR_OK;
}

/* Access */
unsigned int vertex_get(void** data, Vertex* vertex)
{
    if(data == NULL || vertex == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    *data = vertex->data;
    
    return JCRL_ERR_OK;
}

unsigned int vertex_set(void* data, Vertex* vertex)
{
    if(vertex == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    vertex->data = data;
    
    return JCRL_ERR_OK;
}

unsigned int vertex_degree(unsigned int* degree, Vertex* vertex)
{
    if(degree == NULL || vertex == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = list_length(degree, vertex->neighbours);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    return JCRL_ERR_OK;
}

/* Operations */
unsigned int vertex_add_neighbour(Vertex* neighbour, Vertex* vertex)
{
    if(neighbour == NULL || vertex == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = list_append(neighbour, vertex->neighbours);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    return JCRL_ERR_OK;
}

unsigned int vertex_remove_neighbour(Vertex* neighbour, Vertex* vertex)
{
    if(neighbour == NULL || vertex == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int pos = 0;
    unsigned int res = list_find(&pos, neighbour, vertex->neighbours);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    res = list_remove(pos, vertex->neighbours);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    return JCRL_ERR_OK;
}
