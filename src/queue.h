#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdbool.h>

#include "dlist.h"

struct _Queue
{
    unsigned int length;
    DList* list;
};

typedef struct _Queue Queue;

/* Initialisation */
unsigned int queue_init(Queue* queue);
unsigned int queue_free(void (handle_free)(void*), Queue* queue);

/* Equality */
unsigned int queue_equal(bool* equal, Queue* a, Queue* b);

/* Access */
unsigned int queue_peek(void* data, Queue* queue);
unsigned int queue_length(unsigned int* length, Queue* queue);

/* Operations */
unsigned int queue_push(void* data, Queue* queue);
unsigned int queue_pop(void* data, Queue* queue);

#endif // QUEUE_H_
