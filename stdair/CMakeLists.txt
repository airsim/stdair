# Library sources. All listed here for simplicity, but tailored
# compilations can be done in a given subdir if a CMakeList is
# provided there and add_subdirectory is used here (and the
# corresponding sources removed from here, of course).
file ( GLOB_RECURSE stdairlib_SOURCES *.cpp )

# Configuration 
configure_file(config.h.in config.h @ONLY)
configure_file(config/${PACKAGE}-paths.hpp.in config/${PACKAGE}-paths.hpp)

# Assembling
add_library (${STDAIR_LIBRARIES} SHARED ${stdairlib_SOURCES})
set_target_properties (${STDAIR_LIBRARIES} PROPERTIES OUTPUT_NAME "${STDAIR_LIBRARY_NAME}" )
target_link_libraries (${STDAIR_LIBRARIES} ${Boost_LIBRARIES} ${MYSQL_LIBRARIES}
  ${SOCI_LIBRARIES} ${SOCIMYSQL_LIBRARIES})

