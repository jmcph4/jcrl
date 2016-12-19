#ifndef ISORT_H_
#define ISORT_H_

#include "slist.h"
#include "dlist.h"

unsigned int isort_slist(bool (comparison)(void*, void*), SList* list);
unsigned int isort_dlist(bool (comparison)(void*, void*), DList* list);

#endif /* INSERTIONSORT_H_ */
