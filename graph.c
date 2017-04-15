#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
#include <assert.h>

#include "graph.h"
/* graph functions */
GRAPH* test_initialize_graph(const char* filename)
{
  GRAPH* g = malloc(sizeof(GRAPH));
  g->nodes = NULL;
  g->uid = 1;
  FILE *fp = fopen(filename, "r");
  if(fp == NULL)error(-1, errno, "%s:%s", __func__,filename);
  long int from = 0;
  long int to = 0;
  int scan_ret_val;

  do {
    scan_ret_val = fscanf(fp,"%ld - %ld\n", &from, &to);
    NODE* from_node = get_node_or_create(g, from);
    NODE* to_node = get_node_or_create(g, to);
    set_add_item(to_node, from_node->neighbors);
    set_add_item(from_node, to_node->neighbors);
  }while(scan_ret_val != EOF);

  return g;
}

int node_equality_check(void* a, void* b){
  assert(a != NULL);
  assert(b != NULL);
  long int uid1 = ((NODE*)a)->uid;
  long int uid2 = ((NODE*)b)->uid;
  if(uid1 == uid2)return 1;
  else return 0;
}

NODE* get_node_or_create(GRAPH* g, long int uid)
{
  assert(g != NULL);
  LIST* nodes_left = g->nodes;
  /* get existing node */
  while(nodes_left != NULL){
      NODE* current_node = nodes_left->head;
      if(current_node->uid == uid) return current_node;
      else nodes_left = nodes_left->tail;
    }
  /* create new node */
  NODE* ret_val = malloc (sizeof (NODE));
  ret_val->uid = uid;
  ret_val->neighbors = malloc(sizeof(SET));
  ret_val->neighbors->equality_check = &node_equality_check;
  g->nodes = list_add_item_f(ret_val, g->nodes);
  return ret_val;
}

void dump_graph(GRAPH* g)
{
  assert(g != NULL);
  char* indent = "";
  fprintf(stdout, "%sgraph uid: %ld\n", indent, g->uid);
  LIST* nodes = g->nodes;

  while(nodes != NULL)
    {
      indent = " ";
      NODE* cur = nodes->head;
      fprintf(stdout, "%s%ld:{",indent, cur->uid);
      LIST* cur_neighbors = cur->neighbors->elements;
      while(cur_neighbors != NULL) {
        NODE* cur_node = cur_neighbors->head;
        fprintf(stdout, "%ld", cur_node->uid);
        cur_neighbors = cur_neighbors->tail;
      }
      fprintf(stdout, "}\n");
      nodes = nodes->tail;
    }
  return;
}


void destroy_node(NODE* n){
  destroy_set(n->neighbors);
}

void destroy_graph(GRAPH* g){
  LIST* l = g->nodes;
  while(l != NULL){
    NODE* cur_node = l->head;
    destroy_node(cur_node);
    l = l->tail;
  }
  destroy_list(g->nodes);
  free(g);
}
