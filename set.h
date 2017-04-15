#include "list.h"

#ifndef SET_H
#define SET_H
typedef struct set{
  LIST* elements;
  int (*equality_check) (void*, void*);
} SET;

int set_add_item(void*, SET*);
int set_del_item(void*, SET*);
int set_has_item_p(void*, SET*);
void  set_difference(SET*, SET*, SET*);
unsigned int set_size(SET*);
void destroy_set(SET*);

#endif
