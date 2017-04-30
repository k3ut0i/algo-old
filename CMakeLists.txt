cmake_minimum_required(VERSION 3.3)
project (ALGO)
set (ALGO_VERSION_MAJOR 0)
set (ALGO_VERSION_MINOR 1)

include_directories(include)
add_library(list src/list.c)
#add_library(set src/set.c)
#add_library(graph src/graph.c)

#add_executable(simple_guile tests/test_graph_coloring.c)
add_executable(test_list tests/test_list.c)
include(CTest)
