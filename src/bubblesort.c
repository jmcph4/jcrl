#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"
#include "list.h"
#include "bubblesort.h"
#include "macros.h"

unsigned int bubblesort(bool (comparison(void*, void*)), List* list)
{
    if(comparison == NULL || list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int length = 0;
    
    unsigned int res = list_length(&length, list);    
    PASS_UP_ON_FAIL(res);

    if(length == 0 || length == 1) /* trivial cases */
    {
        return JCRL_ERR_OK;
    }
 
    bool swapped = true;
    
    void** previous = calloc(1, sizeof(void*));
    
    if(previous == NULL)
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }
    
    void** current = calloc(1, sizeof(void*));
    
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
            res = list_get(current, i, list);
        
            if(res != JCRL_ERR_OK)
            {
                free(current);
                free(previous);
                return res;
            }
        
            res = list_get(previous, i - 1, list);
        
            if(res != JCRL_ERR_OK)
            {
                free(current);
                free(previous);
                return res;
            }
        
            if(comparison(*previous, *current))
            {
                res = list_swap(i - 1, i, list);
            
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
