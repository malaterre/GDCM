# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"

  "${GDCM_BINARY_DIR}/Testing/Source/Data"
  "${GDCM_SOURCE_DIR}/Testing/Source/Data"

  "${GDCM_SOURCE_DIR}/Utilities"
  )

SET(MessageExchangeDefinition_SRCS

  gdcmAAbortPDU.cxx        gdcmAAssociateRJPDU.cxx  gdcmAbstractSyntax.cxx      gdcmAReleaseRPPDU.cxx  gdcmPDataPDU.cxx    gdcmPresentationContextAC.cxx  gdcmPresentationDataValue.cxx  gdcmUserInformation.cxx
gdcmAAssociateACPDU.cxx  gdcmAAssociateRQPDU.cxx  gdcmApplicationContext.cxx  gdcmAReleaseRQPDU.cxx  gdcmPDataTFPDU.cxx  gdcmPresentationContext.cxx    gdcmTransferSyntax_.cxx
gdcmMaximumLengthSub.cxx
  )

#ADD_LIBRARY(gdcmMED ${MessageExchangeDefinition_SRCS})
# Let's prefer the 4 letter name: MEXD:
ADD_LIBRARY(gdcmMEXD ${MessageExchangeDefinition_SRCS})
TARGET_LINK_LIBRARIES(gdcmMEXD gdcmDICT)
SET_TARGET_PROPERTIES(gdcmMEXD PROPERTIES ${GDCM_LIBRARY_PROPERTIES} LINK_INTERFACE_LIBRARIES "")

