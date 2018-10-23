#ifndef MAP_H_
#define MAP_H_

#include "list.h"

struct _Map
{
    unsigned int k;
    unsigned int n;
    double load_factor;
    List* keys;
    List* buckets;
};

typedef struct _Map Map;

/* Initialisation */
unsigned int map_init(Map* map);
unsigned int map_free(void (handle_free)(void*), Map* map);

/* Equality */
unsigned int map_equal(bool* equal, Map* a, Map* b);

/* Size */
unsigned int map_size(unsigned int* size, Map* map);

/* Membership */
unsigned int map_key_in(bool* in, void* key, Map* map);
unsigned int map_value_in(bool* in, void* value, Map* map);

/* Access */
unsigned int map_get(void* key, void** value, Map* map);
unsigned int map_set(void* key, void* value, Map* map);

/* Operations */
unsigned int map_remove(void* key, Map* map);

/* Utilities */
unsigned int map_clear(Map* map);

#endif /* MAP_H_ */

