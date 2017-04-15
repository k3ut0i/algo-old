CFLAGS = `pkg-config libgvc --cflags` -Wall -Wextra -Wunused -pg -ggdb
LDFLAGS= `pkg-config libgvc --libs`

all:
tests : test_graph_coloring


list.o 	: list.c
set.o 	: set.c
graph.o : graph.c
graph_coloring.o : graph_coloring.c
test_graph_coloring.o : test_graph_coloring.c

test_graph_coloring : test_graph_coloring.o graph_coloring.o graph.o set.o list.o

clean:
	rm -rf *.o test_graph_coloring
