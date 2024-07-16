cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source code files 
set(DIGRAPH_BASICS
    digraph.cpp
    digraph-traverse.cpp
)

add_library(digraph-basics STATIC ${DIGRAPH_BASICS})
