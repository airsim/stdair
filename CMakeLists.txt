#
cmake_minimum_required (VERSION 2.6)

###
##
# Project info
project (stdair)
string (TOLOWER "${PROJECT_NAME}" PACKAGE_TMP)
set (PACKAGE "${PACKAGE_TMP}" CACHE INTERNAL "Description")
string (TOUPPER "${PROJECT_NAME}" PACKAGE_NAME_TMP)
set (PACKAGE_NAME "${PACKAGE_NAME_TMP}" CACHE INTERNAL "Description")

##
# Version
set (stdair_VERSION_MAJOR 0)
set (stdair_VERSION_MINOR 25)
set (stdair_VERSION_PATCH 0)
set (stdair_VERSION "${stdair_VERSION_MAJOR}.${stdair_VERSION_MINOR}.${stdair_VERSION_PATCH}")

##
# Library target
set (STDAIR_LIBRARIES stdairlib)
# Library name
set (STDAIR_LIBRARY_NAME stdair)

# Packaging
include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "C++ Standard Airline IT Library")
set (CPACK_PACKAGE_VENDOR "denis_arnaud@sourceforge.net")
set (CPACK_PACKAGE_VERSION_MAJOR "${stdair_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${stdair_VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${stdair_VERSION_PATCH}")
set (CPACK_PACKAGE_VERSION "${stdair_VERSION}")
set (CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/README)
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set (CPACK_SOURCE_GENERATOR "RPM;TGZ")

# CMake scripts path
set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/config/)

# Compilation
set (CMAKE_CXX_FLAGS "-g -Wall -Werror")
include_directories(BEFORE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}) 

# Dependencies
# ~~~~~~~~~~ BOOST ~~~~~~~~~~
find_package ( Boost 1.44 REQUIRED COMPONENTS program_options date_time 
  iostreams serialization filesystem unit_test_framework)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()
# ~~~~~~~~~~ MySQL ~~~~~~~~~
find_package ( MySQL )
if (MYSQL_FOUND)
  include_directories(${MYSQL_INCLUDE_DIR})
endif()

# ~~~~~~~~~~ SOCI ~~~~~~~~~~
find_package ( SOCI )
if (SOCI_FOUND)
  include_directories(${SOCI_INCLUDE_DIR})
endif()
find_package ( SOCIMySQL )
if (SOCIMYSQL_FOUND)
  include_directories(${SOCIMYSQL_INCLUDE_DIR})
endif()

# Subdirs
add_subdirectory (${PROJECT_NAME})
add_subdirectory (batches)
add_subdirectory (man)
add_subdirectory (doc)
add_subdirectory (test)
