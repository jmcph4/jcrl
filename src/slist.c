#include <stdlib.h>

#include "constants.h"
#include "slist.h"

unsigned int slist_init(SList* list)
{
  if(list == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  list->length = 0;
  list->head = NULL;

  return JCRL_ERR_OK;
}

unsigned int slist_free(SList* list)
{
  struct _SNode* ptr = list->head;
  struct _SNode* prev = NULL;
  
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

unsigned int slist_insert(void* data, unsigned int pos, SList* list)
{ 
  if(list == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  if(pos > list->length)
  {
    return JCRL_ERR_OUT_OF_BOUNDS;
  }
  
  struct _SNode* new_node = calloc(1, sizeof(struct _SNode));
  
  if(new_node == NULL)
  {
    return JCRL_ERR_SYS_MEM_ALLOC;
  }
  
  new_node->data = data;
  new_node->next = NULL;
  
  unsigned int i = 0;
  struct _SNode* tmp = NULL;
  struct _SNode* ptr = list->head;
  
  if(pos == 0) // inserting new head
  {
	new_node->next = list->head;
    list->head = new_node;
  }
  else
  {
    for(ptr=list->head;ptr!=NULL;ptr=ptr->next)
	{
      if(i + 1 == pos)
	  {
	    tmp = ptr->next;
		ptr->next = new_node;
		new_node->next = tmp;
		break;
	  }
	
	  i++;
	}
  }
  
  list->length++;

  return JCRL_ERR_OK;
}

unsigned int slist_remove(unsigned int pos, SList* list)
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
  struct _SNode* tmp = NULL;
  struct _SNode* ptr = list->head;
  
  if(pos == 0) // removing head
  {
    tmp = list->head;
    list->head = list->head->next;
  }
  else
  {
    for(ptr=list->head;ptr!=NULL;ptr=ptr->next)
	{
	  if(i + 1 == pos)
	  {
	    tmp = ptr->next;
	    ptr->next = ptr->next->next;
		break;
	  }
	
	  i++;
	}
  }
  
  free(tmp);
  list->length--;

  return JCRL_ERR_OK;
}

unsigned int slist_traverse(void (*callback)(void*, unsigned int), SList* list)
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
  struct _SNode* ptr = list->head;
  
  for(ptr=list->head;ptr!=NULL;ptr=ptr->next)
  {
    callback(ptr->data, i);
	i++;
  }
  
  return JCRL_ERR_OK;
}

unsigned int slist_get(void** data, unsigned int pos, SList* list)
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
  struct _SNode* ptr = list->head;
  
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

unsigned int slist_set(void* data, unsigned int pos, SList* list)
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
  struct _SNode* ptr = list->head;
  
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

unsigned int slist_length(unsigned int* length, SList* list)
{
  if(length == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  if(list == NULL)
  {
    return JCRL_ERR_NULL_PARAM;
  }
  
  *length = list->length;
  
  return JCRL_ERR_OK;
}
