#include <stdlib.h>

#include "constants.h"
#include "list.h"
#include "queue.h"
#include "macros.h"

/* Initialisation */
unsigned int queue_init(Queue* queue)
{
    if(queue == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = 0;
  
    queue->length = 0;
    queue->list = calloc(1, sizeof(List));
  
    if(queue->list == NULL)
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }
  
    res = list_init(queue->list); 
    PASS_UP_ON_FAIL(res);
    
    return JCRL_ERR_OK;
}

unsigned int queue_free(void (handle_free)(void*), Queue* queue)
{
    if(queue == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = 0;
    
    queue->length = 0;
    
    res = list_free(handle_free, queue->list); 
    PASS_UP_ON_FAIL(res);

    free(queue->list);

    return JCRL_ERR_OK;
}

/* Equality */
unsigned int queue_equal(bool* equal, Queue* a, Queue* b)
{
    if(equal == NULL || a == NULL || b == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    *equal = false;
    
    unsigned int length_a = 0;
    unsigned int length_b = 0;
    
    unsigned int res = queue_length(&length_a, a);
    PASS_UP_ON_FAIL(res);
    
    res = queue_length(&length_b, b); 
    PASS_UP_ON_FAIL(res);
    
    if(length_a == length_b)
    {
        bool lists_equal = false;
        res = list_equal(&lists_equal, a->list, b->list); 
        PASS_UP_ON_FAIL(res);

        if(lists_equal)
        {
            *equal = true;
        }
    }
    
    return JCRL_ERR_OK;
}

/* Access */
unsigned int queue_peek(void* data, Queue* queue)
{
    if(data == NULL || queue == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int length = 0;
    
    unsigned int res = queue_length(&length, queue);
    PASS_UP_ON_FAIL(res);

    res = list_get(data, length - 1, queue->list);
    PASS_UP_ON_FAIL(res);
    
    return JCRL_ERR_OK;
}

unsigned int queue_length(unsigned int* length, Queue* queue)
{
    if(length == NULL || queue == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    *length = queue->length;
    
    return JCRL_ERR_OK;
}

/* Operations */
unsigned int queue_push(void* data, Queue* queue)
{
    if(queue == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = 0;
    
    res = list_insert(data, 0, queue->list);
    PASS_UP_ON_FAIL(res);
    
    queue->length++;
    
    return JCRL_ERR_OK;
}

unsigned int queue_pop(void* data, Queue* queue)
{
    if(data == NULL || queue == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    if(queue->length == 0)
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }
    
    unsigned int res = 0;
    unsigned int* len = calloc(1, sizeof(int));
    
    if(len == NULL)
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }
    
    res = list_length(len, queue->list);
    PASS_UP_ON_FAIL(res);
    
    res = list_get(data, *len-1, queue->list);
    PASS_UP_ON_FAIL(res);
    
    res = list_remove(*len-1, queue->list); 
    PASS_UP_ON_FAIL(res);
    
    queue->length--;
    
    free(len);
    
    return JCRL_ERR_OK;
}
