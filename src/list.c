#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"


/* list functions */
unsigned long list_length(LIST* l)
{
  assert(l!=NULL);
  unsigned long ret_val = 0;
  struct list_cell* c = l->first;
  if(c == NULL) return ret_val;
  else
    {
      while(c != l->last)
	{
	  ret_val++;
	  c =  c->next;
	}
    }
  return ret_val;
}

int list_insert(void* data, unsigned long pos, LIST* l)
{
  struct list_cell* new_cell = malloc(sizeof(struct list_cell));
  new_cell->data = data;
  struct list_cell* c = l->first;
  if(pos == 0)
    {
      new_cell->prev = NULL;
      new_cell->next = l->first;
      l->first->prev = new_cell;
      l->first = new_cell;
      return pos;
    }
  else if (pos > 0 && pos < l->end_pos)
    {
      while(pos != 0)
	{
	  c = c->next;
	  pos--;
	}
      new_cell->prev = c->prev;
      new_cell->next = c;
      c->prev->next = new_cell;
      c->prev = new_cell;
      return pos;
    }
  else if (pos == l->end_pos)
    {
      new_cell->next = NULL;
      new_cell->prev = l->last;
      l->last->next = new_cell;
      l->last = new_cell;
      return pos;
    }
  else return -1;
}

void destroy_list(LIST* l)
{
  if(l == NULL) return;
  struct list_cell* c = l->first;
  if(c == NULL) return;
  else while (c != l->last)
	 {
	   struct list_cell* next = c->next;
	   free(c);
	   c = next;
	 }
  free(l);
  return;
}

unsigned long list_locate(void* data, LIST* l)
{
  unsigned long cur_pos = 0;
  struct list_cell* c = l->first;
  while(c != l->last)
    {
      if(l->ord)
	{
	  if(l->ord(data, c->data) == 0) return cur_pos;
	}
      else
	{
	  if(data == c->data) return cur_pos;
	}
      c = c->next;
      cur_pos++;
    }
  return l->end_pos;/* not found */
}

struct list_cell* list_retrieve(unsigned long pos, LIST* l)
{
  struct list_cell* c = l->first;
  while(c != l->last)
    {
      if(pos == 0) return c;
      c = c->next;
      pos--;
    }
  return NULL;
}

struct list_cell* list_next(unsigned long pos, LIST* l)
{
  return list_retrieve(pos,l)->next;
}

struct list_cell* list_prev(unsigned long pos, LIST* l)
{
  return list_retrieve(pos, l)->prev;
}
/* MISC functions */
void populate_list(unsigned long* num, LIST* l){
  assert(l==NULL);/* just provide a variable to hold list;don't malloc */

}

void list_dump(LIST* l, char* (*dump_item) (void*)){
  list_dump_to(l, dump_item, stdout);
}

void list_dump_to(LIST* l , char* (*dump_item) (void*), FILE* f){
  struct list_cell* c = l->first;
  while(c != l->last){
    fprintf(f, "->%s", dump_item(c->data));
    c = c->next;
  }
}
