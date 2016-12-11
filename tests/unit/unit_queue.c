/*
 * unit_queue.c
 * 
 * Unit tests for the queue implementation. For test declarations, see
 * unit_queue.h.
 */
#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"
#include "queue.h"
#include "unit_queue.h"

/* Initialisation */
bool test_queue_init_normal(void)
{
    bool pass = false;
    
    Queue queue;
    
    unsigned int res = queue_init(&queue);
    
    queue_free(NULL, &queue);
    
    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }
    
    return pass;
}

bool test_queue_init_null_params(void)
{
    bool pass = false;
    
    unsigned int res = queue_init(NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_queue_free_normal(void)
{
    bool pass = false;
    
    Queue queue;
    queue_init(&queue);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    queue_push((void*)a, &queue);
    
    unsigned int res = queue_free(NULL, &queue);
    
    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }
    
    return pass;
}

bool test_queue_free_null_params(void)
{
    bool pass = false;
    
    unsigned int res = queue_free(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_queue_free_empty_queue(void)
{
    bool pass = false;
    
    Queue queue;
    queue_init(&queue);
    
    unsigned int res = queue_free(NULL, &queue);
    
    if(res == JCRL_ERR_OK)
    {
        pass = true;
    }
    
    return pass;
}

/* Equality */
bool test_queue_equal_normal(void)
{
    bool pass = false;
    
    Queue queue_a;
    queue_init(&queue_a);
    
    Queue queue_b;
    queue_init(&queue_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    queue_push((void*)a, &queue_a);
    queue_push((void*)b, &queue_a);
    
    queue_push((void*)a, &queue_b);
    queue_push((void*)b, &queue_b);
    
    bool equal = false;
    
    unsigned int res = queue_equal(&equal, &queue_a, &queue_b);
    
    queue_free(NULL, &queue_a);
    queue_free(NULL, &queue_b);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_queue_equal_null_params(void)
{
    bool pass = false;
    
    unsigned int res = queue_equal(NULL, NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_queue_equal_unequal_queues(void)
{
    bool pass = false;
    
    Queue queue_a;
    queue_init(&queue_a);
    
    Queue queue_b;
    queue_init(&queue_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    queue_push((void*)a, &queue_a);
    queue_push((void*)b, &queue_a);
    
    queue_push((void*)b, &queue_b);
    queue_push((void*)a, &queue_b);
    
    bool equal = false;
    
    unsigned int res = queue_equal(&equal, &queue_a, &queue_b);
    
    if(res == JCRL_ERR_OK && !equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_queue_equal_same_queues(void)
{
    bool pass = false;
    
    Queue queue_a;
    queue_init(&queue_a);
    
    Queue queue_b;
    queue_init(&queue_b);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    queue_push((void*)a, &queue_a);
    queue_push((void*)b, &queue_a);
    
    bool equal = false;
    
    unsigned int res = queue_equal(&equal, &queue_a, &queue_a);
    
    queue_free(NULL, &queue_a);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

/* Access */
bool test_queue_peek_normal(void)
{
    bool pass = false;
    
    Queue queue;
    queue_init(&queue);
    
    Queue expected_queue;
    queue_init(&expected_queue);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    queue_push((void*)a, &queue);
    queue_push((void*)b, &queue);
    
    queue_push((void*)a, &expected_queue);
    queue_push((void*)b, &expected_queue);
    
    unsigned int value = 0;
    
    unsigned int res = queue_peek((void*)&value, &queue);
    
    bool equal = false;
    queue_equal(&equal, &queue, &expected_queue);
    
    queue_free(NULL, &queue);
    queue_free(NULL, &expected_queue);
    
    if(res == JCRL_ERR_OK && equal && value == a)
    {
        pass = true;
    }
    
    return pass;
}

bool test_queue_peek_null_params(void)
{
    bool pass = false;
    
    unsigned int res = queue_peek(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_queue_peek_empty_queue(void)
{
    bool pass = false;
    
    Queue queue;
    queue_init(&queue);
    
    Queue expected_queue;
    queue_init(&expected_queue);
    
    unsigned int value = 0;
    
    unsigned int res = queue_peek((void*)&value, &queue);
    
    bool equal = false;
    queue_equal(&equal, &queue, &expected_queue);
    
    queue_free(NULL, &queue);
    queue_free(NULL, &expected_queue);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS && equal && value == 0)
    {
        pass = true;
    }
    
    return pass;
}

bool test_queue_length_normal(void)
{
    bool pass = false;
    
    Queue queue;
    queue_init(&queue);
    
    Queue expected_queue;
    queue_init(&expected_queue);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    queue_push((void*)a, &queue);
    queue_push((void*)b, &queue);
    
    queue_push((void*)a, &expected_queue);
    queue_push((void*)b, &expected_queue);
    
    unsigned int length = 0;
    
    unsigned int res = queue_length(&length, &queue);
    
    bool equal = false;
    queue_equal(&equal, &queue, &expected_queue);
    
    queue_free(NULL, &queue);
    queue_free(NULL, &expected_queue);
    
    if(res == JCRL_ERR_OK && equal && length == 2)
    {
        pass = true;
    }
    
    return pass;
}

bool test_queue_length_null_params(void)
{
    bool pass = false;
    
    unsigned int res = queue_length(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_queue_length_empty_queue(void)
{
    bool pass = false;
    
    Queue queue;
    queue_init(&queue);
    
    Queue expected_queue;
    queue_init(&expected_queue);
    
    unsigned int length = 0;
    
    unsigned int res = queue_length(&length, &queue);
    
    bool equal = false;
    queue_equal(&equal, &queue, &expected_queue);
    
    queue_free(NULL, &queue);
    queue_free(NULL, &expected_queue);
    
    if(res == JCRL_ERR_OK && equal && length == 0)
    {
        pass = true;
    }
    
    return pass;
}

bool test_queue_push_normal(void)
{
    bool pass = false;
    
    Queue queue;
    queue_init(&queue);
    
    Queue expected_queue;
    queue_init(&expected_queue);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    queue_push((void*)a, &expected_queue);
    queue_push((void*)a, &expected_queue);
    
    queue_push((void*)a, &queue);
    
    unsigned int res = queue_push((void*)a, &queue);
    
    bool equal = false;
    queue_equal(&equal, &queue, &expected_queue);
    
    queue_free(NULL, &queue);
    queue_free(NULL, &expected_queue);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_queue_push_null_params(void)
{
    bool pass = false;
    
    unsigned int res = queue_push(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_queue_push_empty_queue(void)
{
    bool pass = false;
    
    Queue queue;
    queue_init(&queue);
    
    Queue expected_queue;
    queue_init(&expected_queue);
    
    unsigned int a = 12; /* arbitrary value to insert */
    
    queue_push((void*)a, &expected_queue);
    
    unsigned int res = queue_push((void*)a, &queue);
    
    bool equal = false;
    queue_equal(&equal, &queue, &expected_queue);
    
    queue_free(NULL, &queue);
    queue_free(NULL, &expected_queue);
    
    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }
    
    return pass;
}

bool test_queue_pop_normal(void)
{
    bool pass = false;
    
    Queue queue;
    queue_init(&queue);
    
    Queue expected_queue;
    queue_init(&expected_queue);
    
    /* arbitrary values to insert */
    unsigned int a = 12;
    unsigned int b = 3;
    
    queue_push((void*)a, &queue);
    queue_push((void*)b, &queue);
    queue_push((void*)b, &queue);
    
    queue_push((void*)b, &expected_queue);
    queue_push((void*)b, &expected_queue);
    
    unsigned int value = 0;
    
    unsigned int res = queue_pop((void*)&value, &queue);
    
    bool equal = false;
    queue_equal(&equal, &queue, &expected_queue);
    
    if(res == JCRL_ERR_OK && equal && value == a)
    {
        pass = true;
    }
    
    return pass;
}

bool test_queue_pop_null_params(void)
{
    bool pass = false;
    
    unsigned int res = queue_pop(NULL, NULL);
    
    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }
    
    return pass;
}

bool test_queue_pop_empty_queue(void)
{
    bool pass = false;
    
    Queue queue;
    queue_init(&queue);
    
    Queue expected_queue;
    queue_init(&expected_queue);
    
    unsigned int value = 0;
    
    unsigned int res = queue_pop((void*)&value, &queue);
    
    bool equal = false;
    queue_equal(&equal, &queue, &expected_queue);
    
    if(res == JCRL_ERR_OUT_OF_BOUNDS && equal && value == 0)
    {
        pass = true;
    }
    
    return pass;
}
