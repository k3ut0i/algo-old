#include "graph_coloring.h"

/* memory freeing functions */
int unsigned_long_equality(void *l, void* r){
  unsigned long left = *(unsigned long*)l;
  unsigned long right = *(unsigned long*)r;
  if(left > right) return 1;
  else if(left < right) return -1;
  else return 0;
}


void greedy_color_graph(GRAPH* g, char* of){
  assert(g!=NULL);
  assert(of!=NULL);
  unsigned int nc = 0;/* number of colors used. */
  LIST* l = g->nodes;
  const unsigned int graph_size = list_length(l);
  /* list of sets of each color */
  SET* current_colored_nodes = malloc(sizeof(SET));

  while(l!=NULL){
    NODE* n = l->head;
    /* check if there is a set which has no neighbors of n */
    LIST* s = n->neighbors->elements;
    while(s!=NULL){
      
      s = s->tail;;
    }

    l = l->tail;
  }
}
/*   Local Variables: */
/*   compile-command: "gcc -pg -ggdb -o graph_coloring graph_coloring.c" */
/*   End: */
