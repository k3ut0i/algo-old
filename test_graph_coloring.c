#include "graph_coloring.h"

int main(int argc, char** argv)
{
  int opt ;
  char* graph_file_name = NULL;
  if(argc == 1)error(-1,EINVAL,"Usage: %s [-d | -f sample_graph_file]",argv[0]);
  while((opt = getopt(argc, argv, "df:")) != -1){
    if(opt == 'f'){
      graph_file_name = optarg;
    }
    else if(opt == 'd') graph_file_name  = "./resources/simple.graph";
    else{
      fprintf(stderr, "Usage: %s [-d | -f sample_graph]\n",argv[0]);
      exit(EXIT_FAILURE);
    }
  }
  printf("\t:greedy coloring heuristic:\n");
  GRAPH* simple = test_initialize_graph(graph_file_name);
  dump_graph(simple);
  destroy_graph(simple);
  return 0;
}
