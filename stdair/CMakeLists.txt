# Library sources. All listed here for simplicity, but tailored
# compilations can be done in a given subdir if a CMakeList is
# provided there and add_subdirectory is used here (and the
# corresponding sources removed from here, of course).
file (GLOB stdairlib_SOURCES *.cpp basic/*.cpp bom/*.cpp factory/*.cpp
  dbadaptor/*.cpp command/*.cpp service/*.cpp)
file (GLOB stdairlib_HEADERS *.hpp)

# Configuration 
configure_file (config.h.in config.h @ONLY)
configure_file (config/${PACKAGE}-paths.hpp.in config/${PACKAGE}-paths.hpp)

## Assembling
# Source files for the library
add_library (${STDAIR_LIB_TARGET} SHARED ${stdairlib_SOURCES})
# Dependencies on other libraries (Boost, MySQL, SOCI)
target_link_libraries (${STDAIR_LIB_TARGET} 
  ${Boost_LIBRARIES} ${MYSQL_LIBRARIES}
  ${SOCI_LIBRARIES} ${SOCIMYSQL_LIBRARIES})
# Filename and SONAME
if (WIN32)
  set_target_properties (${STDAIR_LIB_TARGET} PROPERTIES 
	OUTPUT_NAME ${STDAIR_LIB_NAME} VERSION ${GENERIC_LIB_VERSION})
else ()
  set_target_properties (${STDAIR_LIB_TARGET} PROPERTIES 
	OUTPUT_NAME ${STDAIR_LIB_NAME}
	VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION})
endif ()

## Installation
# Library
install (TARGETS ${STDAIR_LIB_TARGET} LIBRARY DESTINATION ${LIBDIR})

# Install header files
install (FILES ${stdairlib_HEADERS} DESTINATION include/${CPACK_PACKAGE_NAME})
install (DIRECTORY basic DESTINATION include/${CPACK_PACKAGE_NAME}
  FILES_MATCHING PATTERN "*.hpp")
install (DIRECTORY bom DESTINATION include/${CPACK_PACKAGE_NAME}
  FILES_MATCHING PATTERN "*.hpp")
install (DIRECTORY factory DESTINATION include/${CPACK_PACKAGE_NAME}
  FILES_MATCHING PATTERN "*.hpp")
install (DIRECTORY dbadaptor DESTINATION include/${CPACK_PACKAGE_NAME}
  FILES_MATCHING PATTERN "*.hpp")
install (DIRECTORY command DESTINATION include/${CPACK_PACKAGE_NAME}
  FILES_MATCHING PATTERN "*.hpp")
install (DIRECTORY service DESTINATION include/${CPACK_PACKAGE_NAME}
  FILES_MATCHING PATTERN "*.hpp")
