# Define library. Only source files here!
project(libHtmlPages VERSION 0.1 LANGUAGES CXX)

# Function to handle C++ server pages code generation
# It basically calls the cpspc tool from the Poco libraries and generates
# the corresponding .cpp and .h file in the build directory
# Adapted from http://www.cmake.org/pipermail/cmake/2010-June/037733.html
find_program(CPSPC_EXECUTABLE cpspc)
function(preprocess_cpsp out_var)
  set(result)
  foreach(file ${ARGN})
    #message("file: ${file}")
    get_filename_component(basename ${file} NAME_WE)
    set(cpsp "${CMAKE_CURRENT_SOURCE_DIR}/src/${file}")
    set(cpp  "${CMAKE_CURRENT_BINARY_DIR}/${basename}.cpp")
    set(h    "${CMAKE_CURRENT_BINARY_DIR}/include/HtmlPages/${basename}.h")
    message("cpsp: ${cpsp}")
    message("cpp:  ${cpp}")
    message("h:    ${h}")
    add_custom_command(OUTPUT ${cpp} ${h}
      COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/include/HtmlPages
      #COMMAND echo ${CPSPC_EXECUTABLE} -o ${CMAKE_CURRENT_BINARY_DIR} -H ${CMAKE_CURRENT_BINARY_DIR}/include/HtmlPages -P HtmlPages ${cpsp}
      COMMAND ${CPSPC_EXECUTABLE} -o ${CMAKE_CURRENT_BINARY_DIR} -H ${CMAKE_CURRENT_BINARY_DIR}/include/HtmlPages -P HtmlPages ${cpsp}
      DEPENDS ${cpsp}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Preprocessing ${file}"
      VERBATIM
      )
    set_source_files_properties(${cpp} PROPERTIES GENERATED 1)
    set_source_files_properties(${h}   PROPERTIES GENERATED 1)
    list(APPEND result ${cpp} ${h})
  endforeach()
  set(${out_var} "${result}" PARENT_SCOPE)
endfunction()


## Compile .cpsp files to .cpp
file(GLOB PAGES_IN RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src "${CMAKE_CURRENT_SOURCE_DIR}/src/*Handler.cpsp")
message("PAGES_IN")
foreach(file_path ${PAGES_IN})
    message("\t${file_path}")
endforeach()


preprocess_cpsp(PAGES_OUT ${PAGES_IN})
message("PAGES_OUT")
foreach(file_path ${PAGES_OUT})
    message("\t${file_path}")
endforeach()


message("CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}")
add_library(HtmlPages
  src/JclPageRequestHandler.cpp
  ${PAGES_OUT} )

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(HtmlPages PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

# If we have compiler requirements for this library, list them
# here
target_compile_features(HtmlPages
    PUBLIC cxx_auto_type
    PRIVATE cxx_variadic_templates)

# Depend on a library that we defined in the top-level file
target_link_libraries(HtmlPages
  JclModel
  poco-net
  )

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS HtmlPages EXPORT HtmlPagesConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT HtmlPagesConfig DESTINATION share/HtmlPages/cmake)

# This makes the project importable from the build directory
export(TARGETS HtmlPages FILE HtmlPagesConfig.cmake)

# Every library has unit tests, of course
#add_executable(testlib
#    test/testlib.cpp)
#
#target_link_libraries(testlib
#    HtmlPages)
#
#add_test(testlib testlib)
