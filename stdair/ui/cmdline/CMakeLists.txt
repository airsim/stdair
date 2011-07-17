# Library sources.
file (GLOB stdair_uicl_lib_SOURCES *.cpp)
file (GLOB stdair_uicl_lib_HEADERS *.hpp)

## Assembling
# Source files for the library
add_library (${STDAIR_UICL_LIB_TARGET} SHARED
  ${stdair_uicl_lib_SOURCES} ${stdair_uicl_lib_HEADERS})
#
set_target_properties (${STDAIR_UICL_LIB_TARGET} PROPERTIES LINKER_LANGUAGE CXX)
# Dependencies on other libraries (Boost, MySQL, SOCI)
target_link_libraries (${STDAIR_UICL_LIB_TARGET} ${BOOST_LIBS_FOR_LIB})
# Filename and SONAME
if (WIN32)
  set_target_properties (${STDAIR_UICL_LIB_TARGET} PROPERTIES 
	OUTPUT_NAME ${STDAIR_UICL_LIB_NAME}	VERSION ${GENERIC_LIB_VERSION}
	PUBLIC_HEADER "${stdair_uicl_lib_HEADERS}")
else ()
  set_target_properties (${STDAIR_UICL_LIB_TARGET} PROPERTIES 
	OUTPUT_NAME ${STDAIR_UICL_LIB_NAME}
	VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION}
	PUBLIC_HEADER "${stdair_uicl_lib_HEADERS}")
endif ()

## Installation
# Library
install (TARGETS ${STDAIR_UICL_LIB_TARGET} 
  EXPORT stdair-library-depends
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT runtime
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT runtime
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/${PACKAGE}/ui/cmdline"
  COMPONENT dev)
