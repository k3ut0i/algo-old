CFLAGS = `pkg-config libgvc --cflags` -Wall -Wextra -Wunused -pg -ggdb
LDFLAGS= `pkg-config libgvc --libs` -lm

all:
tests : test_graph_coloring


list.o 	: list.c
set.o 	: set.c
graph.o : graph.c
graph_coloring.o : graph_coloring.c
test_graph_coloring.o : test_graph_coloring.c

simple_guile : simple_guile.c
	gcc -o simple_guile simple_guile.c `pkg-config --cflags --libs guile-2.0`

test_graph_coloring : test_graph_coloring.o graph_coloring.o graph.o set.o list.o
test_list : test_list.c list.o
	gcc -o test_list test_list.c list.o `pkg-config guile-2.0 cmocka --cflags --libs`

clean:
	rm -rf *.o test_graph_coloring
