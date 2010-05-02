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

# install all targets referenced as GDCMTargets
install(EXPORT GDCMTargets DESTINATION ${GDCM_INSTALL_PACKAGE_DIR})

# [Prevent viral CMake dep]
# See the following ref, which explain this mess.
# http://cmake.org/Bug/view.php?id=9822
# 0009822: Please expose: cmGlobalGenerator::GetExportSet at cmake level 

# I cannot retrieve the lists of exported targets, so read them from the file instead
SET( targets )

set(gdcmtarget_cmake
  "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/Export/${GDCM_INSTALL_PACKAGE_DIR}/GDCMTargets.cmake")
if(EXISTS ${gdcmtarget_cmake})
  file(READ ${gdcmtarget_cmake} ENT)
  STRING(REGEX REPLACE "\r?\n" ";" ENT "${ENT}")
  foreach(line ${ENT})
    string(REGEX MATCH "ADD_LIBRARY\\(.*SHARED IMPORTED\\)" m ${line})
    if( m )
      string(REGEX REPLACE "ADD_LIBRARY\\((.*) SHARED IMPORTED\\)" "\\1" out ${m})
      list(APPEND targets ${out})
    endif()
  endforeach(line)
endif()

foreach(target ${targets})
  export(TARGETS ${target} APPEND FILE ${GDCM_BINARY_DIR}/GDCMExports.cmake)
endforeach(target)

