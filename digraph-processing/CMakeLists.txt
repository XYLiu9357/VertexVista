cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source code files 
set(DIGRAPH_ROUTINES
    strong-connectivity.cpp
    topo-sort.cpp
)

add_library(digraph-routines STATIC ${DIGRAPH_ROUTINES})