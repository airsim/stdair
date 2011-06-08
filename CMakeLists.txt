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
set (stdair_VERSION_MAJOR 99)
set (stdair_VERSION_MINOR 99)
set (stdair_VERSION_PATCH 99)
set (stdair_VERSION "${stdair_VERSION_MAJOR}.${stdair_VERSION_MINOR}.${stdair_VERSION_PATCH}")
set (PACKAGE_VERSION "${stdair_VERSION}")
# Note that the soname could be different from the version. The soname
# should change only the ABI compatibility is no longer guaranteed.
set (GENERIC_LIB_VERSION "${stdair_VERSION}")
set (GENERIC_LIB_SOVERSION "${stdair_VERSION_MAJOR}.${stdair_VERSION_MINOR}")
set (LIBDIR "lib${LIB_SUFFIX}")

##
# Project options
option (BUILD_SHARED_LIBS "Set to OFF to build static libraries" ON)
option (INSTALL_DOC "Set to OFF to skip build/install Documentation" ON)
# Set default cmake build type to Debug (None Debug Release RelWithDebInfo
# MinSizeRel)
if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE "Debug")
endif()

# Set default install prefix to project root directory
if (CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
  set (CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}")
endif()

# Offer the user the choice of overriding the installation directories
set (INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set (INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set (INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")
set (INSTALL_DATA_DIR share CACHE PATH
  "Installation directory for data files")

# Make relative paths absolute (needed later on)
foreach (p LIB BIN INCLUDE DATA)
  set (var INSTALL_${p}_DIR)
  if (NOT IS_ABSOLUTE "${${var}}")
    set (${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

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
# "Other" Documentation
set (OTHERDOC_FILES AUTHORS NEWS README INSTALL)
set (OTHERDOC_PATH "share/doc/${PACKAGE}-${PACKAGE_VERSION}")
install (FILES ${OTHERDOC_FILES} DESTINATION ${OTHERDOC_PATH})

##
# Packaging
include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set (CPACK_PACKAGE_DESCRIPTION "C++ Standard Airline IT Library")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_NAME} aims at providing a clean API, and the corresponding C++ implementation, for the basis of Airline IT Business Object Model (BOM), that is, to be used by several other open source projects, such as RMOL, Air-Sched, Travel-CCM, OpenTREP, etc.")

set (CPACK_PACKAGE_CONTACT "Denis Arnaud <denis_arnaud@users.sourceforge.net>")
set (CPACK_PACKAGE_VENDOR "Denis Arnaud")
set (CPACK_PACKAGE_VERSION_MAJOR ${stdair_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${stdair_VERSION_MINOR})
#set (CPACK_PACKAGE_VERSION_PATCH ${stdair_VERSION_PATCH})
set (CPACK_PACKAGE_VERSION_PATCH ${GIT_REVISION})
set (CPACK_PACKAGE_VERSION ${stdair_VERSION})
set (CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/README)
set (CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/COPYING)
set (CPACK_GENERATOR "TBZ2")
#set (CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.6), libgcc1 (>= 1:4.1)")

# Available types of package: DEB, RPM, TZ, TGZ, TBZ2
set (CPACK_SOURCE_GENERATOR "TBZ2")
set (CPACK_SOURCE_PACKAGE_FILE_NAME 
  "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}"
  CACHE INTERNAL "tarball basename")
set (AUTOTOOLS_IGNRD "/tmp/;/tmp2/;/autom4te\\\\.cache/;autogen\\\\.sh$")
set (PACK_IGNRD "${CPACK_PACKAGE_NAME}\\\\.spec;/build/;\\\\.gz$;\\\\.bz2$")
set (EDIT_IGNRD "\\\\.swp$;\\\\.#;/#;~$")
set (SCM_IGNRD 
  "/CVS/;/\\\\.svn/;/\\\\.bzr/;/\\\\.hg/;/\\\\.git/;\\\\.gitignore$")
set (CPACK_SOURCE_IGNORE_FILES
  "${AUTOTOOLS_IGNRD};${SCM_IGNRD};${EDIT_IGNRD};${PACK_IGNRD}"
  CACHE STRING "CPACK will ignore these files")
#set (CPACK_SOURCE_IGNORE_DIRECTORY ${CPACK_SOURCE_IGNORE_FILES} .git)

##
# Set all the directory pathes for the project (e.g., prefix, libdir, bindir)
include (config/project_config.cmake)

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

##
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

##
# Subdirs
add_subdirectory (${PROJECT_NAME})
add_subdirectory (${PROJECT_NAME}/ui/cmdline)
add_subdirectory (batches)
add_subdirectory (db)
add_subdirectory (samples)
add_subdirectory (man)
add_subdirectory (doc)
add_subdirectory (test)

# Add all targets to the build-tree export set
export (TARGETS ${PROJECT_NAME} ${STDAIR_LIB_TARGET} ${STDAIR_UICL_LIB_TARGET}
  FILE "${PROJECT_BINARY_DIR}/StdAirLibraryDepends.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export (PACKAGE stdair)

# Create a StdAirConfig.cmake file for the use from the build tree
set (STDAIR_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
set (STDAIR_LIB_DIR "${PROJECT_BINARY_DIR}/${PACKAGE}")
set (STDAIR_CMAKE_DIR "${PROJECT_BINARY_DIR}")
configure_file (StdAirConfig.cmake.in
  "${PROJECT_BINARY_DIR}/StdAirConfig.cmake" @ONLY)
configure_file (StdAirConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/StdAirConfigVersion.cmake" @ONLY)

# Install the export set for use with the install-tree
#install (EXPORT StdAirLibraryDepends DESTINATION
#  "${INSTALL_DATA_DIR}/${PACKAGE}/CMake" COMPONENT dev)

# Create a StdAirConfig.cmake file for the use from the install tree
# and install it
set (STDAIR_INCLUDE_DIRS "${INSTALL_INCLUDE_DIR}")
set (STDAIR_LIB_DIR "${INSTALL_LIB_DIR}")
set (STDAIR_CMAKE_DIR "${INSTALL_DATA_DIR}/${PACKAGE}/CMake")
configure_file (StdAirConfig.cmake.in
  "${PROJECT_BINARY_DIR}/InstallFiles/StdAirConfig.cmake" @ONLY)
configure_file (StdAirConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/InstallFiles/StdAirConfigVersion.cmake" @ONLY)
install (FILES
  "${PROJECT_BINARY_DIR}/InstallFiles/StdAirConfig.cmake"
  "${PROJECT_BINARY_DIR}/InstallFiles/StdAirConfigVersion.cmake"
  DESTINATION "${STDAIR_CMAKE_DIR}" COMPONENT dev)


##
# Packaging
include (CPack)
# Add a 'dist' target, similar to what is given by GNU Autotools
add_custom_target (dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)


# Display status message for important variables
message (STATUS)
message (STATUS "-------------------------------------------------------------")
message (STATUS "BUILD_SHARED_LIBS = ${BUILD_SHARED_LIBS}" )
message (STATUS "CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}" )
message (STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}" )
message (STATUS "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}" )
message (STATUS "INSTALL_DOC = ${INSTALL_DOC}" )
message (STATUS)
message (STATUS "CPACK_PACKAGE_CONTACT = ${CPACK_PACKAGE_CONTACT}")
message (STATUS "CPACK_PACKAGE_VENDOR = ${CPACK_PACKAGE_VENDOR}")
message (STATUS "CPACK_PACKAGE_VERSION = ${CPACK_PACKAGE_VERSION}")
message (STATUS "CPACK_PACKAGE_DESCRIPTION_FILE = ${CPACK_PACKAGE_DESCRIPTION_FILE}")
message (STATUS "CPACK_RESOURCE_FILE_LICENSE = ${CPACK_RESOURCE_FILE_LICENSE}")
message (STATUS "CPACK_GENERATOR = ${CPACK_GENERATOR}")
message (STATUS "CPACK_DEBIAN_PACKAGE_DEPENDS = ${CPACK_DEBIAN_PACKAGE_DEPENDS}")
message (STATUS "CPACK_SOURCE_GENERATOR = ${CPACK_SOURCE_GENERATOR}")
message (STATUS "CPACK_SOURCE_PACKAGE_FILE_NAME = ${CPACK_SOURCE_PACKAGE_FILE_NAME}")
message (STATUS)
message (STATUS "Change a value with: cmake -D<Variable>=<Value>" )
message (STATUS "-------------------------------------------------------------")
message (STATUS)

# Force some variables that could be defined in the command line to be
# written to cache
set (BUILD_SHARED_LIBS "${BUILD_SHARED_LIBS}" CACHE BOOL
  "Set to OFF to build static libraries" FORCE)
set (CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}" CACHE PATH
  "Where to install ${PROJECT_NAME}" FORCE)
set (CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING
  "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" CACHE PATH
  "Path to custom CMake Modules" FORCE)
set (INSTALL_DOC "${INSTALL_DOC}" CACHE BOOL
  "Set to OFF to skip build/install Documentation" FORCE)
