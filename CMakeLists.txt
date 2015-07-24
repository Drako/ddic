cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0048 NEW)
project(ddic VERSION 0.1.1)
set(PROJECT_DESCRIPTION "Drako's DI Container for C++11")

if(BIICODE)
    include("${CMAKE_HOME_DIRECTORY}/biicode.cmake")
    include("biicode.cmake")
    return()
endif()

option(WITH_TESTS "build the unit tests" OFF)
if(WITH_TESTS)
    enable_testing()
endif(WITH_TESTS)

add_subdirectory(contrib)
add_subdirectory(src)
add_subdirectory(tests)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(Doxyfile.in Doxyfile)
    add_custom_target(doc "${DOXYGEN_EXECUTABLE}" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Generating documentation with Doxygen." VERBATIM
    )
endif(DOXYGEN_FOUND)

set(PACKAGE_NAME "${PROJECT_NAME}")
set(PACKAGE_VERSION "${PROJECT_VERSION}")
set(PACKAGE_STRING "${PACKAGE_NAME}-${PACKAGE_VERSION}")
