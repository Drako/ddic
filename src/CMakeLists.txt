configure_file(ddic_config.hxx.in ddic_config.hxx)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(ddic STATIC
    ddic_container.cxx
    ddic_register_proxy.cxx
    ddic_container.hxx
    ddic_creation_policy.hxx
    ddic_factory.hxx
    ddic_plugin.hxx
    ddic_register_proxy.hxx
    ddic.hxx
    ${CMAKE_CURRENT_BINARY_DIR}/ddic_config.hxx
)
add_library(ddic::lib ALIAS ddic)
target_compile_features(ddic
    PUBLIC
        cxx_auto_type
        cxx_decltype
        cxx_defaulted_functions
        cxx_deleted_functions
        cxx_final
        cxx_override
        cxx_lambdas
        cxx_nullptr
        cxx_range_for
        cxx_right_angle_brackets
        cxx_static_assert
        cxx_strong_enums
        cxx_trailing_return_types
        cxx_variadic_templates
)
if(UNIX)
    target_link_libraries(ddic
        PRIVATE dl
    )
endif(UNIX)
set_property(TARGET ddic PROPERTY POSITION_INDEPENDENT_CODE ON)

install(
    TARGETS ddic
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(
    FILES
        ddic_container.hxx
        ddic_creation_policy.hxx
        ddic_factory.hxx
        ddic_plugin.hxx
        ddic.hxx
        ${CMAKE_CURRENT_BINARY_DIR}/ddic_config.hxx
    DESTINATION
        include
)

