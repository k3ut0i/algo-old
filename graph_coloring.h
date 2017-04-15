#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <graphviz/gvc.h>

#include <error.h>
#include <errno.h>
#include <assert.h>

#include "list.h"
#include "set.h"
#include "graph.h"

#ifndef GRAPH_COLORING_H
#define GRAPH_COLORING_H

/* TODO: a set can be implemented as resizing hash table or
   red and black trees. Choose one and implement later;
*/


/* TODO: coloring functions. */
void greedy_color_graph(GRAPH*, char*);
void optimal_color_graph(GRAPH*, char*);

#endif
