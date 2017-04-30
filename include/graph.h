#include "list.h"
#include "set.h"

#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph{
  long int uid;
  LIST* nodes;
} GRAPH;

typedef struct node{
  long int uid;
  char* data;
  SET* neighbors;
} NODE;

NODE* get_node_or_create(GRAPH*, long int);
int node_equality_check(void*, void*);
void destroy_node(NODE*);

void destroy_graph(GRAPH*) ;
GRAPH*  test_initialize_graph(const char* filename);
void dump_graph(GRAPH*);

#endif
