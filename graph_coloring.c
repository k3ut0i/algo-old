#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>

typedef struct list {
  void* head;
  struct list* tail;
} LIST;

LIST* list_add_item_f(void* , LIST*);
int  list_del_item(void*, LIST*, int (*)(void*, void*));

void destroy_list(LIST*);
int list_length(LIST*);

/* TODO: a set can be implemented as resizing hash table or
   red and black trees. Choose one and implement later;
*/
typedef struct set{
  LIST* elements;
  int (*equality_check) (void*, void*);
} SET;

int set_add_item(void*, SET*);
int set_del_item(void*, SET*);
int set_has_item_p(void*, SET*);
int set_size(SET*);


typedef struct graph{
  long int uid;
  LIST* nodes;
} GRAPH;

typedef struct node{
  long int uid;
  char* data;
  LIST* neighbours;
} NODE;

NODE* get_node_or_create(GRAPH*, long int);
void destroy_graph(GRAPH*) ;
void test_initialize_graph(GRAPH*, const char* filename);
void dump_graph(GRAPH*);
/* TODO: coloring functions. */
void greedy_color_graph(GRAPH*);
void optimal_color_graph(GRAPH*);

int main(int argc, char** argv)
{
  printf("\t:greedy coloring heuristic:\n");
  GRAPH* simple = malloc(sizeof(GRAPH));
  test_initialize_graph(simple, "simple.graph");
  dump_graph(simple);

  return 0;
}

/* list functions */
int list_length(LIST* l)
{
  int ret_val = 0;
  LIST* current_list = l;
  if(l == NULL) return -1;
  else 
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
      if((equality_check(cur->head, item)) == 1)prev->tail = cur->tail;
      else {
        prev = cur;
        cur = cur->tail;
      }
    }
  return 0;
}

void destroy_list(LIST* l)
{
  if((l->tail == NULL) || (l == NULL)) return;
  free(l->head);
  destroy_list(l->tail);
  return;
}

/* graph functions */
void test_initialize_graph(GRAPH* g, const char* filename)
{
  g->nodes = NULL;
  g->uid = 1;
  FILE *fp = fopen(filename, "r");
  long int from, to;
  int scan_ret_val;

  do {
    scan_ret_val = fscanf(fp,"%ld - %ld\n", &from, &to);
    NODE* from_node = get_node_or_create(g, from);
    NODE* to_node = get_node_or_create(g, to);
    from_node->neighbours = list_add_item_f(to_node, from_node->neighbours);
    to_node->neighbours = list_add_item_f(from_node, to_node->neighbours);
  }while(scan_ret_val != EOF);

  return;
}

NODE* get_node_or_create(GRAPH* g, long int uid)
{
  if (g == NULL) error(-1, EINVAL, "%s", __func__);
  LIST* nodes_left = g->nodes;

  while(nodes_left != NULL){
      NODE* current_node = nodes_left->head;
      if(current_node->uid == uid) return current_node;
      else nodes_left = nodes_left->tail;
    }

  NODE* ret_val = malloc (sizeof (NODE));
  ret_val->uid = uid;
  g->nodes = list_add_item_f(ret_val, g->nodes);
  return ret_val;
};

void dump_graph(GRAPH* g)
{
  if (g == NULL) error(-1, EINVAL, "%s", __func__);

  char* indent = "";
  fprintf(stdout, "%sgraph uid: %ld\n", indent, g->uid);
  LIST* nodes = g->nodes;

  while(nodes != NULL)
    {
      indent = " ";
      NODE* cur = nodes->head;
      fprintf(stdout, "%s%ld:{",indent, cur->uid);
      LIST* cur_neighbours = cur->neighbours;
      while(cur_neighbours != NULL) {
        NODE* cur_node = cur_neighbours->head;
        fprintf(stdout, "%ld", cur_node->uid);
        cur_neighbours = cur_neighbours->tail;
      }
      fprintf(stdout, "}\n");
      nodes = nodes->tail;
    }
  return;
}

/* set functions */
int set_add_item(void* item, SET* s)
{
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
  list_del_item(item,s->elements, s->equality_check);
  return 0;
}

/*   Local Variables: */
/*   compile-command: "gcc -pg -ggdb -o graph_coloring graph_coloring.c" */
/*   End: */
