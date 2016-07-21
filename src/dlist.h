#ifndef DLIST_H_
#define DLIST_H_

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

// Initialisation
unsigned int dlist_init(DList* list);
unsigned int dlist_free(DList* list);

// Operations
unsigned int dlist_insert(void* data, unsigned int pos, DList* list);
unsigned int dlist_remove(unsigned int pos, DList* list);
unsigned int dlist_traverse(unsigned int reverse, void (*callback)(void*, unsigned int), DList* list);

#endif // DLIST_H_
