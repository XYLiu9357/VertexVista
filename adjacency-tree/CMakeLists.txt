cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB_NAME adjtree)
set(ADJACENCY_TREE_SRC
    deque.hpp
    adjtree.cpp
)

add_library(${LIB_NAME} ${ADJACENCY_TREE_SRC})
