##
# StdAir (CSV) sample files
#
file (GLOB root_samples RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.csv)
file (GLOB rds01_samples RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} rds01/*.csv)

# Installation of the CSV sample files
install (FILES ${root_samples} DESTINATION ${INSTALL_SAMPLE_DIR}
  COMPONENT runtime)
install (FILES ${rds01_samples} DESTINATION ${INSTALL_SAMPLE_DIR}/rds01
  COMPONENT runtime)
