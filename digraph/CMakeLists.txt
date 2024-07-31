cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source code files 
set(DIGRAPH_SRC
    vertex-map.cpp
    # digraph.cpp
    # digraph-traverse.cpp
)

set(LIB_NAME digraph)

add_library(${LIB_NAME} SHARED ${DIGRAPH_SRC})

target_include_directories(
    ${LIB_NAME} 
    PRIVATE ${CMAKE_SOURCE_DIR}
)
