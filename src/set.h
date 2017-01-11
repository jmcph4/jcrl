#ifndef SET_H_
#define SET_H_

#include <stdbool.h>

#include "list.h"

struct _Set
{
    unsigned int size;
    List* list;
};

typedef struct _Set Set;

/* Initialisation */
unsigned int set_init(Set* set);
unsigned int set_free(void (handle_free)(void*), Set* set);

/* Equality */
unsigned int set_equal(bool* equal, Set* a, Set* b);

/* Membership */
unsigned int set_in(bool* in, void* data, Set* set);
unsigned int set_subset(bool* subset, Set* a, Set* b);
unsigned int set_superset(bool* superset, Set* a, Set* b);

/* Operations */
unsigned int set_insert(void* data, Set* set);
unsigned int set_remove(void* data, Set* set);

unsigned int set_union(Set* a, Set* b, Set* u);
unsigned int set_intersection(Set* a, Set* b, Set* i);
unsigned int set_difference(Set* a, Set* b, Set* d);

/* Utilities */
unsigned int set_enumerate(List* list, Set* set);

#endif /* SET_H_ */
