#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"
#include "list.h"
#include "set.h"

/* Initialisation */
unsigned int set_init(Set* set)
{
    if(set == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    set->size = 0;
    
    set->list = calloc(1, sizeof(List));
    
    if(set->list == NULL)
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }
    
    unsigned int res = list_init(set->list);
    
    if(res != JCRL_ERR_OK)
    {
        free(set->list);
        return res;
    }
    
    return JCRL_ERR_OK;
}

unsigned int set_free(void (handle_free)(void*), Set* set)
{
    if(set == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = list_free(handle_free, set->list);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    free(set->list);
    set->size = 0;
    
    return JCRL_ERR_OK;
}

/* Equality */
unsigned int set_equal(bool* equal, Set* a, Set* b)
{
    if(equal == NULL || a == NULL || b == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    *equal = false;
    
    if(a->size != b->size)
    {
        return JCRL_ERR_OK;
    }
    
    bool subset = false;
    
    unsigned int res = set_subset(&subset, a, b);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    /* due to our cardinality check above, it is sufficient to test for
     * subset only one way */
    if(subset)
    {
        *equal = true;
    }
    
    return JCRL_ERR_OK;
}

/* Membership */
unsigned int set_in(bool* in, void* data, Set* set)
{
    if(in == NULL || set == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = list_in(in, data, set->list);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    return JCRL_ERR_OK;
}

unsigned int set_subset(bool* subset, Set* a, Set* b)
{
    if(subset == NULL || a == NULL || b == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    *subset = false;
    
    if(b->size > a->size)
    {
        return JCRL_ERR_OK;
    }
    
    unsigned int match = 0;
    struct _LNode* ptr = b->list->head;
    
    for(ptr=b->list->head;ptr!=NULL;ptr=ptr->next)
    {
        bool in = false;
        unsigned int res = set_in(&in, ptr->data, a);
        
        if(res != JCRL_ERR_OK)
        {
            return res;
        }
        
        if(in)
        {
            match++;
        }
        else
        {
            break;
        }
    }
    
    if(match == b->size)
    {
        *subset = true;
    }
    
    return JCRL_ERR_OK;
}

unsigned int set_superset(bool* superset, Set* a, Set* b)
{
    if(superset == NULL || a == NULL || b == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    *superset = false;
    
    /* if a is a subset of b, then b is a superset of a */
    bool subset = false;
    unsigned int res = set_subset(&subset, b, a);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    *superset = subset;
    
    return JCRL_ERR_OK;
}

/* Operations */
unsigned int set_insert(void* data, Set* set)
{
    if(set == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    bool in = false;
    
    unsigned int res = list_in(&in, data, set->list);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    if(!in)
    {
        res = list_append(data, set->list);
        
        if(res != JCRL_ERR_OK)
        {
            return res;
        }
        
        set->size++;
    }
    else
    {
        return JCRL_ERR_IMPOSSIBLE;
    }
    
    return JCRL_ERR_OK;
}

unsigned int set_remove(void* data, Set* set)
{
    if(set == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    if(set->size == 0)
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }
    
    unsigned int pos = 0;
    
    unsigned int res = list_find(&pos, data, set->list);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    res = list_remove(pos, set->list);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    set->size--;
    
    return JCRL_ERR_OK;
}

unsigned int set_union(Set* a, Set* b, Set* c)
{
    if(a == NULL || b == NULL || c == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = 0;
    
    struct _LNode* ptr = a->list->head;
    
    for(ptr=a->list->head;ptr!=NULL;ptr=ptr->next)
    {
        res = set_insert(ptr->data, c);
        
        if(res != JCRL_ERR_OK && res != JCRL_ERR_IMPOSSIBLE)
        {
            return res;
        }
    }
    
    ptr = b->list->head;
    
    for(ptr=b->list->head;ptr!=NULL;ptr=ptr->next)
    {
        res = set_insert(ptr->data, c);
        
        if(res != JCRL_ERR_OK && res != JCRL_ERR_IMPOSSIBLE)
        {
            return res;
        }
    }
    
    return JCRL_ERR_OK;
}

unsigned int set_intersection(Set* a, Set* b, Set* c)
{
    if(a == NULL || b == NULL || c == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    struct _LNode* ptr = a->list->head;
    
    for(ptr=a->list->head;ptr!=NULL;ptr=ptr->next)
    {
        bool in = false;
        
        unsigned int res = list_in(&in, ptr->data, b->list);
        
        if(in)
        {
            res = set_insert(ptr->data, c);
            
            if(res != JCRL_ERR_OK && res != JCRL_ERR_IMPOSSIBLE)
            {
                return res;
            }
        }
    }
    
    return JCRL_ERR_OK;
}

unsigned int set_difference(Set* a, Set* b, Set* c)
{
    if(a == NULL || b == NULL || c == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    struct _LNode* ptr = a->list->head;
    
    for(ptr=a->list->head;ptr!=NULL;ptr=ptr->next)
    {
        bool in = false;
        
        unsigned int res = list_in(&in, ptr->data, b->list);
        
        if(!in)
        {
            res = set_insert(ptr->data, c);
            
            if(res != JCRL_ERR_OK && res != JCRL_ERR_IMPOSSIBLE)
            {
                return res;
            }
        }
    }
    
    return JCRL_ERR_OK;
}

unsigned int set_enumerate(List* list, Set* set)
{
    if(list == NULL || set == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    struct _LNode* ptr = set->list->head;
    
    for(ptr=set->list->head;ptr!=NULL;ptr=ptr->next)
    {
        unsigned int res = list_append(ptr->data, list);
        
        if(res != JCRL_ERR_OK)
        {
            return res;
        }
    }
    
    return JCRL_ERR_OK;
}
