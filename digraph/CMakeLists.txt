cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source code files 
set(DIGRAPH_SRC
    digraph.cpp
    digraph-traverse.cpp
)

set(LIB_NAME digraph)

add_library(${LIB_NAME} SHARED ${DIGRAPH_SRC})

target_link_libraries(
    ${LIB_NAME}
    adjtree
)

target_include_directories(
    ${LIB_NAME} 
    PRIVATE ${CMAKE_SOURCE_DIR}
)

# Memory checks
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
