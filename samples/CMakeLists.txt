##
# StdAir (CSV) sample files
#
file (GLOB root_samples *.csv)
file (GLOB rds01_samples rds01/*.csv)

# Installation of the CSV sample files
set (SAMPLE_PATH ${CMAKE_INSTALL_PREFIX}/share/${CPACK_PACKAGE_NAME}/samples)
install (FILES ${root_samples} DESTINATION ${SAMPLE_PATH})
install (FILES ${rds01_samples} DESTINATION ${SAMPLE_PATH}/rds01)
