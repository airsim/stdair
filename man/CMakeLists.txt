##
# StdAir manual pages
# Generated with Doxygen
#
find_package ( Doxygen )
if ( DOXYGEN_FOUND )

  #
  set (OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"     )
  set (top_srcdir       "${CMAKE_SOURCE_DIR}"             )
  set (srcdir           "${CMAKE_CURRENT_SOURCE_DIR}"     )
  set (man1_DIR         "${CMAKE_CURRENT_BINARY_DIR}/man1")
  set (man3_DIR         "${CMAKE_CURRENT_BINARY_DIR}/man3")

  # Manual page sources
  set (man1_SOURCES "stdair.doc stdair-config.doc")
  set (man3_SOURCES "stdair-library.doc")

  # Convert the Doxygen configuration files (basically, just replace
  # the @src_dir@ macro).
  configure_file (doxygen_man1.cfg.in doxygen_man1.cfg @ONLY)
  configure_file (doxygen_man3.cfg.in doxygen_man3.cfg @ONLY)
  
  #
  add_custom_target (man1pages ALL DEPENDS ${man1_SOURCES})
  add_custom_target (man3pages ALL DEPENDS ${man3_SOURCES})
  add_custom_target (package_with_man DEPENDS man1pages man3pages COMMAND make package)

  #
  add_custom_command (OUTPUT "${man1_SOURCES}" COMMAND ${DOXYGEN_EXECUTABLE} 
	"doxygen_man1.cfg" COMMENT "Building section 1 manual pages ...")
  add_custom_command (OUTPUT "${man3_SOURCES}" COMMAND ${DOXYGEN_EXECUTABLE} 
	"doxygen_man3.cfg" COMMENT "Building section 3 manal pages ...")

  #
  set_property (DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES 
	"${CMAKE_CURRENT_BINARY_DIR}/man1")
  set_property (DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES 
	"${CMAKE_CURRENT_BINARY_DIR}/man3")

  #
  install (DIRECTORY "${man1_DIR}" DESTINATION "share/${PROJECT_NAME}/man")
  install (DIRECTORY "${man3_DIR}" DESTINATION "share/${PROJECT_NAME}/man")

endif ()
