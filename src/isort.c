#include <stdlib.h>

#include "constants.h"
#include "isort.h"

unsigned int isort_slist(bool (comparison)(void*, void*), SList* list)
{
    if(comparison == NULL || list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int len = 0;
    
    unsigned int res = slist_length(&len, list);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    if(len == 0 || len == 1) /* trivial cases */
    {
        return JCRL_ERR_OK;
    }
    
    void* previous = calloc(1, sizeof(void*));
    
    if(previous == NULL)
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }
    
    void* current = calloc(1, sizeof(void*));
    
    if(current == NULL)
    {
        free(previous);
        return JCRL_ERR_SYS_MEM_ALLOC;
    }
    
    for(unsigned int i=1;i<len;i++)
    {
        unsigned int j = i;
        
        res = slist_get(&previous, j - 1, list);
        
        if(res != JCRL_ERR_OK)
        {
            free(previous);
            free(current);
            return res;
        }
        
        res = slist_get(&current, j, list);
        
        if(res != JCRL_ERR_OK)
        {
            free(previous);
            free(current);
            return res;
        }
        
        while(j > 0 && comparison(previous, current))
        {
            
            res = slist_swap(j, j - 1, list);
            
            if(res != JCRL_ERR_OK)
            {
                return res;
            }
            
            /* update our view of the list */
            res = slist_get(&previous, j - 1, list);
        
            if(res != JCRL_ERR_OK)
            {
                free(previous);
                free(current);
                return res;
            }
        
            res = slist_get(&current, j, list);
        
            if(res != JCRL_ERR_OK)
            {
                free(previous);
                free(current);
                return res;
            }
            
            j--;
        }
    }
    
    free(previous);
    free(current);
    
    return JCRL_ERR_OK;
}

unsigned int isort_dlist(bool (comparison)(void*, void*), DList* list)
{
    if(comparison == NULL || list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int len = 0;
    
    unsigned int res = dlist_length(&len, list);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    if(len == 0 || len == 1) /* trivial cases */
    {
        return JCRL_ERR_OK;
    }
    
    void* previous = calloc(1, sizeof(void*));
    
    if(previous == NULL)
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }
    
    void* current = calloc(1, sizeof(void*));
    
    if(current == NULL)
    {
        free(previous);
        return JCRL_ERR_SYS_MEM_ALLOC;
    }
    
    for(unsigned int i=1;i<len;i++)
    {
        unsigned int j = i;
        
        res = dlist_get(&previous, j - 1, list);
        
        if(res != JCRL_ERR_OK)
        {
            free(previous);
            free(current);
            return res;
        }
        
        res = dlist_get(&current, j, list);
        
        if(res != JCRL_ERR_OK)
        {
            free(previous);
            free(current);
            return res;
        }
        
        while(j > 0 && comparison(previous, current))
        {
            res = dlist_swap(j, j - 1, list);
            
            if(res != JCRL_ERR_OK)
            {
                return res;
            }
            
            /* update our view of the list */
            res = dlist_get(&previous, j - 1, list);
        
            if(res != JCRL_ERR_OK)
            {
                free(previous);
                free(current);
                return res;
            }
        
            res = dlist_get(&current, j, list);
        
            if(res != JCRL_ERR_OK)
            {
                free(previous);
                free(current);
                return res;
            }
            
            j--;
        }
    }
    
    free(previous);
    free(current);
    
    return JCRL_ERR_OK;
}

