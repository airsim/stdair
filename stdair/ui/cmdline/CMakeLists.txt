# Library sources.
file (GLOB stdair_uicl_lib_SOURCES *.cpp)
file (GLOB stdair_uicl_lib_HEADERS *.hpp)

## Assembling
# Source files for the library
add_library (${STDAIR_UICL_LIB_TARGET} SHARED
  ${stdair_uicl_lib_SOURCES} ${stdair_uicl_lib_HEADERS})
set_target_properties (${STDAIR_UICL_LIB_TARGET} PROPERTIES LINKER_LANGUAGE CXX)
# Dependencies on other libraries (Boost, MySQL, SOCI)
target_link_libraries (${STDAIR_UICL_LIB_TARGET} ${Boost_LIBRARIES})
# Filename and SONAME
if (WIN32)
  set_target_properties (${STDAIR_UICL_LIB_TARGET} PROPERTIES 
	OUTPUT_NAME ${STDAIR_UICL_LIB_NAME} VERSION ${GENERIC_LIB_VERSION})
else ()
  set_target_properties (${STDAIR_UICL_LIB_TARGET} PROPERTIES 
	OUTPUT_NAME ${STDAIR_UICL_LIB_NAME}
	VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION})
endif ()

## Installation
# Library
install (TARGETS ${STDAIR_UICL_LIB_TARGET} LIBRARY DESTINATION ${LIBDIR})

# Install header files
install (FILES ${stdair_uicl_lib_HEADERS} 
  DESTINATION include/${CPACK_PACKAGE_NAME}/ui/cmdline)
