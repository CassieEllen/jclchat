# Define library. Only source files here!
project(libJclModel VERSION 0.1 LANGUAGES CXX)

# Locate all source files
#
file(GLOB_RECURSE JclModelSources
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  "*.cpp" "*.hpp")

message("\nJclModelSources: ${JclModelSources}\n")

# Define JclModel library
#
add_library(JclModel
  ${JclModelSources}
  )

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(JclModel PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

  
# If we have compiler requirements for this library, list them
# here
target_compile_features(JclModel
    PUBLIC cxx_auto_type
    PRIVATE cxx_variadic_templates)

  
# Depend on a library that we defined in the top-level file
target_link_libraries(JclModel
  Poco::DataMySQL
  )


# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS JclModel EXPORT JclModelConfig 
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'
install(EXPORT JclModelConfig DESTINATION share/JclModel/cmake)


# This makes the project importable from the build directory
export(TARGETS JclModel FILE JclModelConfig.cmake)


# Every library has unit tests, of course
###add_executable(testlib
###    test/testlib.cpp)

###target_link_libraries(testlib
###    JclModel)

###add_test(testlib testlib)
