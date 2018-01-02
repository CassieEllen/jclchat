# https://rix0r.nl/blog/2015/08/13/cmake-guide/
# At LEAST 2.8 but newer is better
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(jclchat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)
message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
  
# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include(GNUInstallDirs)

#
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
message("${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Include Boost as an imported target
find_package(Boost REQUIRED)
add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

#add_library(boost-iostreams SHARED IMPORTED)
#set_property(TARGET boost-iostreams PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS})
#set_property(TARGET boost-iostreams PROPERTY IMPORTED_LOCATION ${Boost_IOSTREAMS_LIBRARY})

# Include POCO
find_package(POCO REQUIRED Foundation Net Util Data DataMySQL)
add_library(poco INTERFACE IMPORTED)
set_property(TARGET poco PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${POCO_INCLUDE_DIR})


# Some other library that we import that was also built using CMake
# and has an exported target.
#find_package(MyOtherLibrary REQUIRED)

# Targets that we develop here
enable_testing()
add_subdirectory(HtmlPages)
add_subdirectory(Util)
add_subdirectory(JclModel)
add_subdirectory(JclServer)
add_subdirectory(JclChat)
