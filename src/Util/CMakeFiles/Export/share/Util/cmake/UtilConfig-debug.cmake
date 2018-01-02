#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Util" for configuration "Debug"
set_property(TARGET Util APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Util PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libUtil.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Util )
list(APPEND _IMPORT_CHECK_FILES_FOR_Util "${_IMPORT_PREFIX}/lib/libUtil.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
