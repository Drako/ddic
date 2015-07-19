find_package(Threads REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(gtest STATIC src/gtest-all.cc)
add_library(contrib::gtest ALIAS gtest)
target_include_directories(gtest
    PUBLIC include
    PRIVATE src
)
target_link_libraries(gtest
    PRIVATE ${CMAKE_THREAD_LIBS_INIT}
)

