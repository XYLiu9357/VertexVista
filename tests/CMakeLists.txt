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
    linked-list-tests.cpp
    digraph-tests.cpp
)

set(EXECUTABLE_NAME digraph-test.out)

add_executable(${EXECUTABLE_NAME} ${TEST_SRC})

target_link_libraries(
    ${EXECUTABLE_NAME}
    linked-list
    gtest_main
    pthread
)

target_include_directories(
    ${EXECUTABLE_NAME} 
    PRIVATE ${CMAKE_SOURCE_DIR}
)

# Enable testing
enable_testing()
include(GoogleTest)
