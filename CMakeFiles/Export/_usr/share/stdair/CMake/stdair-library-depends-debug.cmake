#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
SET(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "stdairlib" for configuration "Debug"
SET_PROPERTY(TARGET stdairlib APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(stdairlib PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "/usr/lib/libpython2.7.so;/usr/lib/libboost_iostreams-mt.so;/usr/lib/libboost_serialization-mt.so;/usr/lib/libboost_filesystem-mt.so;/usr/lib/libboost_date_time-mt.so;/usr/lib/libzmq.so;/usr/lib/mysql/libmysqlclient.so;/usr/lib/libsoci_core.so;/usr/lib/libsoci_mysql.so"
  IMPORTED_LOCATION_DEBUG "/usr/lib/libstdair.so.99.99.99"
  IMPORTED_SONAME_DEBUG "libstdair.so.99.99"
  )

# Import target "stdairuicllib" for configuration "Debug"
SET_PROPERTY(TARGET stdairuicllib APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(stdairuicllib PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "/usr/lib/libpython2.7.so;/usr/lib/libboost_iostreams-mt.so;/usr/lib/libboost_serialization-mt.so;/usr/lib/libboost_filesystem-mt.so;/usr/lib/libboost_date_time-mt.so;/usr/lib/libzmq.so;/usr/lib/mysql/libmysqlclient.so;/usr/lib/libsoci_core.so;/usr/lib/libsoci_mysql.so"
  IMPORTED_LOCATION_DEBUG "/usr/lib/libstdairuicl.so.99.99.99"
  IMPORTED_SONAME_DEBUG "libstdairuicl.so.99.99"
  )

# Import target "stdairbin" for configuration "Debug"
SET_PROPERTY(TARGET stdairbin APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(stdairbin PROPERTIES
  IMPORTED_LOCATION_DEBUG "/usr/bin/stdair"
  )

# Commands beyond this point should not need to know the version.
SET(CMAKE_IMPORT_FILE_VERSION)
