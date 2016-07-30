#ifndef QUEUE_H_
#define QUEUE_H_

#include "dlist.h"

struct _Queue
{
  unsigned int length;
  DList* list;
};

typedef struct _Queue Queue;

// Initialisation
unsigned int queue_init(Queue* queue);
unsigned int queue_free(Queue* queue);

// Operations
unsigned int queue_push(void* data, Queue* queue);
unsigned int queue_pop(void** data, Queue* queue);

unsigned int queue_length(unsigned int* length, Queue* queue);

#endif // QUEUE_H_
