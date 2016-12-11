#ifndef SLIST_H_
#define SLIST_H_

#include <stdbool.h>

struct _SNode
{
  void* data;
  struct _SNode* next;
};

struct _SList
{
  unsigned int length;
  struct _SNode* head;
};

typedef struct _SList SList;

/* Initialisation */
unsigned int slist_init(SList* list);
unsigned int slist_free(void (handle_free)(void*), SList* list);

/* Equality */
unsigned int slist_equal(bool* equal, SList* a, SList* b);

/* Membership */
unsigned int slist_in(bool* in, void* data, SList* list);

/* Access */
unsigned int slist_get(void** data, unsigned int pos, SList* list);
unsigned int slist_set(void* data, unsigned int pos, SList* list);
unsigned int slist_length(unsigned int* length, SList* list);

/* Operations */
unsigned int slist_insert(void* data, unsigned int pos, SList* list);
unsigned int slist_remove(unsigned int pos, SList* list);
unsigned int slist_traverse(void (*callback)(void*, unsigned int), SList* list);

/* Utilities */
unsigned int slist_append(void* data, SList* list);
unsigned int slist_concatenate(SList* a, SList* b);
unsigned int slist_swap(unsigned int a, unsigned int b, SList* list);

#endif // SLIST_H_
