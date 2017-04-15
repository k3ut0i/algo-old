#ifndef LIST_H
#define LIST_H

typedef struct list {
  void* head;
  struct list* tail;
} LIST;

LIST* list_add_item_f(void* , LIST*);
int  list_del_item(void*, LIST*, int (*)(void*, void*));
void destroy_list(LIST*);
unsigned int list_length(LIST*);

#endif
