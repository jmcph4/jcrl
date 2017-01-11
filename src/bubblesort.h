#ifndef BUBBLESORT_H_
#define BUBBLESORT_H_

#include <stdbool.h>

#include "list.h"

unsigned int bubblesort(bool (comparison)(void*, void*), List* list);

#endif /* BUBBLESORT_H_ */
