# Install script for directory: /home/localoriuser/dev/sim/stdair/stdairgit/samples

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/share/stdair/samples/fare01.csv;/usr/share/stdair/samples/yieldstore01.csv;/usr/share/stdair/samples/fareError06.csv;/usr/share/stdair/samples/rm07.csv;/usr/share/stdair/samples/fareError05.csv;/usr/share/stdair/samples/fareError07.csv;/usr/share/stdair/samples/schedule05.csv;/usr/share/stdair/samples/rm01.csv;/usr/share/stdair/samples/schedule01.csv;/usr/share/stdair/samples/schedule03.csv;/usr/share/stdair/samples/rm08.csv;/usr/share/stdair/samples/schedule06.csv;/usr/share/stdair/samples/invdump02.csv;/usr/share/stdair/samples/rm09.csv;/usr/share/stdair/samples/demand01.csv;/usr/share/stdair/samples/schedule04.csv;/usr/share/stdair/samples/fareError02.csv;/usr/share/stdair/samples/rm10.csv;/usr/share/stdair/samples/fareError04.csv;/usr/share/stdair/samples/fareError01.csv;/usr/share/stdair/samples/rm11.csv;/usr/share/stdair/samples/schedule07.csv;/usr/share/stdair/samples/invdump01.csv;/usr/share/stdair/samples/schedule02.csv;/usr/share/stdair/samples/rm03.csv;/usr/share/stdair/samples/rm05.csv;/usr/share/stdair/samples/rm06.csv;/usr/share/stdair/samples/fareError03.csv;/usr/share/stdair/samples/ond01.csv;/usr/share/stdair/samples/rm04.csv;/usr/share/stdair/samples/rm02.csv")
FILE(INSTALL DESTINATION "/usr/share/stdair/samples" TYPE FILE FILES
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/fare01.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/yieldstore01.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/fareError06.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/rm07.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/fareError05.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/fareError07.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/schedule05.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/rm01.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/schedule01.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/schedule03.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/rm08.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/schedule06.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/invdump02.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/rm09.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/demand01.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/schedule04.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/fareError02.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/rm10.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/fareError04.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/fareError01.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/rm11.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/schedule07.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/invdump01.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/schedule02.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/rm03.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/rm05.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/rm06.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/fareError03.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/ond01.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/rm04.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/rm02.csv"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/share/stdair/samples/rds01/schedule.csv;/usr/share/stdair/samples/rds01/demand.csv;/usr/share/stdair/samples/rds01/fare.csv;/usr/share/stdair/samples/rds01/yield.csv")
FILE(INSTALL DESTINATION "/usr/share/stdair/samples/rds01" TYPE FILE FILES
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/rds01/schedule.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/rds01/demand.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/rds01/fare.csv"
    "/home/localoriuser/dev/sim/stdair/stdairgit/samples/rds01/yield.csv"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime")

