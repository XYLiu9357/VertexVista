cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source code files 
set(ListSrc
    linked-list.cpp
)

add_library(linked-list SHARED ${ListSrc})