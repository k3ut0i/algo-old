#include "graph_coloring.h"

/* memory freeing functions */

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
    SET* diff_set = malloc(sizeof(SET));
    set_difference(current_colored_nodes, n->neighbors, diff_set);
    if(set_size(diff_set) > 0)
    l = l->tail;
  }
}
/*   Local Variables: */
/*   compile-command: "gcc -pg -ggdb -o graph_coloring graph_coloring.c" */
/*   End: */
