# Doxygen
find_package ( Doxygen )
if ( DOXYGEN_FOUND )

  set ( OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}" )
  set ( PACKAGE_NAME     "${CPACK_PACKAGE_NAME}"            )
  set ( PACKAGE_VERSION  "${CPACK_PACKAGE_VERSION}"         )
  set ( top_srcdir       "${CMAKE_SOURCE_DIR}"      )
  set ( doc_FILES        "${CMAKE_CURRENT_BINARY_DIR}/html" )

  configure_file ( doxygen_html.cfg.in doxygen_html.cfg @ONLY )
  
  add_custom_target ( docs ALL DEPENDS  ${doc_FILES} )
  add_custom_target ( package_with_doc DEPENDS docs COMMAND make package )

  add_custom_command ( OUTPUT ${doc_FILES} COMMAND ${DOXYGEN_EXECUTABLE} "doxygen_html.cfg" COMMENT "Building doc ..." )

  set_property ( DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_CURRENT_BINARY_DIR}/html")

  install ( DIRECTORY ${doc_FILES} DESTINATION "share/doc/${PROJECT_NAME}-${VERSION}" )

endif ()
