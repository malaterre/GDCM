# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"

  "${GDCM_BINARY_DIR}/Testing/Source/Data"
  "${GDCM_SOURCE_DIR}/Testing/Source/Data"

  "${GDCM_SOURCE_DIR}/Utilities"
  )

SET(MessageExchangeDefinition_SRCS
  gdcmAAbortPDU.cxx  gdcmAAssociateACPDU.cxx  gdcmAAssociateRJPDU.cxx  gdcmAAssociateRQPDU.cxx  gdcmAReleaseRPPDU.cxx  gdcmAReleaseRQPDU.cxx  gdcmPDataPDU.cxx

  )

#ADD_LIBRARY(gdcmMED ${MessageExchangeDefinition_SRCS})
# Let's prefer the 4 letter name: MEXD:
ADD_LIBRARY(gdcmMEXD ${MessageExchangeDefinition_SRCS})
SET_TARGET_PROPERTIES(gdcmMEXD PROPERTIES ${GDCM_LIBRARY_PROPERTIES} LINK_INTERFACE_LIBRARIES "")

