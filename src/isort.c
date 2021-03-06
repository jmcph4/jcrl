#include <stdlib.h>

#include "constants.h"
#include "isort.h"
#include "macros.h"

unsigned int isort(bool (comparison)(void*, void*), List* list)
{
    if(comparison == NULL || list == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int len = 0;
    
    unsigned int res = list_length(&len, list); 
    PASS_UP_ON_FAIL(res);
    
    if(len == 0 || len == 1) /* trivial cases */
    {
        return JCRL_ERR_OK;
    }

    void* left = NULL;
    void* current = NULL;

    unsigned int i = 1;
    
    while(i < len)
    {
        unsigned int j = i;

        res = list_get((void**)&left, j - 1, list);
        PASS_UP_ON_FAIL(res);

        res = list_get((void**)&current, j, list);
        PASS_UP_ON_FAIL(res);

        while(j > 0 && comparison(left, current))
        {
            res = list_swap(j, j - 1, list);
            PASS_UP_ON_FAIL(res);

            res = list_get((void**)&left, j - 2, list);
            
            if(res != JCRL_ERR_OK)
            {
                if(res == JCRL_ERR_OUT_OF_BOUNDS)
                {
                    break;
                }
                else
                {
                    return res;
                }
            }
            
            res = list_get((void**)&current, j - 1, list);            
            PASS_UP_ON_FAIL(res);

            j--;
        }

        i++;
    }
    
    return JCRL_ERR_OK;
}

