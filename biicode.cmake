add_bii_targets()

target_compile_features(${BII_BLOCK_TARGET}
    INTERFACE
        cxx_auto_type
        cxx_decltype
        cxx_defaulted_functions
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
if(NOT (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 18.00))
    # cmake claims MSVC 2013 does not support deleted functions, even though the code works fine
    # reason is, that deleted functions are not a documented feature in VS 2013
    target_compile_features(${BII_BLOCK_TARGET} INTERFACE cxx_deleted_functions)
endif()

