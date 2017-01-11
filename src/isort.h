#ifndef ISORT_H_
#define ISORT_H_

#include "list.h"

unsigned int isort(bool (comparison)(void*, void*), List* list);

#endif /* ISORT_H_ */
