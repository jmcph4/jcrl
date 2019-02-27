#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "constants.h"
#include "list.h"
#include "map.h"

uint64_t hash(void* data) 
{
    if(data == NULL) /* null guard */
    {
        return 0;
    }

    uint64_t h = (uint64_t)data;
    uint64_t res = (h >> 20) ^ (h >> 12);

    return res ^ (res >> 7) ^ (res >> 4);
}

uint64_t compress(uint64_t data, uint64_t n)
{
    return data % n;
}

void restructure(Map* map)
{
    if(map == NULL) /* null guard */
    {
        return;
    }

    unsigned int new_num_buckets = map->n * JCRL_MAP_GROWTH_FACTOR;

    List tmp_keys;
    list_init(&tmp_keys);

    List tmp_vals;
    list_init(&tmp_vals);

    void* curr_key = NULL;
    void* curr_val = NULL;

    for(unsigned int i=0;i<map->k;i++)
    {
        /* get key */
        list_get(&curr_key, i, map->keys);
        list_append(curr_key, &tmp_keys);
        
        /* get value */
        map_get(curr_key, &curr_val, map);
        list_append(curr_val, &tmp_vals);
        
        /* remove from map */
        map_remove(curr_key, map);
    }


    unsigned int num_buckets = map->n;
    List* new_bucket = NULL;

    /* expand buckets list */
    for(unsigned int i=0;i<(new_num_buckets-num_buckets);i++)
    {
        /* allocate new bucket */
        new_bucket = calloc(1, sizeof(List));

        if(new_bucket == NULL) /* allocation check */
        {
            return;
        }

        /* initialise new bucket */
        list_init(new_bucket);

        /* add (empty) initialised bucket to buckets */
        list_append(new_bucket, map->buckets);
    }

    unsigned int tmp_keys_len = 0;

    /* get length of tmp_keys so we can iterate */
    list_length(&tmp_keys_len, &tmp_keys);

    /* add all of our keys back */
    for(unsigned int i=0;i<tmp_keys_len;i++)
    {
        list_get(&curr_key, i, &tmp_keys);
        list_get(&curr_val, i, &tmp_vals);
        map_set(curr_key, curr_val, map);
    }
    
    list_free(NULL, &tmp_keys);
    list_free(NULL, &tmp_vals);

    map->n = new_num_buckets;
}

void update(Map* map)
{
    if(map == NULL) /* null guard */
    {
        return;
    }
    
    map->load_factor = map->k / map->n; /* update load factor */

    /* if load factor is too high, restructure */
    if(map->load_factor >= JCRL_MAP_LOAD_THRESHOLD)
    {
        restructure(map);
        map->load_factor = map->k / map->n;
    }
}

/* Initialisation */
unsigned int map_init(Map* map)
{
    if(map == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    map->k = 0;
    map->n = JCRL_MAP_INIT_NUM_BUCKETS;
    map->load_factor = 0.0;

    /* allocate keys list */
    map->keys = calloc(1, sizeof(List));

    if(map->keys == NULL) /* allocation check */
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }
    
    /* initialise keys list */
    unsigned int res = list_init(map->keys);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* allocate space for buckets list */
    map->buckets = calloc(1, sizeof(List));

    if(map->buckets == NULL) /* allocation check */
    {
        return JCRL_ERR_SYS_MEM_ALLOC;
    }
    
    /* initialise buckets list */
    res = list_init(map->buckets);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }
    
    /* initialise each bucket */
    for(unsigned int i=0;i<map->n;i++)
    {
        List* bucket = calloc(1, sizeof(List));

        if(bucket == NULL) /* allocation check */
        {
            return JCRL_ERR_SYS_MEM_ALLOC;
        }

        res = list_init(bucket);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        /* add initialised (empty) bucket to buckets */
        res = list_append(bucket, map->buckets);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }
    }

    return JCRL_ERR_OK;
}

