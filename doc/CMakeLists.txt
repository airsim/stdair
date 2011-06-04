##
# StdAir Documentation (HTML, PDF, RTF)
# Generated with Doxygen
#

# Define the substitutes for the variables present in the Doxygen
# configuration file. Note that PACKAGE, PACKAGE_NAME and PACKAGE_VERSION
# are defined in the main CMakeLists.txt (of the top root directory).
set (OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
set (top_srcdir       "${CMAKE_SOURCE_DIR}")
set (srcdir           "${CMAKE_CURRENT_SOURCE_DIR}")
set (doc_FILES        "${CMAKE_CURRENT_BINARY_DIR}/html")
#
set (DOXYGEN_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")

# Convert the Doxygen configuration files (basically, just replace
# the @<variable>@ variables).
configure_file (doxygen_html.cfg.in doxygen_html.cfg @ONLY)

## Documentation sources
# Images
set (docimages_DIR "${CMAKE_CURRENT_SOURCE_DIR}/images")
# Tutorial
set (doctutorial_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tutorial/*.doc")
# Local
set (doclocaldoc_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/local/*.doc")
set (doclocalhtml_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/local/*.html")
set (doclocal_SOURCES ${doclocaldoc_SOURCES} ${doclocalhtml_SOURCES})
# Aggregating all the documentation sources
set (doc_SOURCES ${doctutorial_SOURCES} ${doclocal_SOURCES})

# Add the 'docs' target, depending on the documentation sources and
# launching Doxygen
add_custom_target (docs
  COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxygen_html.cfg ${doc_SOURCES}
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/doxygen_html.cfg ${doc_SOURCES}
  COMMENT "Building doc ...")

# Copy the images into the target directory.
# First, a CMake configuration file is written. Then, a target is added, 
# using that CMake configuration file. Indeed, the file() directive is
# executed only at configuration time (when 'cmake' is called), whereas
# the add_custom_command() is triggered by every 'make' command.
file (WRITE ${CMAKE_BINARY_DIR}/copy_doc_images.cmake
  "file (COPY ${docimages_DIR}/${CPACK_PACKAGE_NAME}_logo.png	
       DESTINATION ${doc_FILES})
   file (COPY ${docimages_DIR}/sfx_logo.png DESTINATION ${doc_FILES})
   file (COPY ${docimages_DIR}/favicon.ico DESTINATION ${doc_FILES})")
#
add_custom_target (copy_doc_images
 COMMAND ${CMAKE_COMMAND} -P copy_doc_images.cmake)

# Clean-up $build/html and $build/latex on 'make clean'
set_property (DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES 
  "${CMAKE_CURRENT_BINARY_DIR}/html")
set_property (DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES 
  "${CMAKE_CURRENT_BINARY_DIR}/latex")

# Installation of the HTML documentation
set (DOC_PATH "share/doc/${PROJECT_NAME}-${CPACK_PACKAGE_VERSION}")
install (DIRECTORY ${doc_FILES} DESTINATION ${DOC_PATH})
