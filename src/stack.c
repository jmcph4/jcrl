#include <stdlib.h>

#include "constants.h"
#include "stack.h"
#include "dlist.h"

unsigned int stack_init(Stack* stack)
{
  if(stack == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  stack->depth = 0;
  stack->list = calloc(1, sizeof(DList));
  
  if(stack->list == NULL)
  {
    return JCRL_ERR_SYS_MEM_ALLOC;
  }
  
  unsigned int res = dlist_init(stack->list);
  
  if(res != JCRL_ERR_OK)
  {
    return res;
  }
  
  return JCRL_ERR_OK;
}

unsigned int stack_free(Stack* stack)
{
  if(stack == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  unsigned int res = dlist_free(stack->list);
  
  if(res != JCRL_ERR_OK)
  {
    return res;
  }
  
  free(stack->list);
  
  stack->depth = 0;
  stack->list = NULL;
  
  return JCRL_ERR_OK;
}

unsigned int stack_push(void* data, Stack* stack)
{
  if(stack == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  unsigned int res = dlist_insert(data, 0, stack->list);
  
  if(res != JCRL_ERR_OK)
  {
    return res;
  }
  
  stack->depth++;
  
  return JCRL_ERR_OK;
}

unsigned int stack_pop(void* data, Stack* stack)
{
  if(data == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  if(stack == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  if(stack->depth == 0)
  {
    return JCRL_ERR_OUT_OF_BOUNDS;
  }
  
  unsigned int res = 0;
  
  //data = stack->list->head->data;
  res = dlist_get(data, 0, stack->list);
  
  if(res != JCRL_ERR_OK)
  {
    return res;
  }
  
  res = dlist_remove(0, stack->list);
  
  if(res != JCRL_ERR_OK)
  {
    return res;
  }
  
  stack->depth--;
  
  return JCRL_ERR_OK;
}

unsigned int stack_depth(unsigned int* depth, Stack* stack)
{
  if(depth == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  if(stack == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  *depth = stack->depth;
  
  return JCRL_ERR_OK;
}
