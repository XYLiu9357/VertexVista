cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(adjacency-tree)

set(ADJACENCY_TREE_SRC
    src/deque.hpp
    src/adjtree.cpp
)

add_library(${PROJECT_NAME} ${ADJACENCY_TREE_SRC})