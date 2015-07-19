set(CMAKE_INCLUDE_CURRENT_DIR ON)
configure_file(ddic_config.hxx.in ddic_config.hxx)

add_library(ddic STATIC
    ddic_container.cxx
    ddic_container.hxx
    ddic_factory.cxx
    ddic_factory.hxx
    ${CMAKE_CURRENT_BINARY_DIR}/ddic_config.hxx
)
add_library(ddic::lib ALIAS ddic)
target_compile_features(ddic
    PUBLIC
        cxx_auto_type
        cxx_decltype
        cxx_lambdas
        cxx_nullptr
        cxx_range_for
        cxx_right_angle_brackets
        cxx_static_assert
        cxx_strong_enums
        cxx_trailing_return_types
        cxx_variadic_templates
)

install(
    TARGETS ddic
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(
    FILES
        ddic_container.hxx
        ddic_factory.hxx
        ${CMAKE_CURRENT_BINARY_DIR}/ddic_config.hxx
    DESTINATION
        include
)

