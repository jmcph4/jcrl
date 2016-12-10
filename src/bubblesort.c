#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"
#include "slist.h"
#include "dlist.h"
#include "bubblesort.h"

unsigned int bubblesort_slist(bool (comparison(void*, void*)), SList* list)
{
    if(comparison == NULL || list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int length = 0;
    
    unsigned int res = slist_length(&length, list);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    if(length == 0 || length == 1) /* trivial cases */
    {
        return JCRL_ERR_OK;
    }
    
    bool swapped = true;
    
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
    
    while(swapped)
    {
        swapped = false;
        
        for(unsigned int i=1;i<length;i++)
        {
            res = slist_get(&current, i, list);
        
            if(res != JCRL_ERR_OK)
            {
                free(current);
                free(previous);
                return res;
            }
        
            res = slist_get(&previous, i - 1, list);
        
            if(res != JCRL_ERR_OK)
            {
                free(current);
                free(previous);
                return res;
            }
        
            if(comparison(previous, current))
            {
                res = slist_swap(i - 1, i, list);
            
                if(res != JCRL_ERR_OK)
                {
                    free(current);
                    free(previous);
                    return res;
                }
            
                swapped = true;
            }
        }
    }
    
    free(current);
    free(previous);
    
    return JCRL_ERR_OK;
}

unsigned int bubblesort_dlist(bool (comparison(void*, void*)), DList* list)
{
    if(comparison == NULL || list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int length = 0;
    
    unsigned int res = dlist_length(&length, list);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    if(length == 0 || length == 1) /* trivial cases */
    {
        return JCRL_ERR_OK;
    }
 
    bool swapped = true;
    
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
    
    while(swapped)
    {
        swapped = false;
        
        for(unsigned int i=1;i<length;i++)
        {
            res = dlist_get(&current, i, list);
        
            if(res != JCRL_ERR_OK)
            {
                free(current);
                free(previous);
                return res;
            }
        
            res = dlist_get(&previous, i - 1, list);
        
            if(res != JCRL_ERR_OK)
            {
                free(current);
                free(previous);
                return res;
            }
        
            if(comparison(previous, current))
            {
                res = dlist_swap(i - 1, i, list);
            
                if(res != JCRL_ERR_OK)
                {
                    free(current);
                    free(previous);
                    return res;
                }
            
                swapped = true;
            }
        }
    }
    
    free(current);
    free(previous);
    
    return JCRL_ERR_OK;
}
