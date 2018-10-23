#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include <map.h>
#include <constants.h>
#include <macros.h>

#include "unit_map.h"

bool test_map_init_normal(void)
{
    bool pass = false;

    Map map;

    unsigned int res = map_init(&map);

    map_free(NULL, &map);

    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }

    return pass;
}

bool test_map_init_null_params(void)
{
    bool pass = false;

    unsigned int res = map_init(NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_map_free_normal(void)
{
    bool pass = false;

    Map map;
    map_init(&map);

    unsigned int res = map_free(NULL, &map);

    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }

    return pass;
}

bool test_map_free_null_params(void)
{
    bool pass = false;

    unsigned int res = map_free(NULL, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_map_get_normal(void)
{
    bool pass = false;

    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 64;
    unsigned int d = 32;

    Map map;
    map_init(&map);

    /* insert values into map */
    map_set(G_INT(a), G_INT(b), &map);
    map_set(G_INT(c), G_INT(d), &map);

    unsigned int data = 0;

    unsigned int res = map_get(G_INT(a), (void**)&data, &map);

    map_free(NULL, &map);

    if(res == JCRL_ERR_OK && data == b)
    {
        pass = true;
    }

    return pass;
}

bool test_map_get_null_params(void)
{
    bool pass = false;

    unsigned int res = map_get(NULL, NULL, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_map_get_not_found(void)
{
    bool pass = false;
 
    Map map;
    map_init(&map);

    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 64;
    unsigned int d = 32;

    /* insert values into map */
    map_set(G_INT(a), G_INT(b), &map);
    map_set(G_INT(c), G_INT(d), &map);

    unsigned int data = 0;

    unsigned int res = map_get(G_INT(d), (void**)&data, &map);

    map_free(NULL, &map);

    if(res == JCRL_ERR_NOT_FOUND)
    {
        pass = true;
    }

    return pass;
}

bool test_map_set_normal(void)
{
    bool pass = false;

    Map map;
    map_init(&map);

    unsigned int a = 12;
    unsigned int b = 33;

    /* insert values into map */
    unsigned int res = map_set(G_INT(a), G_INT(b), &map);

    unsigned int data = 0;
    map_get(G_INT(a), (void**)&data, &map);

    map_free(NULL, &map);

    if(res == JCRL_ERR_OK && data == b)
    {
        pass = true;
    }

    return pass;
}

bool test_map_set_null_params(void)
{
    bool pass = false;

    unsigned int res = map_set(NULL, NULL, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_map_remove_normal(void)
{
    bool pass = false;

    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 64;
    unsigned int d = 32;

    Map map;
    map_init(&map);

    /* insert values into map */
    map_set(G_INT(a), G_INT(b), &map);
    map_set(G_INT(c), G_INT(d), &map);

    unsigned int res = map_remove(G_INT(a), &map);

    unsigned int size = 0;
    map_size(&size, &map);

    map_free(NULL, &map);

    if(res == JCRL_ERR_OK && size == 1)
    {
        pass = true;
    }

    return pass;
}

bool test_map_remove_null_params(void)
{
    bool pass = false;

    unsigned int res = map_remove(NULL, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_map_remove_not_found(void)
{
    bool pass = false;

    unsigned int a = 12;
    unsigned int b = 33;

    Map map;
    map_init(&map);

    /* insert values into map */
    map_set(G_INT(a), G_INT(b), &map);
    
    unsigned int res = map_remove(G_INT(b), &map);

    map_free(NULL, &map);

    if(res == JCRL_ERR_NOT_FOUND)
    {
        pass = true;
    }

    return pass;
}

bool test_map_size_normal(void)
{
    bool pass = false;

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    unsigned int d = 64;

    Map map;
    map_init(&map);

    map_set(G_INT(a), G_INT(b), &map);
    map_set(G_INT(c), G_INT(d), &map);

    unsigned int size = 0;

    unsigned int res = map_size(&size, &map);

    map_free(NULL, &map);

    if(res == JCRL_ERR_OK && size == 2)
    {
        pass = true;
    }

    return pass;
}

bool test_map_size_null_params(void)
{
    bool pass = false;

    unsigned int res = map_size(NULL, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_map_size_zero(void)
{
    bool pass = false;
 
    Map map;
    map_init(&map);

    unsigned int size = 1;

    unsigned int res = map_size(&size, &map);

    map_free(NULL, &map);

    if(res == JCRL_ERR_OK && size == 0)
    {
        pass = true;
    }

    return pass;
}

bool test_map_key_in_normal(void)
{
    bool pass = false;

    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 1;
    unsigned int d = 32;

    Map map;
    map_init(&map);

    /* insert values into map */
    map_set(G_INT(a), G_INT(b), &map);
    map_set(G_INT(c), G_INT(d), &map);

    bool in = false;

    unsigned int res = map_key_in(&in, G_INT(a), &map);

    map_free(NULL, &map);

    if(res == JCRL_ERR_OK && in)
    {
        pass = true;
    }

    return pass;
}

bool test_map_key_in_null_params(void)
{
    bool pass = false;

    unsigned int res = map_key_in(NULL, NULL, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_map_key_in_not_found(void)
{
    bool pass = false;

    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 64;
    unsigned int d = 32;

    Map map;
    map_init(&map);

    /* insert values into map */
    map_set(G_INT(a), G_INT(b), &map);
    map_set(G_INT(c), G_INT(d), &map);

    bool in = true;

    unsigned int res = map_key_in(&in, G_INT(b), &map);

    map_free(NULL, &map);

    if(res == JCRL_ERR_OK && !in)
    {
        pass = true;
    }

    return pass;
}

bool test_map_value_in_normal(void)
{
    bool pass = false;

    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 64;
    unsigned int d = 32;

    Map map;
    map_init(&map);

    /* insert values into map */
    map_set(G_INT(a), G_INT(b), &map);
    map_set(G_INT(c), G_INT(d), &map);

    bool in = false;

    unsigned int res = map_value_in(&in, G_INT(b), &map);

    map_free(NULL, &map);
    
    if(res == JCRL_ERR_OK && in)
    {
        pass = true;
    }

    return pass;
}

bool test_map_value_in_null_params(void)
{
    bool pass = false;

    unsigned int res = map_value_in(NULL, NULL, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_map_value_in_not_found(void)
{
    bool pass = false;

    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 64;
    unsigned int d = 32;

    Map map;
    map_init(&map);

    /* insert values into map */
    map_set(G_INT(a), G_INT(b), &map);
    map_set(G_INT(c), G_INT(d), &map);

    bool in = false;

    unsigned int res = map_value_in(&in, G_INT(a), &map);

    map_free(NULL, &map);

    if(res == JCRL_ERR_OK && !in)
    {
        pass = true;
    }

    return pass;
}

bool test_map_clear_normal(void)
{
    bool pass = false;

    unsigned int a = 12;
    unsigned int b = 33;
    unsigned int c = 64;
    unsigned int d = 32;

    Map map;
    map_init(&map);

    /* insert values into map */
    map_set(G_INT(a), G_INT(b), &map);
    map_set(G_INT(c), G_INT(d), &map);

    unsigned int res = map_clear(&map);

    unsigned int size = 1;
    map_size(&size, &map);
    
    map_free(NULL, &map);

    if(res == JCRL_ERR_OK && size == 0)
    {
        pass = true;
    }

    return pass;
}

bool test_map_clear_null_params(void)
{
    bool pass = false;

    unsigned int res = map_clear(NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

