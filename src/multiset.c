#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"
#include "multiset.h"
#include "list.h"

unsigned int max(unsigned int a, unsigned int b)
{
    if(a >= b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

unsigned int min(unsigned int a, unsigned int b)
{
    if(a <= b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

/* Initialisation */
unsigned int multiset_init(Multiset* multiset)
{
    if(multiset == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    multiset->data = calloc(1, sizeof(List));
    
    if(multiset->data == NULL)
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }
    
    unsigned int res = list_init(multiset->data);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    multiset->size = 0;
    
    return JCRL_ERR_OK;
}

unsigned int multiset_free(void (handle_free)(void*), Multiset* multiset)
{
    if(multiset == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = list_free(handle_free, multiset->data);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    free(multiset->data);
    
    multiset->size = 0;
    
    return JCRL_ERR_OK;
}

unsigned int multiset_init_list(List* list, Multiset* multiset)
{
    if(list == NULL || multiset == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res =  multiset_init(multiset);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    struct _LNode* ptr = list->head;
    
    for(ptr=list->head;ptr!=NULL;ptr=ptr->next)
    {
        res = multiset_add(ptr->data, multiset);
        
        if(res != JCRL_ERR_OK)
        {
            return res;
        }
    }
    
    return JCRL_ERR_OK;
}

/* Operations */
unsigned int multiset_add(void* data, Multiset* multiset)
{
    if(multiset == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = list_append(data, multiset->data);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    multiset->size++;
    
    return JCRL_ERR_OK;
}

unsigned int multiset_remove(void* data, Multiset* multiset)
{
    if(multiset == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int pos = 0;
    
    unsigned int res = list_find(&pos, data, multiset->data);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    res = list_remove(pos, multiset->data);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    multiset->size--;
    
    return JCRL_ERR_OK;
}

unsigned int multiset_union(Multiset* a, Multiset* b, Multiset* c)
{
    if(a == NULL || b == NULL || c == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = 0;
    
    struct _LNode* ptr_a = a->data->head;
    struct _LNode* ptr_b = b->data->head;
    
    unsigned int mult_a = 0;
    unsigned int mult_b = 0;
    
    bool already_in = false;
    
    for(ptr_a=a->data->head;ptr_a!=NULL;ptr_a=ptr_a->next)
    {
        res = multiset_in(&already_in, ptr_a->data, c);
        
        if(res != JCRL_ERR_OK)
        {
            return res;
        }
        
        if(!already_in)
        {
            res = multiset_multiplicity(&mult_a, ptr_a->data, a);
        
            if(res != JCRL_ERR_OK)
            {
                return res;
            }
            
            res = multiset_multiplicity(&mult_b, ptr_a->data, b);
            
            if(res != JCRL_ERR_OK)
            {
                return res;
            }
            
            for(unsigned int i=0;i<max(mult_a, mult_b);i++)
            {
                res = multiset_add(ptr_a->data, c);
                
                if(res != JCRL_ERR_OK)
                {
                    return res;
                }
            }
        }
    }
    
    for(ptr_b=b->data->head;ptr_b!=NULL;ptr_b=ptr_b->next)
    {
        res = multiset_in(&already_in, ptr_b->data, c);
        
        if(res != JCRL_ERR_OK)
        {
            return res;
        }
        
        if(!already_in)
        {
            res = multiset_multiplicity(&mult_a, ptr_b->data, a);
        
            if(res != JCRL_ERR_OK)
            {
                return res;
            }
            
            res = multiset_multiplicity(&mult_b, ptr_b->data, b);
            
            if(res != JCRL_ERR_OK)
            {
                return res;
            }
            
            for(unsigned int i=0;i<max(mult_a, mult_b);i++)
            {
                res = multiset_add(ptr_b->data, c);
                
                if(res != JCRL_ERR_OK)
                {
                    return res;
                }
            }
        }
    }
    
    return JCRL_ERR_OK;
}

unsigned int multiset_intersection(Multiset* a, Multiset* b, Multiset* c)
{
    if(a == NULL || b == NULL || c == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = 0;
    
    struct _LNode* ptr_a = a->data->head;
    struct _LNode* ptr_b = b->data->head;
    
    unsigned int mult_a = 0;
    unsigned int mult_b = 0;
    
    bool already_in = false;
    
    for(ptr_a=a->data->head;ptr_a!=NULL;ptr_a=ptr_a->next)
    {
        res = multiset_in(&already_in, ptr_a->data, c);
        
        if(res != JCRL_ERR_OK)
        {
            return res;
        }
        
        if(!already_in)
        {
            res = multiset_multiplicity(&mult_a, ptr_a->data, a);
        
            if(res != JCRL_ERR_OK)
            {
                return res;
            }
            
            res = multiset_multiplicity(&mult_b, ptr_a->data, b);
            
            if(res != JCRL_ERR_OK)
            {
                return res;
            }
            
            for(unsigned int i=0;i<min(mult_a, mult_b);i++)
            {
                res = multiset_add(ptr_a->data, c);
                
                if(res != JCRL_ERR_OK)
                {
                    return res;
                }
            }
        }
    }
    
    for(ptr_b=b->data->head;ptr_b!=NULL;ptr_b=ptr_b->next)
    {
        res = multiset_in(&already_in, ptr_b->data, c);
        
        if(res != JCRL_ERR_OK)
        {
            return res;
        }
        
        if(!already_in)
        {
            res = multiset_multiplicity(&mult_a, ptr_b->data, a);
        
            if(res != JCRL_ERR_OK)
            {
                return res;
            }
            
            res = multiset_multiplicity(&mult_b, ptr_b->data, b);
            
            if(res != JCRL_ERR_OK)
            {
                return res;
            }
            
            for(unsigned int i=0;i<min(mult_a, mult_b);i++)
            {
                res = multiset_add(ptr_b->data, c);
                
                if(res != JCRL_ERR_OK)
                {
                    return res;
                }
            }
        }
    }
    
    return JCRL_ERR_OK;
}

unsigned int multiset_difference(Multiset* a, Multiset* b, Multiset* c)
{
    if(a == NULL || b == NULL || c == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = 0;
    
    struct _LNode* ptr = a->data->head;
    
    /* copy a into c */
    for(ptr=a->data->head;ptr!=NULL;ptr=ptr->next)
    {
        res = multiset_add(ptr->data, c);
        
        if(res != JCRL_ERR_OK)
        {
            return res;
        }
    }
    
    ptr = b->data->head;
    
    /* remove all elements in b from c */
    for(ptr=b->data->head;ptr!=NULL;ptr=ptr->next)
    {
        res = multiset_remove(ptr->data, c);
        
        if(res != JCRL_ERR_OK && res != JCRL_ERR_NOT_FOUND)
        {
            return res;
        }
    }
    
    return JCRL_ERR_OK;
}

unsigned int multiset_sum(Multiset* a, Multiset* b, Multiset* c)
{
    if(a == NULL || b == NULL || c == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = 0;
    struct _LNode* ptr = a->data->head;
    
    for(ptr=a->data->head;ptr!=NULL;ptr=ptr->next)
    {
        res = multiset_add(ptr->data, c);
        
        if(res != JCRL_ERR_OK)
        {
            return res;
        }
    }
    
    for(ptr=b->data->head;ptr!=NULL;ptr=ptr->next)
    {
        res = multiset_add(ptr->data, c);
        
        if(res != JCRL_ERR_OK)
        {
            return res;
        }
    }
    
    return JCRL_ERR_OK;
}

/* Size */
unsigned int multiset_cardinality(unsigned int* cardinality, Multiset* multiset)
{
    if(cardinality == NULL || multiset == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    *cardinality = multiset->size;
    
    return JCRL_ERR_OK;
}

unsigned int multiset_multiplicity(unsigned int* multiplicity, void* data, Multiset* multiset)
{
    if(multiplicity == NULL || multiset == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = list_count(multiplicity, data, multiset->data);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    return JCRL_ERR_OK;
}

/* Membership */
unsigned int multiset_in(bool* in, void* data, Multiset* multiset)
{
    if(in == NULL || multiset == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = list_in(in, data, multiset->data);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    return JCRL_ERR_OK;
}

/* Equality */
unsigned int multiset_equal(bool* equal, Multiset* a, Multiset* b)
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
    
    if(a->size == 0)
    {
        *equal = true;
        return JCRL_ERR_OK;
    }
    
    unsigned int res = 0;
    
    struct _LNode* ptr = a->data->head;
    
    unsigned int mult_a = 0;
    unsigned int mult_b = 0;
    bool in_b = false;
    
    for(ptr=a->data->head;ptr!=NULL;ptr=ptr->next)
    {
        res = multiset_in(&in_b, ptr->data, b);
        
        if(res != JCRL_ERR_OK)
        {
            return res;
        }
        
        if(!in_b)
        {
            break;
        }
        
        res = multiset_multiplicity(&mult_a, ptr->data, a);
        
        if(res != JCRL_ERR_OK)
        {
            return res;
        }
        
        res = multiset_multiplicity(&mult_b, ptr->data, b);
        
        if(res != JCRL_ERR_OK)
        {
            return res;
        }
        
        if(mult_a != mult_b)
        {
            break;
        }
        
        *equal = true;
    }
    
    return JCRL_ERR_OK;
}

/* Utilities */
unsigned int multiset_enumerate(List* list, Multiset* multiset)
{
    if(list == NULL || multiset == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    if(multiset->size == 0)
    {
        return JCRL_ERR_OK;
    }
    
    unsigned int res = 0;
    
    struct _LNode* ptr = multiset->data->head;
    
    for(ptr=multiset->data->head;ptr!=NULL;ptr=ptr->next)
    {
        res = list_append(ptr->data, list);
        
        if(res != JCRL_ERR_OK)
        {
            return res;
        }
    }
    
    return JCRL_ERR_OK;
}
