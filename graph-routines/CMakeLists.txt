cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source code files 
set(GRAPH_ROUTINES_SRC
    paths.cpp
    # biparte.cpp
    # connected-components.cpp
    # cycle.cpp
    # eulerian.cpp
    # planarity.cpp
    # strong-connectivity.cpp
    # topo-sort.cpp
)
set(LIB_NAME graph_routines)

add_library(${LIB_NAME} SHARED ${GRAPH_ROUTINES_SRC})

target_include_directories(
    ${LIB_NAME} 
    PRIVATE ${CMAKE_SOURCE_DIR}
)
