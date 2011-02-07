# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Source/InformationObjectDefinition"
  "${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat"

  "${GDCM_BINARY_DIR}/Testing/Source/Data"
  "${GDCM_SOURCE_DIR}/Testing/Source/Data"

  "${GDCM_SOURCE_DIR}/Utilities"
  "${GDCM_SOURCE_DIR}/Utilities/socketxx"
  "${GDCM_SOURCE_DIR}/Utilities/socketxx/socket++" # local.h
  "${GDCM_BINARY_DIR}/Utilities/socketxx/socket++" # config.h
  )

SET(MessageExchangeDefinition_SRCS
  gdcmAAbortPDU.cxx
  gdcmAAssociateACPDU.cxx
  gdcmAAssociateRJPDU.cxx
  gdcmAAssociateRQPDU.cxx
  gdcmARTIMTimer.cxx
  gdcmAReleaseRPPDU.cxx
  gdcmAReleaseRQPDU.cxx
  gdcmAbstractSyntax.cxx
  gdcmApplicationContext.cxx
  gdcmAsynchronousOperationsWindowSub.cxx
  gdcmBaseRootQuery.cxx
  gdcmCEchoMessages.cxx
  gdcmCFindMessages.cxx
  gdcmCMoveMessages.cxx
  gdcmCStoreMessages.cxx
  gdcmCommandDataSet.cxx
  gdcmCompositeMessageFactory.cxx
  gdcmCompositeNetworkFunctions.cxx
  gdcmImplementationClassUIDSub.cxx
  gdcmImplementationUIDSub.cxx
  gdcmImplementationVersionNameSub.cxx
  gdcmMaximumLengthSub.cxx
  gdcmPDUFactory.cxx
  gdcmPDataTFPDU.cxx
  gdcmPatientRootQuery.cxx
  gdcmPresentationContext.cxx
  gdcmPresentationContextAC.cxx
  gdcmPresentationDataValue.cxx
  gdcmQueryFactory.cxx
  gdcmQueryImage.cxx
  gdcmQueryPatient.cxx
  gdcmQuerySeries.cxx
  gdcmQueryStudy.cxx
  gdcmServiceClassUser.cxx
  gdcmStudyRootQuery.cxx
  gdcmTransferSyntaxSub.cxx
  gdcmULActionAA.cxx
  gdcmULActionAE.cxx
  gdcmULActionAR.cxx
  gdcmULActionDT.cxx
  gdcmULBasicCallback.cxx
  gdcmULConnection.cxx
  gdcmULConnectionInfo.cxx
  gdcmULConnectionManager.cxx
  gdcmULTransitionTable.cxx
  gdcmULWritingCallback.cxx
  gdcmUserInformation.cxx
  )

ADD_LIBRARY(gdcmMEXD ${MessageExchangeDefinition_SRCS})
TARGET_LINK_LIBRARIES(gdcmMEXD gdcmMSFF gdcmDICT gdcmDSED gdcmIOD socketxx)
SET_TARGET_PROPERTIES(gdcmMEXD PROPERTIES ${GDCM_LIBRARY_PROPERTIES} LINK_INTERFACE_LIBRARIES "")
if(WIN32)
  target_link_libraries(ws2_32.lib)
endif(WIN32)

# libs
install_library(gdcmMEXD)
# PDB
install_pdb(gdcmMEXD)
# include files
install_includes("*.h")
