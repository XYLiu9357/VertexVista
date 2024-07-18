cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(digraph)

# Build libraries
add_subdirectory(adjacency-tree)
add_subdirectory(digraph)
# add_subdirectory(digraph-processing)

# Build executable with unit tests if specified
option(BUILD_TESTS "Build executable containing unit tests" OFF)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
