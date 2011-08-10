# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. Example variables are:
#   CPACK_GENERATOR                     - Generator used to create package
#   CPACK_INSTALL_CMAKE_PROJECTS        - For each project (path, name, component)
#   CPACK_CMAKE_GENERATOR               - CMake Generator used for the projects
#   CPACK_INSTALL_COMMANDS              - Extra commands to install components
#   CPACK_INSTALL_DIRECTORIES           - Extra directories to install
#   CPACK_PACKAGE_DESCRIPTION_FILE      - Description file for the package
#   CPACK_PACKAGE_DESCRIPTION_SUMMARY   - Summary of the package
#   CPACK_PACKAGE_EXECUTABLES           - List of pairs of executables and labels
#   CPACK_PACKAGE_FILE_NAME             - Name of the package generated
#   CPACK_PACKAGE_ICON                  - Icon used for the package
#   CPACK_PACKAGE_INSTALL_DIRECTORY     - Name of directory for the installer
#   CPACK_PACKAGE_NAME                  - Package project name
#   CPACK_PACKAGE_VENDOR                - Package project vendor
#   CPACK_PACKAGE_VERSION               - Package project version
#   CPACK_PACKAGE_VERSION_MAJOR         - Package project version (major)
#   CPACK_PACKAGE_VERSION_MINOR         - Package project version (minor)
#   CPACK_PACKAGE_VERSION_PATCH         - Package project version (patch)

# There are certain generator specific ones

# NSIS Generator:
#   CPACK_PACKAGE_INSTALL_REGISTRY_KEY  - Name of the registry key for the installer
#   CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS - Extra commands used during uninstall
#   CPACK_NSIS_EXTRA_INSTALL_COMMANDS   - Extra commands used during install


SET(CPACK_BINARY_BUNDLE "")
SET(CPACK_BINARY_CYGWIN "")
SET(CPACK_BINARY_DEB "")
SET(CPACK_BINARY_DRAGNDROP "")
SET(CPACK_BINARY_NSIS "")
SET(CPACK_BINARY_OSXX11 "")
SET(CPACK_BINARY_PACKAGEMAKER "")
SET(CPACK_BINARY_RPM "")
SET(CPACK_BINARY_STGZ "")
SET(CPACK_BINARY_TBZ2 "")
SET(CPACK_BINARY_TGZ "")
SET(CPACK_BINARY_TZ "")
SET(CPACK_BINARY_ZIP "")
SET(CPACK_CMAKE_GENERATOR "Unix Makefiles")
SET(CPACK_COMPONENTS_ALL "")
SET(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
SET(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
SET(CPACK_GENERATOR "TBZ2")
SET(CPACK_INSTALL_CMAKE_PROJECTS "/home/localoriuser/dev/sim/stdair/stdairgit;Project;ALL;/")
SET(CPACK_INSTALL_PREFIX "/usr")
SET(CPACK_MODULE_PATH "")
SET(CPACK_NSIS_DISPLAY_NAME "stdair 99.99.99")
SET(CPACK_NSIS_INSTALLER_ICON_CODE "")
SET(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
SET(CPACK_NSIS_PACKAGE_NAME "stdair 99.99.99")
SET(CPACK_OUTPUT_CONFIG_FILE "/home/localoriuser/dev/sim/stdair/stdairgit/CPackConfig.cmake")
SET(CPACK_PACKAGE_CONTACT "Denis Arnaud <denis_arnaud - at - users dot sourceforge dot net>")
SET(CPACK_PACKAGE_DEFAULT_LOCATION "/")
SET(CPACK_PACKAGE_DESCRIPTION "C++ Standard Airline IT Library")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "/home/localoriuser/dev/sim/stdair/stdairgit/README")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "stdair aims at providing a clean API, and the corresponding C++ implementation, for the basis of Airline IT Business Object Model (BOM), that is, to be used by several other open source projects, such as RMOL, Air-Sched, Travel-CCM, OpenTREP, etc.")
SET(CPACK_PACKAGE_FILE_NAME "stdair-99.99.99-Linux")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "stdair 99.99.99")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "stdair 99.99.99")
SET(CPACK_PACKAGE_NAME "stdair")
SET(CPACK_PACKAGE_RELOCATABLE "true")
SET(CPACK_PACKAGE_VENDOR "Denis Arnaud")
SET(CPACK_PACKAGE_VERSION "99.99.99")
SET(CPACK_PACKAGE_VERSION_MAJOR "99")
SET(CPACK_PACKAGE_VERSION_MINOR "99")
SET(CPACK_PACKAGE_VERSION_PATCH "1")
SET(CPACK_RESOURCE_FILE_LICENSE "/home/localoriuser/dev/sim/stdair/stdairgit/COPYING")
SET(CPACK_RESOURCE_FILE_README "/home/localoriuser/dev/sim/stdair/stdairgit/README")
SET(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake/Templates/CPack.GenericWelcome.txt")
SET(CPACK_SET_DESTDIR "OFF")
SET(CPACK_SOURCE_CYGWIN "")
SET(CPACK_SOURCE_GENERATOR "TBZ2;TGZ")
SET(CPACK_SOURCE_IGNORE_FILES "/tmp/;/tmp2/;/autom4te\\.cache/;autogen\\.sh$;/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.gitignore$;\\.swp$;\\.#;/#;~$;stdair\\.spec;/build/;\\.gz$;\\.bz2$")
SET(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/home/localoriuser/dev/sim/stdair/stdairgit/CPackSourceConfig.cmake")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "stdair-99.99.99")
SET(CPACK_SOURCE_TBZ2 "")
SET(CPACK_SOURCE_TGZ "")
SET(CPACK_SOURCE_TZ "")
SET(CPACK_SOURCE_ZIP "")
SET(CPACK_SYSTEM_NAME "Linux")
SET(CPACK_TOPLEVEL_TAG "Linux")
