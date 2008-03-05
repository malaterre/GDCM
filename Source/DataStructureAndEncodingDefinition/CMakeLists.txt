# Define the srcs for Data Structure and Encoding Definitions
# DSED
SET(DSED_SRCS
  gdcmTag.cxx
  gdcmFileSet.cxx
  gdcmDataSet.cxx
  gdcmByteSwapFilter.cxx
  gdcmExplicitDataElement.cxx
  gdcmFileMetaInformation.cxx
  gdcmFragment.cxx
  gdcmImplicitDataElement.cxx
  gdcmItem.cxx
  #gdcmParser.cxx
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
  "${GDCM_BINARY_DIR}/Utilities/zlib"

  # src:
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition/"


  "${GDCM_SOURCE_DIR}/Utilities"
 )


ADD_LIBRARY(gdcmDSED ${DSED_SRCS})
TARGET_LINK_LIBRARIES(gdcmDSED gdcmzlib gdcmCommon)
IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS gdcmDSED
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
  )
ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)

IF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
  FILE(GLOB header_files "*.h" "*.txx")
  INSTALL(FILES ${header_files}
    DESTINATION ${GDCM_INSTALL_INCLUDE_DIR} COMPONENT Development
  )
ENDIF(NOT GDCM_INSTALL_NO_DEVELOPMENT)

