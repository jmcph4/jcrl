#include <stdlib.h>

#include "constants.h"
#include "stack.h"
#include "list.h"
#include "macros.h"

/* Initialisation */
unsigned int stack_init(Stack* stack)
{
    if(stack == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
  
    stack->depth = 0;
    stack->list = calloc(1, sizeof(List));
  
    if(stack->list == NULL)
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }
  
    unsigned int res = list_init(stack->list);
    PASS_UP_ON_FAIL(res);
    
    return JCRL_ERR_OK;
}

unsigned int stack_free(void (handle_free)(void*), Stack* stack)
{
    if(stack == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = list_free(handle_free, stack->list);
    PASS_UP_ON_FAIL(res);
    
    free(stack->list);
    
    stack->depth = 0;
    stack->list = NULL;
    
    return JCRL_ERR_OK;
}

/* Equality */
unsigned int stack_equal(bool* equal, Stack* a, Stack* b)
{
    if(equal == NULL || a == NULL || b == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int depth_a = 0;
    unsigned int depth_b = 0;
    
    unsigned int res = stack_depth(&depth_a, a);
    PASS_UP_ON_FAIL(res);
    
    res = stack_depth(&depth_b, b);
    PASS_UP_ON_FAIL(res);
    
    bool lists_equal = false;
        
    res = list_equal(&lists_equal, a->list, b->list);
    
    PASS_UP_ON_FAIL(res);
    
    if(depth_a == depth_b && lists_equal)
    {
        *equal = true;
    }
    else
    {
        *equal = false;
    }
    
    return JCRL_ERR_OK;
}

/* Access */
unsigned int stack_peek(void* data, Stack* stack)
{
    if(data == NULL || stack == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = list_get(data, 0, stack->list);
    PASS_UP_ON_FAIL(res);
    
    return JCRL_ERR_OK;
}

unsigned int stack_depth(unsigned int* depth, Stack* stack)
{
    if(depth == NULL || stack == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    *depth = stack->depth;
    
    return JCRL_ERR_OK;
}

/* Operations */
unsigned int stack_push(void* data, Stack* stack)
{
    if(stack == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = list_insert(data, 0, stack->list);
    PASS_UP_ON_FAIL(res);
    
    stack->depth++;
    
    return JCRL_ERR_OK;
}

unsigned int stack_pop(void* data, Stack* stack)
{
    if(data == NULL || stack == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    if(stack->depth == 0)
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }
    
    unsigned int res = list_get(data, 0, stack->list);
    PASS_UP_ON_FAIL(res);
    
    res = list_remove(0, stack->list); 
    PASS_UP_ON_FAIL(res);
    
    stack->depth--;
    
    return JCRL_ERR_OK;
}
