/*
 * unit_vertex.c
 * 
 * Unit tests for the vertex implementation. For test declarations, see
 * unit_vertex.h.
 */
#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"
#include "dlist.h"
#include "unit_vertex.h"

/* Initialisation */
bool test_vertex_init_normal(void)
{
    bool pass = false;
    
    Vertex vertex;
    
    unsigned int res = vertex_init(&vertex);
    
    vertex_free(NULL, &vertex);
    
    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }
    
    return pass;
}

bool test_vertex_init_null_params(void)
{
    bool pass = false;
    
    unsigned int res = vertex_init(NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_vertex_free_normal(void)
{
    bool pass = false;
    
    Vertex vertex;
    vertex_init(&vertex);
    
    unsigned int res = vertex_free(NULL, &vertex);
    
    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }
    
    return pass;
}

bool test_vertex_free_null_params(void)
{
    bool pass = false;
    
    unsigned int res = vertex_free(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

/* Equality */
bool test_vertex_equal_normal(void)
{
    bool pass = false;
    
    Vertex vertex;
    vertex_init(&vertex);
    
    Vertex expected_vertex;
    vertex_init(&expected_vertex);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    vertex_set((void*)a, &vertex);
    vertex_set((void*)a, &expected_vertex);
    
    bool equal = false;
    
    unsigned int res = vertex_equal(&equal, &vertex, &expected_vertex);
    
    vertex_free(NULL, &vertex);
    vertex_free(NULL, &expected_vertex);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_vertex_equal_null_params(void)
{
    bool pass = false;
    
    unsigned int res = vertex_equal(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_vertex_equal_unequal_vertices(void)
{
    bool pass = false;
    
    Vertex vertex_a;
    vertex_init(&vertex_a);
    
    Vertex vertex_b;
    vertex_init(&vertex_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    
    vertex_set((void*)a, &vertex_a);
    vertex_set((void*)b, &vertex_b);
    
    bool equal = false;
    
    unsigned int res = vertex_equal(&equal, &vertex_a, &vertex_b);
    
    vertex_free(NULL, &vertex_a);
    vertex_free(NULL, &vertex_b);
    
    if(res == JCRL_ERR_OK && !equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_vertex_equal_empty_vertices(void)
{
    bool pass = false;
    
    Vertex vertex_a;
    vertex_init(&vertex_a);
    
    Vertex vertex_b;
    vertex_init(&vertex_b);
    
    bool equal = false;
    
    unsigned int res = vertex_equal(&equal, &vertex_a, &vertex_b);
    
    vertex_free(NULL, &vertex_a);
    vertex_free(NULL, &vertex_b);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_vertex_equal_same_vertex(void)
{
    bool pass = false;
    
    Vertex vertex;
    vertex_init(&vertex);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    vertex_set((void*)a, &vertex);
    
    bool equal = false;
    
    unsigned int res = vertex_equal(&equal, &vertex, &vertex);
    
    vertex_free(NULL, &vertex);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

/* Access */
bool test_vertex_get_normal(void)
{
    bool pass = false;
    
    Vertex vertex;
    vertex_init(&vertex);
    
    Vertex expected_vertex;
    vertex_init(&expected_vertex);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    vertex_set((void*)a, &vertex);
    vertex_set((void*)a, &expected_vertex);
    
    unsigned int* data = calloc(1, sizeof(unsigned int));
    
    unsigned int res = vertex_get((void*)&data, &vertex);
    
    bool equal = false;
    vertex_equal(&equal, &vertex, &expected_vertex);
    
    if(res == JCRL_ERR_OK && equal && (unsigned int)data == a)
    {
        pass = true;
    }
    
    free(data);
    
    return pass;
}

bool test_vertex_get_null_params(void)
{
    bool pass = false;
    
    unsigned int res = vertex_get(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_vertex_set_normal(void)
{
    bool pass = false;
    
    Vertex vertex;
    vertex_init(&vertex);
    
    Vertex expected_vertex;
    vertex_init(&expected_vertex);

    unsigned int a = 12; /* arbitrary value to insert */
    
    unsigned int res = vertex_set((void*)a, &vertex);
    
    vertex_set((void*)a, &expected_vertex);
    
    bool equal = false;
    vertex_equal(&equal, &vertex, &expected_vertex);
    
    vertex_free(NULL, &vertex);
    vertex_free(NULL, &expected_vertex);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_vertex_set_null_params(void)
{
    bool pass = false;
    
    unsigned int res = vertex_set(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_vertex_degree_normal(void)
{
    bool pass = false;
    
    Vertex vertex;
    vertex_init(&vertex);
    
    Vertex neighbour;
    vertex_init(&neighbour);
    
    Vertex expected_vertex;
    vertex_init(&expected_vertex);
    
    vertex_add_neighbour(&neighbour, &vertex);
    vertex_add_neighbour(&neighbour, &expected_vertex);
    
    unsigned int degree = 0;
    
    unsigned int res = vertex_degree(&degree, &vertex);
    
    bool equal = false;
    vertex_equal(&equal, &vertex, &expected_vertex);
    
    vertex_free(NULL, &vertex);
    vertex_free(NULL, &expected_vertex);
    
    if(res == JCRL_ERR_OK && equal && degree == 1)
    {
        pass = true;
    }
    
    return pass;
}

bool test_vertex_degree_null_params(void)
{
    bool pass = false;
    
    unsigned int res = vertex_degree(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

/* Operations */
bool test_vertex_add_neighbour_normal(void)
{
    bool pass = false;
    
    Vertex vertex_a;
    vertex_init(&vertex_a);
    
    Vertex vertex_b;
    vertex_init(&vertex_b);
    
    Vertex expected_vertex_a;
    vertex_init(&expected_vertex_a);
    
    Vertex expected_vertex_b;
    vertex_init(&expected_vertex_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    
    vertex_set((void*)a, &vertex_a);
    vertex_set((void*)b, &vertex_b);
    
    vertex_set((void*)a, &expected_vertex_a);
    vertex_set((void*)b, &expected_vertex_b);
    
    dlist_append(&vertex_b, expected_vertex_a.neighbours); /* cheap hack */
    
    unsigned int res = vertex_add_neighbour(&vertex_b, &vertex_a);
    
    bool equal_a = false;
    vertex_equal(&equal_a, &vertex_a, &expected_vertex_a);
    
    bool equal_b = false;
    vertex_equal(&equal_b, &vertex_b, &expected_vertex_b);
    
    vertex_free(NULL, &vertex_a);
    vertex_free(NULL, &vertex_b);
    vertex_free(NULL, &expected_vertex_a);
    vertex_free(NULL, &expected_vertex_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b)
    {
        pass = true;
    }
    
    return pass;
}

bool test_vertex_add_neighbour_null_params(void)
{
    bool pass = false;
    
    unsigned int res = vertex_add_neighbour(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_vertex_remove_neighbour_normal(void)
{
    bool pass = false;
    
    Vertex vertex_a;
    vertex_init(&vertex_a);
    
    Vertex vertex_b;
    vertex_init(&vertex_b);
    
    Vertex expected_vertex_a;
    vertex_init(&expected_vertex_a);
    
    Vertex expected_vertex_b;
    vertex_init(&expected_vertex_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    
    vertex_set((void*)a, &vertex_a);
    vertex_set((void*)b, &vertex_b);
    
    vertex_set((void*)a, &expected_vertex_a);
    vertex_set((void*)b, &expected_vertex_b);
    
    vertex_add_neighbour(&vertex_b, &vertex_a);
    
    unsigned int res = vertex_remove_neighbour(&vertex_b, &vertex_a);
    
    bool equal_a = false;
    vertex_equal(&equal_a, &vertex_a, &expected_vertex_a);
    
    bool equal_b = false;
    vertex_equal(&equal_b, &vertex_b, &expected_vertex_b);
    
    vertex_free(NULL, &vertex_a);
    vertex_free(NULL, &vertex_b);
    vertex_free(NULL, &expected_vertex_a);
    vertex_free(NULL, &expected_vertex_b);
    
    if(res == JCRL_ERR_OK && equal_a && equal_b)
    {
        pass = true;
    }
    
    return pass;
}

bool test_vertex_remove_neighbour_null_params(void)
{
    bool pass = false;
    
    unsigned int res = vertex_remove_neighbour(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_vertex_remove_neighbour_not_found(void)
{
    bool pass = false;
    
    Vertex vertex_a;
    vertex_init(&vertex_a);
    
    Vertex vertex_b;
    vertex_init(&vertex_b);
    
    Vertex expected_vertex_a;
    vertex_init(&expected_vertex_a);
    
    Vertex expected_vertex_b;
    vertex_init(&expected_vertex_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 33;
    
    vertex_set((void*)a, &vertex_a);
    vertex_set((void*)b, &vertex_b);
    
    vertex_set((void*)a, &expected_vertex_a);
    vertex_set((void*)b, &expected_vertex_b);
    
    unsigned int res = vertex_remove_neighbour(&vertex_b, &vertex_a);
    
    bool equal_a = false;
    vertex_equal(&equal_a, &vertex_a, &expected_vertex_a);
    
    bool equal_b = false;
    vertex_equal(&equal_b, &vertex_b, &expected_vertex_b);
    
    vertex_free(NULL, &vertex_a);
    vertex_free(NULL, &vertex_b);
    vertex_free(NULL, &expected_vertex_a);
    vertex_free(NULL, &expected_vertex_b);
    
    if(res == JCRL_ERR_NOT_FOUND && equal_a && equal_b)
    {
        pass = true;
    }
    
    return pass;
}
