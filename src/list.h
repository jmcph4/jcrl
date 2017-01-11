#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>

struct _LNode
{
  void* data;
  struct _LNode* next;
  struct _LNode* prev;
};

struct _List
{
  unsigned int length;
  struct _LNode* head;
  struct _LNode* tail;
};

typedef struct _List List;

/* Initialisation */
unsigned int list_init(List* list);
unsigned int list_free(void (handle_free)(void*), List* list);

/* Equality */
unsigned int list_equal(bool* equal, List* a, List* b);

/* Membership */
unsigned int list_in(bool* in, void* data, List* list);

/* Operations */
unsigned int list_insert(void* data, unsigned int pos, List* list);
unsigned int list_remove(unsigned int pos, List* list);
unsigned int list_traverse(unsigned int reverse,
                            void (*callback)(void*, unsigned int),
                            List* list);

/* Access */
unsigned int list_get(void** data, unsigned int pos, List* list);
unsigned int list_set(void* data, unsigned int pos, List* list);
unsigned int list_length(unsigned int* length, List* list);

/* Utilities */
unsigned int list_append(void* data, List* list);
unsigned int list_concatenate(List* a, List* b);
unsigned int list_swap(unsigned int a, unsigned int b, List* list);
unsigned int list_find(unsigned int* pos, void* data, List* list);

#endif /* LIST_H_ */
