##
# StdAir manual pages
# Generated with Doxygen
#

# Define the substitutes for the variables present in the Doxygen
# configuration files. Note that PACKAGE, PACKAGE_NAME and PACKAGE_VERSION
# are defined in the main CMakeLists.txt (of the top root directory).
set (OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"     )
set (top_srcdir       "${CMAKE_SOURCE_DIR}"             )
set (srcdir           "${CMAKE_CURRENT_SOURCE_DIR}"     )
set (man1_DIR         "${CMAKE_CURRENT_BINARY_DIR}/man1")
set (man3_DIR         "${CMAKE_CURRENT_BINARY_DIR}/man3")

# Convert the Doxygen configuration files (basically, just replace
# the @<variable>@ variables).
configure_file (doxygen_man1.cfg.in doxygen_man1.cfg @ONLY)
configure_file (doxygen_man3.cfg.in doxygen_man3.cfg @ONLY)

## Manual page sources
# Section 1 (general commands)
set (man1_SOURCES stdair.doc stdair-config.doc)
# Section 3 (development)
set (man3_SOURCES "stdair-library.doc")

#
add_custom_target (man1pages 
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/doxygen_man1.cfg ${man1_SOURCES}
  COMMAND ${DOXYGEN_EXECUTABLE} doxygen_man1.cfg ${man1_SOURCES}
  COMMENT "Building section 1 manual pages ...")
add_custom_target (man3pages 
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/doxygen_man3.cfg ${man3_SOURCES}
  COMMAND ${DOXYGEN_EXECUTABLE} doxygen_man3.cfg ${man3_SOURCES}
  COMMENT "Building section 3 manal pages ...")
add_custom_target (manpages ALL DEPENDS man1pages man3pages)

# Clean-up $build/man1 and $build/man3 on 'make clean'
set_property (DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES 
  "${CMAKE_CURRENT_BINARY_DIR}/man1")
set_property (DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES 
  "${CMAKE_CURRENT_BINARY_DIR}/man3")

# Installation of the manual pages
set (MAN_PATH "share/${PROJECT_NAME}/man")
install (DIRECTORY "${man1_DIR}" DESTINATION ${MAN_PATH})
install (DIRECTORY "${man3_DIR}" DESTINATION ${MAN_PATH})
