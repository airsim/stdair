##
# StdAir (CSV) sample files
#
file (GLOB root_samples RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.csv)
file (GLOB rds01_samples RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} rds01/*.csv)
file (GLOB ibp_samples RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} IBP_study/*.csv)
file (GLOB NewQFF_instance01_samples RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
NewQFF/instance01/*.csv)
file (GLOB NewQFF_instance02_samples RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
NewQFF/instance02/*.csv)
file (GLOB OldQFF_instance01_samples RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
OldQFF/instance01/*.csv)
file (GLOB OldQFF_instance02_samples RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
OldQFF/instance02/*.csv)
file (GLOB QForecasting_samples RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
QForecasting/*.csv)
file (GLOB HybridForecasting_samples RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
HybridForecasting/*.csv)

# Installation of the CSV sample files
install (FILES ${root_samples} DESTINATION ${INSTALL_SAMPLE_DIR}
  COMPONENT runtime)
install (FILES ${rds01_samples} DESTINATION ${INSTALL_SAMPLE_DIR}/rds01
  COMPONENT runtime)
install (FILES ${ibp_samples} DESTINATION ${INSTALL_SAMPLE_DIR}/IBP_study
  COMPONENT runtime)
install (FILES ${NewQFF_instance01_samples} DESTINATION 
${INSTALL_SAMPLE_DIR}/NewQFF/instance01 COMPONENT runtime)
install (FILES ${NewQFF_instance02_samples} DESTINATION 
${INSTALL_SAMPLE_DIR}/NewQFF/instance02 COMPONENT runtime)
install (FILES ${OldQFF_instance01_samples} DESTINATION 
${INSTALL_SAMPLE_DIR}/OldQFF/instance01 COMPONENT runtime)
install (FILES ${OldQFF_instance02_samples} DESTINATION 
${INSTALL_SAMPLE_DIR}/OldQFF/instance02 COMPONENT runtime)
install (FILES ${QForecasting_samples} DESTINATION 
${INSTALL_SAMPLE_DIR}/QForecasting COMPONENT runtime)
install (FILES ${HybridForecasting_samples} DESTINATION 
${INSTALL_SAMPLE_DIR}/HybridForecasting COMPONENT runtime)
