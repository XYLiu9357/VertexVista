cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(vertexvista)

# Build libraries
add_subdirectory(graph)
add_subdirectory(graph-routines)

# Build executable with unit tests if specified
option(BUILD_TESTS "Build executable containing unit tests" OFF)

if(BUILD_TESTS)
    enable_testing()
    # set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    add_subdirectory(tests)
endif()
