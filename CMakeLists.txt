cmake_minimum_required(VERSION 3.12)
project(HashTable)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/GTests)
if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage ${PROJECT_TEST_NAME} coverage)
endif()

add_executable(HashTable HashTable.hpp testing.cpp value.cpp value.hpp main.cpp)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)

target_link_libraries(HashTable gtest gtest_main)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(${PROJECT_TEST_NAME} gcov)
endif()

set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)