#include <stdlib.h>
#include "list.h"


/* list functions */
unsigned int list_length(LIST* l)
{
  int ret_val = 0;
  LIST* current_list = l;
  while(current_list != NULL){
    ret_val++;
    current_list = current_list->tail;
  }
  return ret_val;
}

LIST* list_add_item_f(void* data, LIST* tail)
{
  LIST* new_list = malloc(sizeof(LIST));
  new_list->head = data;
  new_list->tail = tail;
  return new_list;
}

int list_del_item(void* item, LIST* l, int(*equality_check)(void*, void*))
{
  /* TODO: better return values. */
  LIST* cur = l;
  LIST* prev = NULL;

  while(cur != NULL){
    if((equality_check(cur->head, item)) == 1){
      prev->tail = cur->tail;
      free(cur);/* remove the current list node */
    }
      else {
        prev = cur;
        cur = cur->tail;
      }
    }
  return 0;
}
void destroy_list(LIST* l)
{
  if(l == NULL) return;
  if(l->tail == NULL)return;
  destroy_list(l->tail);
  free(l);
  return;
}
