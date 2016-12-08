#ifndef DLIST_H_
#define DLIST_H_

#include <stdbool.h>

struct _DNode
{
  void* data;
  struct _DNode* next;
  struct _DNode* prev;
};

struct _DList
{
  unsigned int length;
  struct _DNode* head;
  struct _DNode* tail;
};

typedef struct _DList DList;

/* Initialisation */
unsigned int dlist_init(DList* list);
unsigned int dlist_free(DList* list);

/* Equality */
unsigned int dlist_equal(bool* equal, DList* a, DList* b);

/* Operations */
unsigned int dlist_insert(void* data, unsigned int pos, DList* list);
unsigned int dlist_remove(unsigned int pos, DList* list);
unsigned int dlist_traverse(unsigned int reverse,
                            void (*callback)(void*, unsigned int),
                            DList* list);

/* Access */
unsigned int dlist_get(void** data, unsigned int pos, DList* list);
unsigned int dlist_set(void* data, unsigned int pos, DList* list);
unsigned int dlist_length(unsigned int* length, DList* list);

/* Utilities */
unsigned int dlist_append(void* data, DList* list);
unsigned int dlist_concatenate(DList* a, DList* b);
unsigned int dlist_swap(unsigned int a, unsigned int b, DList* list);

#endif /* DLIST_H_ */
