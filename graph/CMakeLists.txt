cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source code files 
set(GRAPH_SRC
    node-edge.cpp
    graph.cpp
    digraph.cpp
)

set(LIB_NAME graph)

add_library(${LIB_NAME} SHARED ${GRAPH_SRC})

target_include_directories(
    ${LIB_NAME} 
    PRIVATE ${CMAKE_SOURCE_DIR}
)
