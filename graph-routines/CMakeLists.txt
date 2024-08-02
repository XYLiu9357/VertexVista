cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source code files 
set(GRAPH_ROUTINES
    biparte.cpp
    connected-components.cpp
    cycle.cpp
    eulerian.cpp
    planarity.cpp
    strong-connectivity.cpp
    topo-sort.cpp
)

add_library(digraph-routines SHARED ${GRAPH_ROUTINES})