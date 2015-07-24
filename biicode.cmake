configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/ddic_config.hxx.in ${CMAKE_CURRENT_BINARY_DIR}/src/ddic_config.hxx)

add_bii_targets()

if(UNIX)
    target_link_libraries(${BII_BLOCK_TARGET} INTERFACE dl)
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


