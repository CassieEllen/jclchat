# https://rix0r.nl/blog/2015/08/13/cmake-guide/
project(jclchat LANGUAGES CXX)
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)
message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
  
# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include(GNUInstallDirs)

# Setup a path to the cmake modules.
#
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
#message("${CMAKE_SOURCE_DIR}/cmake/Modules/")

#link_directories("/usr/local/lib")

# Find the Poco library modules.
find_package(Poco 1.9.0 REQUIRED Foundation Net Util Data DataMySQL)

message("Poco_LIBRARIES ${Poco_LIBRARIES}")
  
# Include Boost as an imported target
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.58.0 REQUIRED
  COMPONENTS filesystem system unit_test_framework
  )

message("Boost_FOUND: ${Boost_FOUND}")
message("Boost_INCLUDE_DIR: ${Boost_INCLUDE_DIR}")
message("Boost_LIBRARIES: ${Boost_LIBRARIES}")

# Targets that we develop here
enable_testing()
add_subdirectory(Util)
#add_subdirectory(HtmlPages)
add_subdirectory(JclModel)
add_subdirectory(JclServer)
add_subdirectory(JclChat)
add_subdirectory(CreateDB)
