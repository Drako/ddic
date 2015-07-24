if(BIICODE)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/ddic_config.hxx.in ${CMAKE_CURRENT_BINARY_DIR}/src/ddic_config.hxx)

    add_bii_targets()

    target_include_directories(${BII_BLOCK_TARGET} INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/src)
    if(UNIX)
        target_link_libraries(${BII_LIB_TARGET} INTERFACE dl)
    endif(UNIX)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.7.0")
            target_compile_options(${BII_BLOCK_TARGET} INTERFACE "-std=c++0x")
        else()
            target_compile_options(${BII_BLOCK_TARGET} INTERFACE "-std=c++11")
        endif()
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        # will have to adjust this... older clang versions may need -std=c++0x
        # but I could not find an exact version number :-/
        target_compile_options(${BII_BLOCK_TARGET} INTERFACE "-std=c++11")
    endif()

    return()
endif()

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0048 NEW)
project(ddic VERSION 0.1.1)
set(PROJECT_DESCRIPTION "Drako's DI Container for C++11")

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
