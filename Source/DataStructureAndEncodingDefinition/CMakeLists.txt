# Define the srcs for Data Structure and Encoding Definitions
# DSED
SET(DSED_SRCS
  gdcmTag.cxx
  gdcmByteValue.cxx
  gdcmFileSet.cxx
  gdcmDataSet.cxx
  gdcmByteSwapFilter.cxx
  gdcmUNExplicitImplicitDataElement.cxx
  gdcmExplicitDataElement.cxx
  gdcmFileMetaInformation.cxx
  gdcmFragment.cxx
  gdcmImplicitDataElement.cxx
  gdcmItem.cxx
  gdcmReader.cxx
  gdcmWriter.cxx
  #gdcmParser.cxx
  gdcmCSAHeader.cxx
  gdcmSequenceOfFragments.cxx
  gdcmSequenceOfItems.cxx
  gdcmTransferSyntax.cxx
  gdcmMediaStorage.cxx
  gdcmVM.cxx
  gdcmVR.cxx
  gdcmFile.cxx
  gdcmPreamble.cxx
  gdcmParseException.cxx
  gdcmDataElement.cxx
  gdcmUNExplicitDataElement.cxx
  gdcmCP246ExplicitDataElement.cxx
  gdcmExplicitImplicitDataElement.cxx
  gdcmVR16ExplicitDataElement.cxx
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  # Bin:
  "${GDCM_BINARY_DIR}/Source/Common"

  # src:
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition/"


  "${GDCM_SOURCE_DIR}/Utilities"
 )
IF(NOT GDCM_USE_SYSTEM_ZLIB)
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Utilities/gdcmzlib"
)
ENDIF(NOT GDCM_USE_SYSTEM_ZLIB)


ADD_LIBRARY(gdcmDSED ${DSED_SRCS})
TARGET_LINK_LIBRARIES(gdcmDSED gdcmCommon)
SET_TARGET_PROPERTIES(gdcmDSED PROPERTIES ${GDCM_LIBRARY_PROPERTIES})
IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  # Runtime
  INSTALL(TARGETS gdcmDSED
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime ${NAMELINK_SKIP}
  )
  #Development
  INSTALL(TARGETS gdcmDSED
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development ${NAMELINK_ONLY}
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
  )
ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)

IF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
  FILE(GLOB header_files "*.h" "*.txx")
  INSTALL(FILES ${header_files}
    DESTINATION ${GDCM_INSTALL_INCLUDE_DIR} COMPONENT Development
  )
ENDIF(NOT GDCM_INSTALL_NO_DEVELOPMENT)

