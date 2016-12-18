#include <stdlib.h>
#include <stdbool.h>

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

unsigned int slist_free(void (handle_free)(void*), SList* list)
{
    if(list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    struct _SNode* ptr = list->head;
    struct _SNode* prev = NULL;
  
    for(ptr=list->head;ptr!=NULL;ptr=ptr->next)
    {
        if(ptr != list->head)
        {
            if(handle_free != NULL)
            {
                handle_free(prev->data);
            }   
            
            free(prev);
            prev = ptr;
        }
    }
  
    if(handle_free != NULL)
    {
        handle_free(list->head->data);
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
  
    if(pos >= list->length)
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }
  
    unsigned int i = 0;
    struct _SNode* tmp = NULL;
    struct _SNode* ptr = list->head;
  
    if(pos == 0) /* removing head */
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
    if(callback == NULL || list == NULL)
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
    if(data == NULL || list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
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
        return JCRL_ERR_NULL_PARAM;
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
    if(length == NULL || list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
  
    *length = list->length;
  
    return JCRL_ERR_OK;
}

unsigned int slist_equal(bool* equal, SList* a, SList* b)
{
    if(equal == NULL || a == NULL || b == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    if(a->length != b->length)
    {
        *equal = false;
        return JCRL_ERR_OK;
    }
    
    struct _SNode* a_ptr = a->head;
    struct _SNode* b_ptr = b->head;
    
    for(a_ptr=a->head;a_ptr!=NULL;a_ptr=a_ptr->next)
    {
        if(a_ptr->data != b_ptr->data)
        {
            *equal = false;
            return JCRL_ERR_OK;
        }
        
        b_ptr = b_ptr->next; /* step forward in b */
    }
    
    *equal = true;
    
    return JCRL_ERR_OK;
}

unsigned int slist_in(bool* in, void* data, SList* list)
{
    if(in == NULL || list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    *in = false;
    
    if(list->length == 0) /* trivial case */
    {
        return JCRL_ERR_OK;
    }
    
    struct _SNode* ptr = list->head;
    
    for(ptr=list->head;ptr!=NULL;ptr=ptr->next)
    {
        if(ptr->data == data)
        {
            *in = true;
            break;
        }
    }
    
    return JCRL_ERR_OK;
}

unsigned int slist_append(void* data, SList* list)
{
    if(list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = slist_insert(data, list->length, list);
    
    return res;
}

unsigned int slist_concatenate(SList* a, SList* b)
{
    if(a == NULL || b == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
  
    unsigned int res = 0;
    struct _SNode* ptr = b->head;
  
    for(ptr=b->head;ptr!=NULL;ptr=ptr->next)
    {
        res = slist_append(ptr->data, a);
        
        if(res != JCRL_ERR_OK)
        {
            return res;
        }
    }
  
    return JCRL_ERR_OK;
}

unsigned int slist_swap(unsigned int a, unsigned int b, SList* list)
{
    if(list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    if(a == b) /* trivial case, nothing to do */
    {
        return JCRL_ERR_OK;
    }
    
    void** temp_a = calloc(1, sizeof(void*));
    
    if(temp_a == NULL)
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }
    
    void** temp_b = calloc(1, sizeof(void*));
    
    if(temp_b == NULL)
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }
    
    unsigned int res = slist_get(temp_a, a, list);
            
    if(res != JCRL_ERR_OK)
    {
        free(temp_a);
        free(temp_b);
        return res;
    }
    
    res = slist_get(temp_b, b, list);
    
    if(res != JCRL_ERR_OK)
    {
        free(temp_a);
        free(temp_b);
        return res;
    }
    
    res = slist_set(*temp_a, b, list);
    
    if(res != JCRL_ERR_OK)
    {
        free(temp_a);
        free(temp_b);
        return res;
    }
    
    res = slist_set(*temp_b, a, list);
    
    if(res != JCRL_ERR_OK)
    {
        free(temp_a);
        free(temp_b);
        return res;
    }
    
    free(temp_a);
    free(temp_b);
    
    return JCRL_ERR_OK;
}

unsigned int slist_find(unsigned int* pos, void* data, SList* list)
{
    if(pos == NULL || list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    bool in = false;
    
    unsigned int res = slist_in(&in, data, list);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    if(in)
    {
        unsigned int i = 0;
        
        struct _SNode* ptr = list->head;
        
        for(ptr=list->head;ptr!=NULL;ptr=ptr->next)
        {
            if(ptr->data == data)
            {
                *pos = i;
                break;
            }
            
            i++;
        }
    }
    else
    {
        return JCRL_ERR_NOT_FOUND;
    }
    
    return JCRL_ERR_OK;
}
