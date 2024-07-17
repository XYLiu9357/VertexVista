cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source code files 
set(DIGRAPH_BASICS
    digraph.cpp
    digraph-traverse.cpp
)

set(LIB_NAME digraph_basics)

add_library(${LIB_NAME} SHARED ${DIGRAPH_BASICS})

target_link_libraries(
    ${LIB_NAME}
    linked-list
)
