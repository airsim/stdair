# Install script for directory: /home/localoriuser/dev/sim/stdair/stdairgit

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/usr/share/stdair/CMake/stdair-library-depends.cmake")
    FILE(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}/usr/share/stdair/CMake/stdair-library-depends.cmake"
         "/home/localoriuser/dev/sim/stdair/stdairgit/CMakeFiles/Export/_usr/share/stdair/CMake/stdair-library-depends.cmake")
    IF(EXPORT_FILE_CHANGED)
      FILE(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}/usr/share/stdair/CMake/stdair-library-depends-*.cmake")
      IF(OLD_CONFIG_FILES)
        MESSAGE(STATUS "Old export file \"$ENV{DESTDIR}/usr/share/stdair/CMake/stdair-library-depends.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        FILE(REMOVE ${OLD_CONFIG_FILES})
      ENDIF(OLD_CONFIG_FILES)
    ENDIF(EXPORT_FILE_CHANGED)
  ENDIF()
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/share/stdair/CMake/stdair-library-depends.cmake")
FILE(INSTALL DESTINATION "/usr/share/stdair/CMake" TYPE FILE FILES "/home/localoriuser/dev/sim/stdair/stdairgit/CMakeFiles/Export/_usr/share/stdair/CMake/stdair-library-depends.cmake")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
     "/usr/share/stdair/CMake/stdair-library-depends-debug.cmake")
FILE(INSTALL DESTINATION "/usr/share/stdair/CMake" TYPE FILE FILES "/home/localoriuser/dev/sim/stdair/stdairgit/CMakeFiles/Export/_usr/share/stdair/CMake/stdair-library-depends-debug.cmake")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/share/stdair/CMake/stdair-config.cmake;/usr/share/stdair/CMake/stdair-config-version.cmake")
FILE(INSTALL DESTINATION "/usr/share/stdair/CMake" TYPE FILE FILES
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair-config.cmake"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair-config-version.cmake"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "/home/localoriuser/dev/sim/stdair/stdairgit/stdair-config")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/localoriuser/dev/sim/stdair/stdairgit/stdair.pc")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/aclocal" TYPE FILE FILES "/home/localoriuser/dev/sim/stdair/stdairgit/stdair.m4")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/stdair-99.99.99" TYPE FILE FILES
    "/home/localoriuser/dev/sim/stdair/stdairgit/AUTHORS"
    "/home/localoriuser/dev/sim/stdair/stdairgit/NEWS"
    "/home/localoriuser/dev/sim/stdair/stdairgit/README"
    "/home/localoriuser/dev/sim/stdair/stdairgit/INSTALL"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/localoriuser/dev/sim/stdair/stdairgit/stdair/cmake_install.cmake")
  INCLUDE("/home/localoriuser/dev/sim/stdair/stdairgit/doc/cmake_install.cmake")
  INCLUDE("/home/localoriuser/dev/sim/stdair/stdairgit/db/cmake_install.cmake")
  INCLUDE("/home/localoriuser/dev/sim/stdair/stdairgit/samples/cmake_install.cmake")
  INCLUDE("/home/localoriuser/dev/sim/stdair/stdairgit/man/cmake_install.cmake")
  INCLUDE("/home/localoriuser/dev/sim/stdair/stdairgit/test/stdair/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/localoriuser/dev/sim/stdair/stdairgit/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/localoriuser/dev/sim/stdair/stdairgit/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
