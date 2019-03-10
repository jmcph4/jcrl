#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"
#include "list.h"
#include "set.h"
#include "macros.h"

/* Initialisation */
unsigned int set_init(Set* set)
{
    if(set == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = multiset_init((Multiset*)set);
    PASS_UP_ON_FAIL(res);
    
    return JCRL_ERR_OK;
}

unsigned int set_free(void (handle_free)(void*), Set* set)
{
    if(set == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = multiset_free(handle_free, (Multiset*)set);
    PASS_UP_ON_FAIL(res);
    
    return JCRL_ERR_OK;
}

/* Equality */
unsigned int set_equal(bool* equal, Set* a, Set* b)
{
    if(equal == NULL || a == NULL || b == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = multiset_equal(equal, (Multiset*)a, (Multiset*)b);
    PASS_UP_ON_FAIL(res);
    
    return JCRL_ERR_OK;
}

/* Size */
unsigned int set_cardinality(unsigned int* cardinality, Set* set)
{
    if(cardinality == NULL || set == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = multiset_cardinality(cardinality, set);
PASS_UP_ON_FAIL(res);

    return JCRL_ERR_OK;
}

/* Membership */
unsigned int set_in(bool* in, void* data, Set* set)
{
    if(in == NULL || set == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = multiset_in(in, data, (Multiset*)set);
    PASS_UP_ON_FAIL(res);
    
    return JCRL_ERR_OK;
}

unsigned int set_subset(bool* subset, Set* a, Set* b)
{
    if(subset == NULL || a == NULL || b == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = multiset_subset(subset, (Multiset*)a, (Multiset*)b);
    PASS_UP_ON_FAIL(res);
    
    return JCRL_ERR_OK;
}

unsigned int set_superset(bool* superset, Set* a, Set* b)
{
    if(superset == NULL || a == NULL || b == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = multiset_superset(superset, (Multiset*)a, (Multiset*)b);
    PASS_UP_ON_FAIL(res);
    
    return JCRL_ERR_OK;
}

/* Operations */
unsigned int set_add(void* data, Set* set)
{
    if(set == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    bool in = false;
    
    unsigned int res = multiset_in(&in, data, (Multiset*)set);
    PASS_UP_ON_FAIL(res);
    
    if(!in)
    {
        res = multiset_add(data, (Multiset*)set);
        
        PASS_UP_ON_FAIL(res);
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
    
    unsigned int res = multiset_remove(data, (Multiset*)set);
    PASS_UP_ON_FAIL(res);
    
    return JCRL_ERR_OK;
}

unsigned int set_union(Set* a, Set* b, Set* c)
{
    if(a == NULL || b == NULL || c == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = multiset_union((Multiset*)a, (Multiset*)b,
                                        (Multiset*)c);
    PASS_UP_ON_FAIL(res);
    
    return JCRL_ERR_OK;
}

unsigned int set_intersection(Set* a, Set* b, Set* c)
{
    if(a == NULL || b == NULL || c == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = multiset_intersection((Multiset*)a, (Multiset*)b, 
                                                (Multiset*)c);
    PASS_UP_ON_FAIL(res);
    
    return JCRL_ERR_OK;
}

unsigned int set_difference(Set* a, Set* b, Set* c)
{
    if(a == NULL || b == NULL || c == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = multiset_difference((Multiset*)a, (Multiset*)b, 
                                                (Multiset*)c);
    PASS_UP_ON_FAIL(res);
    
    return JCRL_ERR_OK;
}

unsigned int set_enumerate(List* list, Set* set)
{
    if(list == NULL || set == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }
    
    unsigned int res = multiset_enumerate(list, (Multiset*)set);
    PASS_UP_ON_FAIL(res);
    
    return JCRL_ERR_OK;
}
