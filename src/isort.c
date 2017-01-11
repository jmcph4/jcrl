#include <stdlib.h>

#include "constants.h"
#include "isort.h"

unsigned int isort(bool (comparison)(void*, void*), List* list)
{
    if(comparison == NULL || list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int len = 0;
    
    unsigned int res = list_length(&len, list);
    
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
        
        res = list_get(&previous, j - 1, list);
        
        if(res != JCRL_ERR_OK)
        {
            free(previous);
            free(current);
            return res;
        }
        
        res = list_get(&current, j, list);
        
        if(res != JCRL_ERR_OK)
        {
            free(previous);
            free(current);
            return res;
        }
        
        while(j > 0 && comparison(previous, current))
        {
            res = list_swap(j, j - 1, list);
            
            if(res != JCRL_ERR_OK)
            {
                return res;
            }
            
            /* update our view of the list */
            res = list_get(&previous, j - 1, list);
        
            if(res != JCRL_ERR_OK)
            {
                free(previous);
                free(current);
                return res;
            }
        
            res = list_get(&current, j, list);
        
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

