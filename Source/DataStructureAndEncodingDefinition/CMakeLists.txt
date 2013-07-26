# Define the srcs for Data Structure and Encoding Definitions
# DSED
SET(DSED_SRCS
  gdcmTag.cxx
  gdcmTagToVR.cxx
  gdcmPrivateTag.cxx
  gdcmCodeString.cxx
  gdcmByteValue.cxx
  gdcmValue.cxx
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
  gdcmPDBHeader.cxx
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
# zlib stuff are actually included (template) so we need to link them here.
TARGET_LINK_LIBRARIES(gdcmDSED ${GDCM_ZLIB_LIBRARIES})
SET_TARGET_PROPERTIES(gdcmDSED PROPERTIES ${GDCM_LIBRARY_PROPERTIES} LINK_INTERFACE_LIBRARIES "gdcmCommon")

# libs
install_library(gdcmDSED)
# PDB
install_pdb(gdcmDSED)
# include files
install_includes("*.h" "*.txx")
