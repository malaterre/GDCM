# Required:
# sudo apt-get install libperl-dev

# http://www.swig.org/Doc2.0/Perl5.html
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

FIND_PACKAGE(PerlLibs REQUIRED)
INCLUDE_DIRECTORIES(
  ${PERL_INCLUDE_PATH}
)

SET_SOURCE_FILES_PROPERTIES(gdcm.i PROPERTIES CPLUSPLUS ON)

# TODO check convetion for perl module name:
SWIG_ADD_MODULE(perl_gdcm perl gdcm.i)
SWIG_LINK_LIBRARIES(perl_gdcm gdcmMSFF)

#SET_TARGET_PROPERTIES(${SWIG_MODULE_perl_gdcm_REAL_NAME} PROPERTIES LINK_INTERFACE_LIBRARIES "")
# Remove 'lib' prefix :no-op on windows and valid for UNIX based syste
SET_TARGET_PROPERTIES(${SWIG_MODULE_perl_gdcm_REAL_NAME} PROPERTIES PREFIX "")

IF(UNIX)
  SET_TARGET_PROPERTIES(${SWIG_MODULE_perl_gdcm_REAL_NAME} PROPERTIES OUTPUT_NAME "gdcm")
ENDIF(UNIX)


# Let's copy gdcm.pm into the bin dir:
#ADD_CUSTOM_COMMAND(
#  OUTPUT ${LIBRARY_OUTPUT_PATH}/gdcm.pm
#  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/gdcm.php ${LIBRARY_OUTPUT_PATH}/gdcm.pm
#  DEPENDS "${swig_generated_file_fullname}"
#  COMMENT "copying gdcm.pm"
#)
#ADD_CUSTOM_TARGET(GDCMPERL ALL
#  DEPENDS ${LIBRARY_OUTPUT_PATH}/gdcm.pm
#  COMMENT "building gdcm.pm"
#)

# Module are always place in the library destination
# but for poor win32 user I decided to place them
# right next to the other dlls
IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  install_swig_module(perl_gdcm Perl)
  # because gdcm.pm is constructed with custom commands, it need the INSTALL(FILES signature:
  INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/gdcm.pm
    DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT PerlModule
  )
ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)
