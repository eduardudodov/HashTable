cmake_minimum_required(VERSION 3.12)
project(HashTable)

set(CMAKE_CXX_STANDARD 17)



add_executable(HashTable HashTable.hpp testing.cpp value.cpp value.hpp main.cpp)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)

target_link_libraries(HashTable gtest gtest_main)

set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)