#include <stdlib.h>

#include "constants.h"
#include "dlist.h"
#include "queue.h"

unsigned int queue_init(Queue* queue)
{
  if(queue == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }

  unsigned int res = 0;
  
  queue->length = 0;
  queue->list = calloc(1, sizeof(DList));
  
  if(queue->list == NULL)
  {
    return JCRL_ERR_SYS_MEM_ALLOC;
  }
  
  res = dlist_init(queue->list);
  
  if(res != JCRL_ERR_OK)
  {
    return res;
  }

  return JCRL_ERR_OK;
}

unsigned int queue_free(Queue* queue)
{
  if(queue == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  unsigned int res = 0;
  
  queue->length = 0;
  
  res = dlist_free(queue->list);
  
  if(res != JCRL_ERR_OK)
  {
    return res;
  }
  
  return JCRL_ERR_OK;
}

unsigned int queue_push(void* data, Queue* queue)
{
  if(queue == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  unsigned int res = 0;
  
  res = dlist_insert(data, 0, queue->list);
  
  if(res != JCRL_ERR_OK)
  {
    return res;
  }
  
  queue->length++;
  
  return JCRL_ERR_OK;
}

unsigned int queue_pop(void** data, Queue* queue)
{
  if(data == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }

  if(queue == NULL)
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
  
  res = dlist_length(len, queue->list);
  
  if(res != JCRL_ERR_OK)
  {
    return res;
  }
  
  res = dlist_get(data, *len-1, queue->list);
  
  if(res != JCRL_ERR_OK)
  {
    return res;
  }
  
  res = dlist_remove(*len-1, queue->list);
  
  if(res != JCRL_ERR_OK)
  {
    return res;
  }
  
  queue->length--;
  
  free(len);
  
  return JCRL_ERR_OK;
}

unsigned int queue_length(unsigned int* length, Queue* queue)
{
  if(length == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  if(queue == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  *length = queue->length;
  
  return JCRL_ERR_OK;
}
