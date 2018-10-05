cmake_minimum_required(VERSION 3.12)
project(HashTable)

set(CMAKE_CXX_STANDARD 17)

add_executable(HashTable HashTable.h testing.cpp value.cpp value.h)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)

target_link_libraries(HashTable gtest gtest_main)