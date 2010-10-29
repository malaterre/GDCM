# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Source/InformationObjectDefinition"

  "${GDCM_BINARY_DIR}/Testing/Source/Data"
  "${GDCM_SOURCE_DIR}/Testing/Source/Data"

  "${GDCM_SOURCE_DIR}/Utilities"
  "${GDCM_SOURCE_DIR}/Utilities/socketxx"
  "${GDCM_SOURCE_DIR}/Utilities/socketxx/socket++" # local.h
  "${GDCM_BINARY_DIR}/Utilities/socketxx/socket++" # config.h
  )

SET(MessageExchangeDefinition_SRCS

  gdcmAAbortPDU.cxx        gdcmAAssociateRJPDU.cxx  gdcmAbstractSyntax.cxx      gdcmAReleaseRPPDU.cxx  
  #gdcmPDataPDU.cxx
  gdcmPresentationContextAC.cxx  gdcmPresentationDataValue.cxx  gdcmUserInformation.cxx
gdcmAAssociateACPDU.cxx  gdcmAAssociateRQPDU.cxx  gdcmApplicationContext.cxx  gdcmAReleaseRQPDU.cxx  gdcmPDataTFPDU.cxx  gdcmPresentationContext.cxx    gdcmTransferSyntax_.cxx
gdcmMaximumLengthSub.cxx
gdcmCommandDataSet.cxx
gdcmImplementationClassUIDSub.cxx
gdcmImplementationUIDSub.cxx
gdcmImplementationVersionNameSub.cxx
gdcmAsynchronousOperationsWindowSub.cxx
gdcmAssociationEstablishment.cxx
gdcmULTransitionTable.cxx
gdcmULActionAA.cxx
gdcmULActionAE.cxx
gdcmULActionAR.cxx
gdcmULActionDT.cxx
gdcmARTIMTimer.cxx
gdcmULConnection.cxx
gdcmULConnectionManager.cxx
gdcmULConnectionInfo.cxx
gdcmPDUFactory.cxx
gdcmCompositeMessageFactory.cxx
gdcmCEchoMessages.cxx
gdcmCFindMessages.cxx
gdcmCStoreMessages.cxx
gdcmCMoveMessages.cxx
gdcmQueryImage.cxx
gdcmQuerySeries.cxx
gdcmQueryStudy.cxx
gdcmQueryPatient.cxx
gdcmPatientRootQuery.cxx
gdcmStudyRootQuery.cxx
gdcmBaseRootQuery.cxx
gdcmQueryFactory.cxx
  )

#ADD_LIBRARY(gdcmMED ${MessageExchangeDefinition_SRCS})
# Let's prefer the 4 letter name: MEXD:
ADD_LIBRARY(gdcmMEXD ${MessageExchangeDefinition_SRCS})
#TARGET_LINK_LIBRARIES(gdcmMEXD gdcmDICT gdcmCommon)
SET_TARGET_PROPERTIES(gdcmMEXD PROPERTIES ${GDCM_LIBRARY_PROPERTIES} LINK_INTERFACE_LIBRARIES "")
if(WIN32)
#target_link_libraries(${SOCKETXX_LIBRARY_NAME} wsock32)
target_link_libraries(gdcmMEXD gdcmDICT gdcmDSED gdcmIOD socketxx ws2_32.lib)
else (WIN32)
TARGET_LINK_LIBRARIES(gdcmMEXD gdcmDICT gdcmDSED gdcmIOD socketxx)
endif(WIN32)
