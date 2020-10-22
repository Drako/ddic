if (WITH_TESTS)
    add_library(ddic_test_plugin MODULE
            binary_expression.cxx
            binary_expression.hxx
            )
    add_library(ddic::tests::plugin ALIAS ddic_test_plugin)
    target_include_directories(ddic_test_plugin
            PRIVATE
            ../src
            ${CMAKE_CURRENT_BINARY_DIR}/../src
            )
    target_link_libraries(ddic_test_plugin
            ddic::lib
            )

    add_executable(ddic_test_app
            main.cxx
            default_factory.cxx
            prototype_factory.cxx
            functor_factory.cxx
            container.cxx
            binary_expression.hxx
            )
    add_executable(ddic::tests ALIAS ddic_test_app)
    target_include_directories(ddic_test_app
            PRIVATE
            ../src
            ${CMAKE_CURRENT_BINARY_DIR}/../src
            )
    target_link_libraries(ddic_test_app
            ddic::lib
            contrib::gtest
            contrib::gmock
            )

    # the plugin is a module and we don't want to link against it
    # yet for the tests we want the module to be present already
    # so it needs to be built before the tests
    add_dependencies(ddic_test_app ddic::tests::plugin)

    add_test(
            NAME ddic_test
            COMMAND ddic_test_app
    )
endif (WITH_TESTS)

