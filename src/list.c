#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "constants.h"
#include "list.h"

unsigned int list_init(List* list)
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

unsigned int list_free(void (handle_free)(void*), List* list)
{
    if(list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    struct _LNode** elems = calloc(list->length, sizeof(struct _LNode*));

    if(elems == NULL)
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }

    unsigned int e = 0;

    /* traverse list, copying pointers into array */
    for(struct _LNode* ptr=list->head;ptr!=NULL;ptr=ptr->next)
    {
        elems[e] = ptr;
        e++;
    }

    /* traverse array of elements, freeing as we go */
    for(unsigned int i=0;i<e;i++)
    {
        if(handle_free != NULL)
        {
            handle_free(elems[i]->data);
        }

        free(elems[i]);
    }

    free(elems); /* free array itself */

    /* zero out fields */
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
    
    return JCRL_ERR_OK;
}

unsigned int list_insert(void* data, unsigned int pos, List* list)
{
    /* initial checks */
    if(list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    if(pos > list->length)
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }
    
    struct _LNode* new_node = calloc(1, sizeof(struct _LNode));
    
    if(new_node == NULL)
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }
    
    // initialise new node
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    
    unsigned int i = 0;
    struct _LNode* ptr = list->head;
    
    if(list->length == 0)
    {
        list->head = new_node;
        list->tail = new_node;
        
        list->length++;
        
        return JCRL_ERR_OK;
    }
    
    if(pos == 0) // inserting new head
    {
        new_node->next = list->head;
        
        if(list->head->next != NULL)
        {
            list->head->next->prev = new_node;
        }
        
        list->head = new_node;
        
        list->length++;
            
        return JCRL_ERR_OK;
    }
        
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
    
    list->length++;
    
    return JCRL_ERR_OK;
}

unsigned int list_remove(unsigned int pos, List* list)
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
    struct _LNode* tmp = NULL;
    struct _LNode* ptr = list->head;
    
    if(pos == 0) // removing head
    {
        tmp = list->head;
        
        if(list->head->next != NULL)
        {
            list->head->next->prev = NULL;
        }
        
        list->head = list->head->next;
    }
    else
    {
        for(ptr=list->head;ptr!=NULL;ptr=ptr->next)
        {
            if(i + 1 == pos)
            {
                tmp = ptr->next;
            
                if(ptr->next->next != NULL)
                {
                    ptr->next->next->prev = ptr;
                }
                else
                {
                    list->tail = ptr;
                }
            
                ptr->next = ptr->next->next;
            
                break;
            }
        
            i++;
        }
    }
    
    free(tmp);
    list->length--;
    
    if(list->length == 0)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    
    return JCRL_ERR_OK;
}

unsigned int list_traverse(unsigned int reverse, 
                            void (*callback)(void*, unsigned int), 
                            List* list)
{
    if(callback == NULL || list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int i = 0;
    struct _LNode* ptr = NULL;
    
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

unsigned int list_get(void** data, unsigned int pos, List* list)
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
    struct _LNode* ptr = list->head;
    
    for(ptr=list->head;ptr!=NULL;ptr=ptr->next)
    {
        if(i == pos)
        {
            *data = ptr->data;
        
            break;
        }
        
        i++;
    }
    
    return JCRL_ERR_OK;
}

unsigned int list_set(void* data, unsigned int pos, List* list)
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
    struct _LNode* ptr = list->head;
    
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
    
unsigned int list_length(unsigned int* length, List* list)
{
    if(length == NULL || list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    *length = list->length;
    
    return JCRL_ERR_OK;
}

unsigned int list_equal(bool* equal, List* a, List* b)
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
    
    struct _LNode* a_ptr = a->head;
    struct _LNode* b_ptr = b->head;
    
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

unsigned int list_in(bool* in, void* data, List* list)
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
    
    struct _LNode* ptr = list->head;
    
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

unsigned int list_append(void* data, List* list)
{
    if(list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = list_insert(data, list->length, list);
    
    return res;
    
}

unsigned int list_concatenate(List* a, List* b)
{
    if(a == NULL || b == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = 0;
    struct _LNode* ptr = b->head;
    
    for(ptr=b->head;ptr!=NULL;ptr=ptr->next)
    {
        res = list_append(ptr->data, a);
        
        if(res != JCRL_ERR_OK)
        {
            return res;
        }
    }
    
    return JCRL_ERR_OK;
}

unsigned int list_swap(unsigned int a, unsigned int b, List* list)
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
    
    unsigned int res = list_get(temp_a, a, list);
            
    if(res != JCRL_ERR_OK)
    {
        free(temp_a);
        free(temp_b);
        return res;
    }
    
    res = list_get(temp_b, b, list);
    
    if(res != JCRL_ERR_OK)
    {
        free(temp_a);
        free(temp_b);
        return res;
    }
    
    res = list_set(*temp_a, b, list);
    
    if(res != JCRL_ERR_OK)
    {
        free(temp_a);
        free(temp_b);
        return res;
    }
    
    res = list_set(*temp_b, a, list);
    
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

unsigned int list_find(unsigned int* pos, void* data, List* list)
{
    if(pos == NULL || list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    bool in = false;
    
    unsigned int res = list_in(&in, data, list);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    if(in)
    {
        unsigned int i = 0;
        
        struct _LNode* ptr = list->head;
        
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

unsigned int list_count(unsigned int* count, void* data, List* list)
{
    if(count == NULL || list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int num = 0;
    
    struct _LNode* ptr = list->head;
    
    for(ptr=list->head;ptr!=NULL;ptr=ptr->next)
    {
        if(ptr->data == data)
        {
            num++;
        }
    }
    
    *count = num;
    
    return JCRL_ERR_OK;
}
