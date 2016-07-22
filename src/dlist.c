#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "dlist.h"

unsigned int dlist_init(DList* list)
{
  if(list == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  list->length = 0;
  list->head = NULL;
  list->tail = NULL;

  return JCRL_ERR_OK;
}

unsigned int dlist_free(DList* list)
{
  struct _DNode* ptr = list->head;
  struct _DNode* prev = NULL;
  
  for(ptr=list->head;ptr!=NULL;ptr=ptr->next)
  {
    if(ptr != list->head)
	{
	  free(prev);
	  prev = ptr;
	}
  }
  
  free(list->head);
  list->length = 0;

  return JCRL_ERR_OK;
}

unsigned int dlist_insert(void* data, unsigned int pos, DList* list)
{
  // initial checks
  if(list == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  if(pos > list->length)
  {
    return JCRL_ERR_OUT_OF_BOUNDS;
  }
  
  // allocate new node
  struct _DNode* new_node = calloc(1, sizeof(struct _DNode));
  
  if(new_node == NULL)
  {
    return JCRL_ERR_SYS_MEM_ALLOC;
  }
  
  // initialise new node
  new_node->data = data;
  new_node->next = NULL;
  new_node->prev = NULL;
  
  unsigned int i = 0;
  struct _DNode* ptr = list->head;
  
  if(list->length == 0)
  {
    list->head = new_node;
	list->tail = new_node;
  }
  else
  {
    if(pos == 0) // inserting new head
    {
      new_node->next = list->head;
  
      if(list->head->next != NULL)
	  {
	    list->head->next->prev = new_node;
	  }
	
	  list->head = new_node;
    }
    else
    {
      for(ptr=list->head;ptr!=NULL;ptr=ptr->next)
      {
        if(i + 1 == pos)
	    {
	      new_node->next = ptr->next;
	      new_node->prev = ptr;
	  
	      if(ptr->next != NULL)
	      {
	        ptr->next->prev = new_node;
	      }
		  else
		  {
		    list->tail = new_node;
		  }
	  
	      ptr->next = new_node;
	  
	      break;
	    }
  
        i++;
      }
    }
  }
  
  list->length++;

  return JCRL_ERR_OK;
}

unsigned int dlist_remove(unsigned int pos, DList* list)
{
  if(list == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  if(pos > list->length)
  {
    return JCRL_ERR_OUT_OF_BOUNDS;
  }
  
  unsigned int i = 0;
  struct _DNode* tmp = NULL;
  struct _DNode* ptr = list->head;
  
  if(pos == 0) // removing head
  {
    tmp = list->head;
    list->head = list->head->next;
  }
  else if(pos == list->length - 1) // removing tail
  {
    tmp = list->tail;
	list->tail = list->tail->prev;
  }
  else
  {
    for(ptr=list->head;ptr!=NULL;ptr=ptr->next)
	{
	  if(i + 1 == pos)
	  {
	    tmp = ptr->next;
	    ptr->next = ptr->next->next;
		ptr->next->next->prev = ptr; // check
		break;
	  }
	
	  i++;
	}
  }
  
  free(tmp);
  list->length--;

  return JCRL_ERR_OK;
}

unsigned int dlist_traverse(unsigned int reverse, void (*callback)(void*, unsigned int), DList* list)
{
  if(callback == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  if(list == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  unsigned int i = 0;
  struct _DNode* ptr = NULL;
  
  if(reverse == 0)
  {
    ptr = list->head;
  
    for(ptr=list->head;ptr!=NULL;ptr=ptr->next)
    {
      callback(ptr->data, i);
	  i++;
    }
  }
  else if(reverse == 1)
  {
    ptr = list->tail;
	
	for(ptr=list->tail;ptr!=NULL;ptr=ptr->prev)
	{
	  callback(ptr->data, i);
	  i++;
	}
  }
  
  return JCRL_ERR_OK;
}

unsigned int dlist_get(void** data, unsigned int pos, DList* list)
{
  if(data == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }

  if(list == NULL)
  {
    return JCRL_ERR_OK;
  }
  
  if(pos >= list->length)
  {
    return JCRL_ERR_OUT_OF_BOUNDS;
  }
  
  unsigned int i = 0;
  struct _DNode* ptr = list->head;
  
  for(ptr=list->head;ptr!=NULL;ptr=ptr->next)
  {
    if(i == pos)
	{
	  *data = ptr->data;
	}
	
    i++;
  }

  return JCRL_ERR_OK;
}

unsigned int dlist_set(void* data, unsigned int pos, DList* list)
{
  if(list == NULL)
  {
    return JCRL_ERR_OK;
  }
  
  if(pos >= list->length)
  {
    return JCRL_ERR_OUT_OF_BOUNDS;
  }
  
  unsigned int i = 0;
  struct _DNode* ptr = list->head;
  
  for(ptr=list->head;ptr!=NULL;ptr=ptr->next)
  {
    if(i == pos)
	{
	  ptr->data = data;
	}
	
    i++;
  }

  return JCRL_ERR_OK;
}
