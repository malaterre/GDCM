### Build the configuration file for external projects using GDCM and cmake:
CONFIGURE_FILE( GDCMConfig.cmake.in
  ${GDCM_BINARY_DIR}/GDCMConfig.cmake
  @ONLY
)
INSTALL( FILES ${GDCM_BINARY_DIR}/GDCMConfig.cmake
  DESTINATION ${GDCM_INSTALL_PACKAGE_DIR}
)
CONFIGURE_FILE( GDCMConfigVersion.cmake.in
  ${GDCM_BINARY_DIR}/GDCMConfigVersion.cmake
  @ONLY
)
INSTALL( FILES ${GDCM_BINARY_DIR}/GDCMConfigVersion.cmake
  DESTINATION ${GDCM_INSTALL_PACKAGE_DIR}
)
CONFIGURE_FILE( UseGDCM.cmake.in
  ${GDCM_BINARY_DIR}/UseGDCM.cmake
  @ONLY
)
INSTALL( FILES ${GDCM_BINARY_DIR}/UseGDCM.cmake
  DESTINATION ${GDCM_INSTALL_PACKAGE_DIR}
)

# install all target referenced as GDCMTargets
install(EXPORT GDCMTargets DESTINATION ${GDCM_INSTALL_PACKAGE_DIR})
#get_target_property(VAR target property)
#export(TARGETS ${GDCM_LIBRARIES} FILE ${GDCM_BINARY_DIR}/GDCMExports.cmake)
file(WRITE ${GDCM_BINARY_DIR}/GDCMExports.cmake "")

#message( ${GDCM_EXECUTABLES} )
SET( targets ${GDCM_LIBRARIES} ${GDCM_EXECUTABLES} )

foreach(target ${targets})
  export(TARGETS ${target} APPEND FILE ${GDCM_BINARY_DIR}/GDCMExports.cmake)
endforeach(target)


# Ref:
# http://cmake.org/Bug/view.php?id=9822
# 0009822: Please expose: cmGlobalGenerator::GetExportSet at cmake level 

