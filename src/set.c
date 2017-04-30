#include <stdlib.h>
#include <assert.h>
#include "set.h"


/* set functions */
int set_add_item(void* item, SET* s)
{
  assert(s != NULL);
  assert(s->equality_check != NULL);
  LIST* l = s->elements;
  while(l != NULL){
      if(s->equality_check(l->head, item)) return 0;
      else l = l->tail;
    }
  
  s->elements = list_add_item_f(item, s->elements);
  return 1;
}

int set_del_item(void* item, SET* s)
{
  assert(s != NULL);
  list_del_item(item,s->elements, s->equality_check);
  return 0;
}
int set_has_item_p(void* item, SET* s){
  assert(s!=NULL);
  LIST* l = s->elements;
  while(l != NULL){
    if(s->equality_check(item, l->head))return 1;
    l = l->tail;
  }
  return 0;
}
void  set_difference(SET* a, SET* b, SET* result){
  assert((a!=NULL) && (b!=NULL) && (result!=NULL));
  LIST* l = a->elements;
  while(l!=NULL){
    if(set_has_item_p(l->head, b));
    else  set_add_item(l->head, result);
    l = l->tail;
  }
}

unsigned int set_size(SET* s){
  return list_length(s->elements);
}

void destroy_set(SET* s){
  destroy_list(s->elements);
  free(s);
}
