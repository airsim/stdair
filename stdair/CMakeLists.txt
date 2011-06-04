# Library sources. All listed here for simplicity, but tailored
# compilations can be done in a given subdir if a CMakeList is
# provided there and add_subdirectory is used here (and the
# corresponding sources removed from here, of course).
file (GLOB_RECURSE stdairlib_SOURCES *.cpp)
file (GLOB stdairlib_HEADERS *.hpp)

# Configuration 
configure_file (config.h.in config.h @ONLY)
configure_file (config/${PACKAGE}-paths.hpp.in config/${PACKAGE}-paths.hpp)

# Assembling
add_library (${STDAIR_LIBRARIES} SHARED ${stdairlib_SOURCES})
set_target_properties (${STDAIR_LIBRARIES} PROPERTIES 
  OUTPUT_NAME "${STDAIR_LIBRARY_NAME}" )
target_link_libraries (${STDAIR_LIBRARIES} ${Boost_LIBRARIES} ${MYSQL_LIBRARIES}
  ${SOCI_LIBRARIES} ${SOCIMYSQL_LIBRARIES})

# Tell CMake about the dependencies
set (CMAKE_REQUIRED_LIBRARIES 
  "${STDAIR_LIBRARIES};${Boost_LIBRARIES} ${MYSQL_LIBRARIES} ${SOCI_LIBRARIES} ${SOCIMYSQL_LIBRARIES}")

## Installation
# Library
install (TARGETS ${STDAIR_LIBRARIES} LIBRARY DESTINATION lib)

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
install (DIRECTORY ui/cmdline DESTINATION include/${CPACK_PACKAGE_NAME}/ui
  FILES_MATCHING PATTERN "*.hpp")
