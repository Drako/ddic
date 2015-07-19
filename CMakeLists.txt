cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0048 NEW)
project(ddic VERSION 0.1.1)

option(WITH_TESTS "build the unit tests" OFF)
if(WITH_TESTS)
    enable_testing()
endif(WITH_TESTS)

add_subdirectory(contrib)
add_subdirectory(src)
add_subdirectory(tests)

