#ifndef LIST_H
#define LIST_H

/* double linked list */
struct list_cell {
  /* only refer to data that can be owned by list_cell.
 if external data just reference a pointer to the data. */
  void* data;
  struct list_cell* next;
  struct list_cell* prev;

};

typedef struct list{
  struct list_cell *first;
  struct list_cell *last;
  unsigned long end_pos; /* position of last + 1 */
  int (*ord)(void*, void*);/* order function returns gt,eq,lt values as 1,0,-1 */  
}LIST;


int list_insert(void*, unsigned long, LIST*);
unsigned long list_locate(void*, LIST*);
struct list_cell* list_retrieve(unsigned long, LIST*);
struct list_cell* list_next(unsigned long, LIST*);
struct list_cell* list_prev(unsigned long, LIST*);


unsigned long list_length(LIST*);
void list_dump(LIST*, void (*)(void*));
void list_dump_to(LIST*, void (*) (void*), int);
void list_purge(LIST*);
/* populate a list with a given array of numbers*/
void populate_list(unsigned long*, LIST*);

void destroy_list(LIST*);
#endif
