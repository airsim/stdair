##
# StdAir Documentation (HTML, PDF, RTF)
# Generated with Doxygen
#
find_package ( Doxygen )
if ( DOXYGEN_FOUND )

  #
  set (OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
  set (top_srcdir       "${CMAKE_SOURCE_DIR}"      )
  set (srcdir           "${CMAKE_CURRENT_SOURCE_DIR}"     )
  set (doc_FILES        "${CMAKE_CURRENT_BINARY_DIR}/html")

  # Manual page sources
  set (docimagesPNG_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/images/*.png")
  set (docimagesICO_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/images/*.ico")
  set (docimages_SOURCES ${docimagesICO_SOURCES} ${docimagesPNG_SOURCES})
  set (doctutorial_SOURCES "tutorial/*.doc")
  set (doclocaldoc_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/local/*.doc")
  set (doclocalhtml_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/local/*.html")
  set (doclocal_SOURCES ${doclocaldoc_SOURCES} ${doclocalhtml_SOURCES})
  set (doc_SOURCES ${docimages_SOURCES} ${doctutorial_SOURCES} ${doclocal_SOURCES})

  # Convert the Doxygen configuration files (basically, just replace
  # the @src_dir@ macro).
  configure_file (doxygen_html.cfg.in doxygen_html.cfg @ONLY)
  
  #
  #add_custom_target (docs ALL DEPENDS ${doc_FILES})
  add_custom_target (docs ALL DEPENDS ${doc_SOURCES})
  add_custom_target (package_with_doc DEPENDS docs COMMAND make package)

  #
  add_custom_command ( OUTPUT ${doc_SOURCES} COMMAND ${DOXYGEN_EXECUTABLE} 
	"doxygen_html.cfg" COMMENT "Building doc ..." )

  #
  set_property ( DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES 
	"${CMAKE_CURRENT_BINARY_DIR}/html")
  set_property ( DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES 
	"${CMAKE_CURRENT_BINARY_DIR}/latex")

  #
  install ( DIRECTORY ${doc_FILES} DESTINATION 
	"share/doc/${PROJECT_NAME}-${CPACK_PACKAGE_VERSION}")

endif ()
