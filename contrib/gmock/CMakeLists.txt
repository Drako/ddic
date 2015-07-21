set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(gmock STATIC src/gmock-all.cc)
add_library(contrib::gmock ALIAS gmock)
target_include_directories(gmock
    PUBLIC include
    PRIVATE src
)
target_link_libraries(gmock
    PUBLIC gtest
    PRIVATE ${CMAKE_THREAD_LIBS_INIT}
)
