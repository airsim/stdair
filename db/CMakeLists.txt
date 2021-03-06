##
# StdAir database scripts
#

# Define the substitutes for the variables present in the database
# script files. Note that PACKAGE, PACKAGE_NAME and PACKAGE_VERSION
# are defined in the main CMakeLists.txt (of the top root directory).
set (OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set (top_srcdir       ${CMAKE_SOURCE_DIR}        )
set (srcdir           ${CMAKE_CURRENT_SOURCE_DIR})

set (db_admin_DIR     admin)
set (db_data_DIR      data)
set (STDAIR_DB_DATA_DIR
  ${CMAKE_INSTALL_PREFIX}/share/${PACKAGE}/db/${db_data_DIR})

##
# Convert the database admin files (basically, just replace the @<variable>@
# variables).
set (db_admin_sh_SOURCES clean_all_tables.sh clean_a_table.sh
  count_all_tables.sh count_a_table.sh
  create_airinv_db.sh create_airinv_user.sh
  create_tvlsim_db.sh create_tvlsim_user.sh
  dump_airinv_db_structure.sh dump_tvlsim_db_structure.sh
  load_airinv_tvlsim_data.sh load_tvlsim_data.sh)
set (db_admin_sh_in_SOURCES "")
#
foreach (db_admin_sh ${db_admin_sh_SOURCES})
  set (db_admin_sh_in ${db_admin_DIR}/${db_admin_sh}.in)
  configure_file (${db_admin_sh_in} ${CMAKE_CURRENT_BINARY_DIR}/${db_admin_DIR}/${db_admin_sh} @ONLY)
  # Add the non converted script name to the dedicated list
  set (db_admin_sh_in_SOURCES ${db_admin_sh_in_SOURCES} ${db_admin_sh_in})
endforeach()

# Add the 'dbadmin' target, depending on the generated db admin scripts
add_custom_target (dbadmin ALL DEPENDS ${db_admin_sh_in_SOURCES})


##
# Installation of the database scripts
set (DB_ADMIN_PATH libexec/${PACKAGE})
foreach (db_admin_sh ${db_admin_sh_SOURCES})
  install (PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${db_admin_DIR}/${db_admin_sh}
	DESTINATION ${DB_ADMIN_PATH})
endforeach()

# Installation of the database data files (SQL and CSV)
set (DB_DATA_PATH ${CMAKE_INSTALL_PREFIX}/share/${PACKAGE}/db)
install (DIRECTORY ${db_data_DIR} DESTINATION ${DB_DATA_PATH}
  FILES_MATCHING PATTERN "*.sql" PATTERN "*.csv")
