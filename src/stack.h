#ifndef STACK_H_
#define STACK_H_

#include "list.h"

struct _Stack
{
  unsigned int depth;
  List* list;
};

typedef struct _Stack Stack;

/* Initialisation */
unsigned int stack_init(Stack* stack);
unsigned int stack_free(void (handle_free)(void*), Stack* stack);

/* Equality */
unsigned int stack_equal(bool* equal, Stack* a, Stack* b);

/* Access */
unsigned int stack_peek(void* data, Stack* stack);
unsigned int stack_depth(unsigned int* depth, Stack* stack);

/* Operations */
unsigned int stack_push(void* data, Stack* stack);
unsigned int stack_pop(void* data, Stack* stack);

#endif // STACK_H_
