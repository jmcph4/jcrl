#ifndef BUBBLESORT_H_
#define BUBBLESORT_H_

#include <stdbool.h>

#include "slist.h"
#include "dlist.h"

unsigned int bubblesort_slist(bool (comparison)(void*, void*), SList* list);
unsigned int bubblesort_dlist(bool (comparison)(void*, void*), DList* list);

#endif /* BUBBLESORT_H_ */
