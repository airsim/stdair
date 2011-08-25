# Define the substitutes for the variables present in the develpment
# support files. Note that PACKAGE, PACKAGE_NAME and PACKAGE_VERSION
# are defined in the main CMakeLists.txt (of the top root directory).
set (prefix       "${CMAKE_INSTALL_PREFIX}")
set (exec_prefix  "${prefix}")
set (bindir       "${prefix}/bin")
set (libdir       "${exec_prefix}/${LIBDIR}")
set (includedir   "${prefix}/include")
set (datarootdir  "${prefix}/share")
set (datadir      "${datarootdir}")
set (pkgdatadir   "${datarootdir}/${CPACK_PACKAGE_NAME}")
set (sampledir    "${datarootdir}/${CPACK_PACKAGE_NAME}/samples")
set (docdir       "${datarootdir}/doc/${CPACK_PACKAGE_NAME}-${stdair_VERSION}")
set (mandir       "${datarootdir}/man")
set (infodir      "${datarootdir}/info")

# Specify the file name and installation directory
set (PROJ_PATH_CFG ${PACKAGE}/config/${PACKAGE}-paths.hpp)
set (PROJ_PATH_INS_PATH ${PACKAGE}/config)

#
file (WRITE ${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_PATH_CFG} "
#ifndef __STDAIR_PATHS_HPP
#define __STDAIR_PATHS_HPP

#define PACKAGE \"${PROJECT_NAME}\"
#define PACKAGE_NAME \"${CPACK_PROJECT_NAME}\"
#define PACKAGE_VERSION \"${CPACK_PACKAGE_VERSION}\"
#define PREFIXDIR \"${prefix}\"
#define BINDIR \"${bindir}\"
#define LIBEXECDIR \"${libexecdir}\"
#define DATADIR \"${datadir}\"
#define DOCDIR \"${docdir}\"
#define STDAIR_SAMPLE_DIR \"${sampledir}\"

#endif // __STDAIR_PATHS_HPP
")

# Add the target
add_custom_target (proj_path_cfg ALL DEPENDS)
add_dependencies (proj_path_cfg ${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_PATH_CFG})

# Install the project path header
install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_PATH_CFG}
  DESTINATION ${PROJ_PATH_INS_PATH})
