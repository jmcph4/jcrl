#ifndef MULTISET_H_
#define MULTISET_H_

#include <stdbool.h>

#include "list.h"

struct _Multiset
{
    unsigned int size;
    List* data;
};

typedef struct _Multiset Multiset;

/* Initialisation */
unsigned int multiset_init(Multiset* multiset);
unsigned int multiset_free(void (handle_free)(void*), Multiset* multiset);

unsigned int multiset_init_list(List* data, Multiset* multiset);

/* Operations */
unsigned int multiset_add(void* data, Multiset* multiset);
unsigned int multiset_remove(void* data, Multiset* multiset);

unsigned int multiset_union(Multiset* a, Multiset* b, Multiset* c);
unsigned int multiset_intersection(Multiset* a, Multiset* b, Multiset* c);
unsigned int multiset_difference(Multiset* a, Multiset* b, Multiset* c);
unsigned int multiset_sum(Multiset* a, Multiset* b, Multiset* c);

/* Size */
unsigned int multiset_cardinality(unsigned int* cardinality, 
                                    Multiset* multiset);
unsigned int multiset_multiplicity(unsigned int* multiplicity, void* data, 
                                    Multiset* multiset);

/* Equality */
unsigned int multiset_equal(bool* equal, Multiset* a, Multiset* b);

/* Membership */
unsigned int multiset_in(bool* in, void* data, Multiset* multiset);

/* Utilities */
unsigned int multiset_enumerate(List* list, Multiset* multiset);

#endif /* MULTISET_H_ */
