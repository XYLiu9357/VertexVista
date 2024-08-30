cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch google test 
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

set(TEST_SRC
    main.cpp
    graph-tests.cpp
    graph-traversal-tests.cpp
    uf-tests.cpp
    # routine-tests.cpp
)
set(TEST_NAME graph-test.out)

add_executable(${TEST_NAME} ${TEST_SRC})

target_link_libraries(
    ${TEST_NAME}
    graph
    graph_routines
    gtest_main
)

target_include_directories(
    ${TEST_NAME} 
    PRIVATE ${CMAKE_SOURCE_DIR}
)

# Enable testing
include(GoogleTest)
