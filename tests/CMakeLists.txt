if(WITH_TESTS)
    add_executable(ddic_test_app
        main.cxx
    )
    add_executable(ddic::tests ALIAS ddic_test_app)
    target_link_libraries(ddic_test_app
        ddic::lib
        contrib::gtest
        contrib::gmock
    )

    add_test(NAME ddic_test COMMAND ddic_test_app)
endif(WITH_TESTS)

