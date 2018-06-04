# Define library. Only source files here!
project(libUtil VERSION 0.1 LANGUAGES CXX)

# Locate all source files
#
file(GLOB_RECURSE UtilSources
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  "*.cpp" "*.hpp")

message("\nUtilSources: ${UtilSources}\n")

# Define Util Library
#
add_library(Util
        ${UtilSources}
        )


# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(Util PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

  
# If we have compiler requirements for this library, list them
# here
target_compile_features(Util
    PUBLIC cxx_auto_type
    PRIVATE cxx_variadic_templates)

  
# Depend on a library that we defined in the top-level file
target_link_libraries(Util
        poco-net
        )

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS Util EXPORT UtilConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT UtilConfig DESTINATION share/Util/cmake)

# This makes the project importable from the build directory
export(TARGETS Util FILE UtilConfig.cmake)

# Every library has unit tests, of course
###add_executable(testlib
###    test/testlib.cpp)

###target_link_libraries(testlib
###    Util)

###add_test(testlib testlib)
