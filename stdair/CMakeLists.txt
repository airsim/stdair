##
# Convert the configuration headers (basically, just replace the @<variable>@
# variables).
configure_file (config.h.in config.h @ONLY)
set (PROJ_PATH_CFG_SRC config/${PACKAGE}-paths.hpp.in)
set (PROJ_PATH_CFG ${CMAKE_CURRENT_BINARY_DIR}/config/${PACKAGE}-paths.hpp)
configure_file (${PROJ_PATH_CFG_SRC} ${PROJ_PATH_CFG} @ONLY)

# Add the 'hdr_cfg' target, depending on the converted header
add_custom_target (hdr_cfg ALL DEPENDS ${PROJ_PATH_CFG})


##
# Library sources. All listed here for simplicity, but tailored
# compilations can be done in a given subdir if a CMakeList is
# provided there and add_subdirectory is used here (and the
# corresponding sources removed from here, of course).
# The libraries could then be assembled as CMake modules.
file (GLOB stdairlib_root_HEADERS *.hpp)
file (GLOB stdairlib_basic_HEADERS basic/*.hpp)
file (GLOB stdairlib_bom_HEADERS bom/*.hpp)
file (GLOB stdairlib_factory_HEADERS factory/*.hpp)
file (GLOB stdairlib_dbadaptor_HEADERS dbadaptor/*.hpp)
file (GLOB stdairlib_command_HEADERS command/*.hpp)
file (GLOB stdairlib_service_HEADERS service/*.hpp)
set (stdairlib_HEADERS
  ${stdairlib_root_HEADERS} ${stdairlib_basic_HEADERS}
  ${stdairlib_bom_HEADERS} ${stdairlib_factory_HEADERS}
  ${stdairlib_dbadaptor_HEADERS} ${stdairlib_command_HEADERS}
  ${stdairlib_service_HEADERS} ${PROJ_PATH_CFG})
file (GLOB stdairlib_SOURCES
  *.cpp basic/*.cpp bom/*.cpp factory/*.cpp
  dbadaptor/*.cpp command/*.cpp service/*.cpp)
set (stdairlib_SOURCES ${stdairlib_HEADERS} ${stdairlib_SOURCES})


## Assembling
# Source files for the library
add_library (${STDAIR_LIB_TARGET} SHARED ${stdairlib_SOURCES})
# Dependencies on other libraries (Boost, MySQL, SOCI)
target_link_libraries (${STDAIR_LIB_TARGET} 
  ${BOOST_LIBS_FOR_LIB} ${MYSQL_LIBRARIES}
  ${SOCI_LIBRARIES} ${SOCIMYSQL_LIBRARIES})
#
add_dependencies (${STDAIR_LIB_TARGET} hdr_cfg)
# Filename and SONAME
if (WIN32)
  set_target_properties (${STDAIR_LIB_TARGET} PROPERTIES 
	OUTPUT_NAME ${STDAIR_LIB_NAME} 
	VERSION ${GENERIC_LIB_VERSION}
	PUBLIC_HEADER "${stdairlib_root_HEADERS}")
else()
  set_target_properties (${STDAIR_LIB_TARGET} PROPERTIES 
	OUTPUT_NAME ${STDAIR_LIB_NAME}
	VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION}
	PUBLIC_HEADER "${stdairlib_root_HEADERS}")
endif()


## Installation
# Library
install (TARGETS ${STDAIR_LIB_TARGET} 
  EXPORT StdAirLibraryDepends
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/${PACKAGE}" COMPONENT dev)

# Install header files
install (DIRECTORY basic
  EXPORT StdAirLibraryDepends
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/${PACKAGE}" COMPONENT dev
  FILES_MATCHING PATTERN "*.hpp")
install (DIRECTORY bom
  EXPORT StdAirLibraryDepends
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/${PACKAGE}" COMPONENT dev
  FILES_MATCHING PATTERN "*.hpp")
install (DIRECTORY factory
  EXPORT StdAirLibraryDepends
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/${PACKAGE}" COMPONENT dev
  FILES_MATCHING PATTERN "*.hpp")
install (DIRECTORY dbadaptor
  EXPORT StdAirLibraryDepends
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/${PACKAGE}" COMPONENT dev
  FILES_MATCHING PATTERN "*.hpp")
install (DIRECTORY command
  EXPORT StdAirLibraryDepends
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/${PACKAGE}" COMPONENT dev
  FILES_MATCHING PATTERN "*.hpp")
install (DIRECTORY service
  EXPORT StdAirLibraryDepends
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/${PACKAGE}" COMPONENT dev
  FILES_MATCHING PATTERN "*.hpp")
install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/config
  EXPORT StdAirLibraryDepends
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/${PACKAGE}" COMPONENT dev
  FILES_MATCHING PATTERN "*.hpp")