unsigned int map_free(void (handle_free)(void*), Map* map)
{
    if(map == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = JCRL_ERR_OK;

    for(unsigned int i=0;i<map->n;i++)
    {
        List* bucket = NULL;

        /* get bucket from buckets list */
        res = list_get((void**)&bucket, i, map->buckets);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }
       
        unsigned int bucket_len = 0;

        res = list_length(&bucket_len, bucket);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        List* pair = NULL;

        /* free each pair in the bucket */
        for(unsigned int j=0;j<bucket_len;j++)
        {
            res = list_get((void**)&pair, j, bucket);

            if(res != JCRL_ERR_OK)
            {
                return res;
            }

            res = list_free(handle_free, pair);

            if(res != JCRL_ERR_OK)
            {
                return res;
            }
        }

        res = list_free(handle_free, bucket);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }
    }

    res = list_free(NULL, map->buckets);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    res = list_free(NULL, map->keys);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    map->k = 0;
    map->n = 0;
    map->load_factor = 0.0;

    return JCRL_ERR_OK;
}

/* Size */
unsigned int map_size(unsigned int* size, Map* map)
{
    if(size == NULL || map == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    *size = map->k;

    return JCRL_ERR_OK;
}

/* Membership */
unsigned int map_key_in(bool* in, void* key, Map* map)
{
    if(in == NULL || map == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    return list_in(in, key, map->keys);
}

unsigned int map_value_in(bool* in, void* value, Map* map)
{
    if(in == NULL || map == NULL)
    {
        return JCRL_ERR_NULL_PARAM;
    }

    *in = false; /* assume false for now */

    unsigned int res = JCRL_ERR_OK;
    void* curr_key = NULL;
    void* curr_val = NULL;

    /* iterate over each key, testing if we have value */
    for(unsigned int i=0;i<map->k;i++)
    {
        /* get current key to search */
        res = list_get(&curr_key, i, map->keys);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }
        
        /* retrieve value from map */
        res = map_get(curr_key, &curr_val, map);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        /* test for value equality */
        if(curr_val == value)
        {
            *in = true;
            break;
        }
    }

    return JCRL_ERR_OK;
}

/* Access */
unsigned int map_get(void* key, void** value, Map* map)
{
    if(value == NULL || map == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    bool have_key = false;

    /* check if we have key */
    unsigned int res = map_key_in(&have_key, key, map);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* if we don't have key, HALT */
    if(!have_key)
    {
        return JCRL_ERR_NOT_FOUND;
    }

    /* hash and compress */
    uint64_t hash_code = hash(key);
    int offset = compress(hash_code, map->n);
    
    List* bucket = NULL;

    /* lookup bucket */
    res = list_get((void**)&bucket, offset, map->buckets);
    
    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    unsigned int bucket_len = 0;

    /* get number of elements in bucket */
    res = list_length(&bucket_len, bucket);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    List* curr_pair = NULL;
    List* curr_key = NULL;
    List* curr_value = NULL;

    for(unsigned int i=0;i<bucket_len;i++)
    {
        /* extract pair */
        res = list_get((void**)&curr_pair, i, bucket);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }
        
        /* get key from pair */
        res = list_get((void**)&curr_key, 0, curr_pair);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        /* get value from pair */
        res = list_get((void**)&curr_value, 1, curr_pair);

        if(key == curr_key) /* found? */
        {
            *value = curr_value;
            break;
        }
    }

    return JCRL_ERR_OK;
}

unsigned int map_set(void* key, void* value, Map* map)
{
    if(map == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    /* hash and compress */
    uint64_t hash_code = hash(key);
    uint64_t offset = compress(hash_code, map->n);

    List* bucket = NULL;

    /* lookup bucket */
    unsigned int res = list_get((void**)(void**)&bucket, offset, map->buckets);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    bool key_exists = false;

    res = list_in(&key_exists, key, map->keys);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* check to see if we already have the key */
    if(key_exists)
    {
        void* curr_key = NULL; /* current key (from (k,v) pair */
        List* curr_kv_pair = NULL; /* current (key,value) pair */
        unsigned int bucket_len = 0; /* length of bucket */

        /* get length of this bucket */
        res = list_length(&bucket_len, bucket);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        for(unsigned int i=0;i<bucket_len;i++)
        {
            /* retrieve pair */
            res = list_get((void**)&curr_kv_pair, i, bucket);

            if(res != JCRL_ERR_OK)
            {
                return res;
            }
            
            /* get key at this position in the bucket */
            res = list_get((void**)&curr_key, 0, curr_kv_pair);

            if(res != JCRL_ERR_OK)
            {
                return res;
            }

            if(curr_key == key) /* if we've found the key */
            {
                /* update value */
                res = list_set(value, 1, curr_kv_pair);

                if(res != JCRL_ERR_OK)
                {
                    return res;
                }

                break;
            }
        }
    }
    else
    {
        /* allocate space for new pair */
        List* pair = calloc(1, sizeof(List));

        if(pair == NULL) /* allocation check */
        {
            return JCRL_ERR_SYS_MEM_ALLOC;
        }

        /* initialise new pair */
        res = list_init(pair);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        /* insert key into new pair */
        res = list_append(key, pair);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        /* insert value into new pair */
        res = list_append(value, pair);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        /* add new pair to end of bucket */
        res = list_append(pair, bucket);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        /* add new key to list of keys for lookup */
        res = list_append(key, map->keys);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        map->k++;
    }

    update(map);

    return JCRL_ERR_OK;
}

unsigned int map_remove(void* key, Map* map)
{
    if(map == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = JCRL_ERR_OK;

    bool have_key = false;

    /* check if we have the key first */
    res = map_key_in(&have_key, key, map);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    if(!have_key)
    {
        return JCRL_ERR_NOT_FOUND;
    }

    unsigned int key_pos = 0;

    void* curr_key = NULL;
    void* curr_val = NULL;
    List* curr_pair = NULL;

    /* find key in key list */
    for(unsigned int i=0;i<map->k;i++)
    {
        res = list_get(&curr_key, i, map->keys);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        if(key == curr_key)
        {
            key_pos = i;
            break;
        }
    }

    /* remove key from key list */
    res = list_remove(key_pos, map->keys);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    /* hash and compress */
    uint64_t hash_code = hash(curr_key);
    uint64_t offset = compress(hash_code, map->n);

    List* bucket = NULL;

    /* lookup bucket */
    res = list_get((void**)&bucket, offset, map->buckets);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    unsigned int bucket_len = 0;

    res = list_length(&bucket_len, bucket);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }

    for(unsigned int i=0;i<bucket_len;i++)
    {
        /* get pair from bucket */
        res = list_get((void**)&curr_pair, i, bucket);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        /* extract key from pair */
        res = list_get(&curr_key, 0, curr_pair);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        /* extract value from pair */
        res = list_get(&curr_val, 1, curr_pair);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        if(key == curr_key) /* found pair */
        {
            /* free pair */
            res = list_free(NULL, curr_pair);

            if(res != JCRL_ERR_OK)
            {
                return res;
            }

            /* remember position of pair in bucket */
            key_pos = i;
            break;
        }
    }
        
    /* remove pair from bucket */
    res = list_remove(key_pos, bucket);

    if(res != JCRL_ERR_OK)
    {
        return res;
    }    

    map->k--;
    update(map);

    return JCRL_ERR_OK;
}

unsigned int map_clear(Map* map)
{
    if(map == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    unsigned int res = JCRL_ERR_OK;

    void* curr_key = NULL;

    /* iterate over each key, removing it from map */
    while(map->k > 0)
    {
        res = list_get(&curr_key, 0, map->keys);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }

        res = map_remove(curr_key, map);

        if(res != JCRL_ERR_OK)
        {
            return res;
        }
    }

    return JCRL_ERR_OK;
}

