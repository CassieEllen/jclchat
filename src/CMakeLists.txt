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

# Setup a path to the cmake modules.
#
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
message("${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Include Boost as an imported target
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.58.0 REQUIRED
  COMPONENTS filesystem system
  )
#add_library(boost INTERFACE IMPORTED)
#set_property(TARGET boost PROPERTY
#    INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

message("Boost_FOUND: ${Boost_FOUND}")
message("Boost_INCLUDE_DIR: ${Boost_INCLUDE_DIR}")
message("Boost_LIBRARIES: ${Boost_LIBRARIES}")

#add_library(boost SHARED IMPORTED)
#set_property(TARGET boost PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
#set_property(TARGET boost PROPERTY IMPORTED_LOCATION "${Boost_LIBRARIES}")

#message("boost INTERFACE IMPORTED: ${boost}")

#add_library(boost-iostreams SHARED IMPORTED)
#set_property(TARGET boost-iostreams PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS})
#set_property(TARGET boost-iostreams PROPERTY IMPORTED_LOCATION ${Boost_IOSTREAMS_LIBRARY})

# Include POCO
find_package(POCO REQUIRED Foundation Net Util Data DataMySQL)

add_library(poco INTERFACE IMPORTED)
set_property(TARGET poco PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${POCO_INCLUDE_DIR})

message("POCO_LIBRARIES: ${POCO_LIBRARIES}")

add_library(poco-foundation SHARED IMPORTED)
set_property(TARGET poco-foundation PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${POCO_INCLUDE_DIR})
set_property(TARGET poco-foundation PROPERTY IMPORTED_LOCATION ${POCO_Foundation_LIBRARY_DEBUG})

add_library(poco-net SHARED IMPORTED)
set_property(TARGET poco-net PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${POCO_INCLUDE_DIR})
set_property(TARGET poco-net PROPERTY IMPORTED_LOCATION ${POCO_Net_LIBRARY_DEBUG})

add_library(poco-util SHARED IMPORTED)
set_property(TARGET poco-util PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${POCO_INCLUDE_DIR})
set_property(TARGET poco-util PROPERTY IMPORTED_LOCATION ${POCO_Util_LIBRARY_DEBUG})

add_library(poco-data SHARED IMPORTED)
set_property(TARGET poco-data PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${POCO_INCLUDE_DIR})
set_property(TARGET poco-data PROPERTY IMPORTED_LOCATION ${POCO_Data_LIBRARY_DEBUG})

# add_library(poco-DataMySQL SHARED IMPORTED)
# set_property(TARGET poco-DataMySQL PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${POCO_INCLUDE_DIR})
# set_property(TARGET poco-DataMySQL PROPERTY IMPORTED_LOCATION ${POCO_DataMySQL_LIBRARY_DEBUG})

Add_library(poco-mysql SHARED IMPORTED)
set_property(TARGET poco-mysql PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${POCO_INCLUDE_DIR})
set_property(TARGET poco-mysql PROPERTY IMPORTED_LOCATION ${POCO_DataMySQL_LIBRARY_DEBUG})


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
