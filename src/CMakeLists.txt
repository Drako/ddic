configure_file(ddic_config.hxx.in ddic_config.hxx)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_DEBUG_POSTFIX "_d")
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
set_target_properties(ddic
        PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MINOR}
        INTERFACE_ddic_MAJOR_VERSION ${PROJECT_VERSION_MAJOR}
        COMPATIBLE_INTERFACE_STRING PROJECT_VERSION_MAJOR
        )
target_include_directories(ddic INTERFACE ${CMAKE_INSTALL_PREFIX}/include)
if (UNIX)
    target_link_libraries(ddic
            PRIVATE dl
            )
endif (UNIX)
set_property(TARGET ddic PROPERTY POSITION_INDEPENDENT_CODE ON)

include(CMakePackageConfigHelpers)
install(
        TARGETS ddic
        EXPORT DDICTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
install(
        FILES
        ddic_container.hxx
        ddic_creation_policy.hxx
        ddic_factory.hxx
        ddic_plugin.hxx
        ddic_register_proxy.hxx
        ddic.hxx
        ${CMAKE_CURRENT_BINARY_DIR}/ddic_config.hxx
        DESTINATION
        include
)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/DDICConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)
export(TARGETS ddic
        FILE "${CMAKE_CURRENT_BINARY_DIR}/DDICTargets.cmake"
        )
configure_file(DDICConfig.cmake "${CMAKE_CURRENT_BINARY_DIR}/DDICConfig.cmake" COPYONLY)
set(ConfigPackageLocation lib/cmake/DDIC)
install(EXPORT DDICTargets FILE DDICTargets.cmake DESTINATION ${ConfigPackageLocation})
install(
        FILES
        DDICConfig.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/DDICConfigVersion.cmake"
        DESTINATION ${ConfigPackageLocation}
)

