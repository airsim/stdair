#
cmake_minimum_required (VERSION 2.6)

# See also:
# http://snikt.net/index.php/2010/04/01/howto-use-cmake-with-cc-projects

###
##
# Project info
project (stdair)
set (PACKAGE_PRETTY_NAME "StdAir" CACHE INTERNAL "Description")
string (TOLOWER "${PROJECT_NAME}" PACKAGE_TMP)
set (PACKAGE "${PACKAGE_TMP}" CACHE INTERNAL "Description")
string (TOUPPER "${PROJECT_NAME}" PACKAGE_NAME_TMP)
set (PACKAGE_NAME "${PACKAGE_NAME_TMP}" CACHE INTERNAL "Description")

##
# Version
set (stdair_VERSION_MAJOR 0)
set (stdair_VERSION_MINOR 32)
set (stdair_VERSION_PATCH 0)
set (stdair_VERSION "${stdair_VERSION_MAJOR}.${stdair_VERSION_MINOR}.${stdair_VERSION_PATCH}")
set (PACKAGE_VERSION "${stdair_VERSION}")

# Note that the soname could be different from the version. The soname
# should change only the ABI compatibility is no longer guaranteed.
set (GENERIC_LIB_VERSION "${stdair_VERSION}")
set (GENERIC_LIB_SOVERSION "${stdair_VERSION_MAJOR}.${stdair_VERSION_MINOR}")
set (LIBDIR "lib${LIB_SUFFIX}")

##
# Library target. It is specified here because both the stair (for the library
# target) and batches (for the binary target) sub-directories need it.
set (STDAIR_LIB_TARGET ${PROJECT_NAME}lib)
set (STDAIR_UICL_LIB_TARGET ${PROJECT_NAME}uicllib)
# Library names
set (STDAIR_LIB_NAME ${PROJECT_NAME})
set (STDAIR_UICL_LIB_NAME ${PROJECT_NAME}uicl)

##
# SCM (Git)
find_package (Git)
if (Git_FOUND)
  Git_WC_INFO (${CMAKE_CURRENT_SOURCE_DIR} ER)
  set (GIT_REVISION ${ER_WC_REVISION})
endif (Git_FOUND)

##
# Packaging
include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set (CPACK_PACKAGE_DESCRIPTION "C++ Standard Airline IT Library")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_NAME} aims at providing a clean API, and the corresponding C++ implementation, for the basis of Airline IT Business Object Model (BOM), that is, to be used by several other open source projects, such as RMOL, Air-Sched, Travel-CCM, OpenTREP, etc.")

set (CPACK_PACKAGE_CONTACT "Denis Arnaud <denis_arnaud@users.sourceforge.net>")
set (CPACK_PACKAGE_VENDOR "Denis Arnaud")
set (CPACK_PACKAGE_VERSION_MAJOR "${stdair_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${stdair_VERSION_MINOR}")
#set (CPACK_PACKAGE_VERSION_PATCH "${stdair_VERSION_PATCH}")
set (CPACK_PACKAGE_VERSION_PATCH "${GIT_REVISION}")
set (CPACK_PACKAGE_VERSION "${stdair_VERSION}")
set (CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/README)
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")

#set (CPACK_SOURCE_GENERATOR "DEB;RPM;TGZ;TBZ2")
set (CPACK_GENERATOR "TGZ;TBZ2")
#set (CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.6), libgcc1 (>= 1:4.1)")
include (CPack)
# Add a 'dist' target, similar to what is given by GNU Autotools
add_custom_target (dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)

##
# "Other" Documentation
set (OTHERDOC_FILES AUTHORS NEWS README)
set (OTHERDOC_PATH "share/doc/${CPACK_PACKAGE_NAME}-${stdair_VERSION}")
install (FILES ${OTHERDOC_FILES} DESTINATION ${OTHERDOC_PATH})

##
# For the other developers to use that project
include (config/devhelpers.cmake)

# CMake scripts path
set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/config/)

# Compilation
# Note: the debug flag (-g) is set (or not) by giving the
# corresponding option when calling cmake:
# cmake -DCMAKE_BUILD_TYPE:STRING={Debug,Release,MinSizeRel,RelWithDebInfo}
#set (CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Werror")
set (CMAKE_CXX_FLAGS "-Wall -Werror")
include_directories (BEFORE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}) 

# Dependencies
# ~~~~~~~~~~ BOOST ~~~~~~~~~~
find_package (Boost 1.44 REQUIRED COMPONENTS program_options date_time 
  iostreams serialization filesystem unit_test_framework)
if (Boost_FOUND)
  include_directories (${Boost_INCLUDE_DIRS})
endif()

# ~~~~~~~~~~ MySQL ~~~~~~~~~
find_package (MySQL)
if (MYSQL_FOUND)
  include_directories (${MYSQL_INCLUDE_DIR})
endif()

# ~~~~~~~~~~ SOCI ~~~~~~~~~~
find_package (SOCI)
if (SOCI_FOUND)
  include_directories (${SOCI_INCLUDE_DIR})
endif()
find_package (SOCIMySQL)
if (SOCIMYSQL_FOUND)
  include_directories (${SOCIMYSQL_INCLUDE_DIR})
endif()

# ~~~~~~~~~~ MySQL ~~~~~~~~~
find_package (Doxygen REQUIRED)


# Subdirs
add_subdirectory (${PROJECT_NAME})
add_subdirectory (${PROJECT_NAME}/ui/cmdline)
add_subdirectory (batches)
add_subdirectory (samples)
add_subdirectory (man)
add_subdirectory (doc)
add_subdirectory (test)
