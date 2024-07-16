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
    tests.cpp
)

add_executable(digraph-test.out ${TEST_SRC})

target_link_libraries(digraph-test.out
    GTest::gtest_main
)

# Add include directories
target_include_directories(digraph-test.out PRIVATE 
    ${CMAKE_SOURCE_DIR}
)

# Enable testing
enable_testing()
include(GoogleTest)
