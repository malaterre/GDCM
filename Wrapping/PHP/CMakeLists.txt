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
set_property(TARGET ${SWIG_MODULE_php_gdcm_REAL_NAME} PROPERTY NO_SONAME 1)

SET_TARGET_PROPERTIES(${SWIG_MODULE_php_gdcm_REAL_NAME} PROPERTIES LINK_INTERFACE_LIBRARIES "")
# Remove 'lib' prefix :no-op on windows and valid for UNIX based syste
SET_TARGET_PROPERTIES(${SWIG_MODULE_php_gdcm_REAL_NAME} PROPERTIES PREFIX "")

# For some reason the php glue module name is odd using swig 1.3.40, it is php_gdcm on windows
# while simply gdcm on other unix system:
# ...
#    if (!dl('php_gdcm.dll')) return;
#  } else {
#    // PHP_SHLIB_SUFFIX gives 'dylib' on MacOS X but modules are 'so'.
#    if (PHP_SHLIB_SUFFIX === 'dylib') {
#      if (!dl('gdcm.so')) return;
#    } else {
#      if (!dl('gdcm.'.PHP_SHLIB_SUFFIX)) return;
# ...
IF(UNIX)
  SET_TARGET_PROPERTIES(${SWIG_MODULE_php_gdcm_REAL_NAME} PROPERTIES OUTPUT_NAME "gdcm")
ENDIF(UNIX)

# See gdcm bug #3175803
# This is fixed in SWIG 2.0.2:
# http://sourceforge.net/tracker/?func=detail&atid=101645&aid=3166423&group_id=1645
if(${SWIG_VERSION} LESS 2.0.2)
  add_custom_command(TARGET ${SWIG_MODULE_php_gdcm_REAL_NAME}
    PRE_BUILD
    COMMAND sed -i -e 's/zend_error_noreturn/zend_error/g' "${swig_generated_file_fullname}"
    COMMENT "Patching zend_error_noreturn into zend_error"
  )
endif()

# Let's copy gdcm.php into the bin dir:
ADD_CUSTOM_COMMAND(
  OUTPUT ${LIBRARY_OUTPUT_PATH}/gdcm.php
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/gdcm.php ${LIBRARY_OUTPUT_PATH}/gdcm.php
  DEPENDS "${swig_generated_file_fullname}"
  COMMENT "copying gdcm.php"
)
ADD_CUSTOM_TARGET(GDCMPHP ALL
  DEPENDS ${LIBRARY_OUTPUT_PATH}/gdcm.php
  COMMENT "building gdcm.php"
)

# Module are always place in the library destination
# but for poor win32 user I decided to place them
# right next to the other dlls
IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  install_swig_module(php_gdcm PHP)
  # because gdcm.php is constructed with custom commands, it need the INSTALL(FILES signature:
  INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/gdcm.php
    DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT PHPModule
  )
ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)
