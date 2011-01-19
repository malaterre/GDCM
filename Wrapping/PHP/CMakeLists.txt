# Required:
# sudo apt-get install php5-dev
FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/InformationObjectDefinition"
  "${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
)

#FIND_PACKAGE(PHP4 REQUIRED)
FIND_PACKAGE(PHP5 REQUIRED)

INCLUDE_DIRECTORIES(
  ${PHP4_INCLUDE_PATH}
  ${PHP5_INCLUDE_PATH}
)

SET_SOURCE_FILES_PROPERTIES(gdcm.i PROPERTIES CPLUSPLUS ON)

# Some old swig 1.3 did not support this option:
#SET(CMAKE_SWIG_OUTDIR "${CMAKE_CURRENT_BINARY_DIR}")

# swig expect a name like that: php_gdcm.so
SWIG_ADD_MODULE(php_gdcm php gdcm.i)
SWIG_LINK_LIBRARIES(php_gdcm gdcmMSFF)

SET_TARGET_PROPERTIES(${SWIG_MODULE_php_gdcm_REAL_NAME} PROPERTIES LINK_INTERFACE_LIBRARIES "")

# Module are always place in the library destination
# but for poor win32 user I decided to place them
# right next to the other dlls
IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS ${SWIG_MODULE_php_gdcm_REAL_NAME}
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT PHPModule
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT PHPModule
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT PHPModule
  )
  # because gdcm.php is constructed with custom commands, it need the INSTALL(FILES signature:
  INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/gdcm.php
    DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT PHPModule
  )
ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)
