SET(MEXD_TEST_SRCS
TestAAbortPDU.cxx
TestAAssociateACPDU.cxx
TestAAssociateRJPDU.cxx
TestAAssociateRQPDU.cxx
TestAbstractSyntax.cxx
TestApplicationContext.cxx
TestAReleaseRPPDU.cxx
TestAReleaseRQPDU.cxx
TestARTIMTimer.cxx
TestAssociationEstablishment.cxx
TestAsynchronousOperationsWindowSub.cxx
TestBaseCompositeMessage.cxx
TestBasePDU.cxx
TestBaseRootQuery.cxx
TestCEchoMessages.cxx
TestCFindMessages.cxx
TestCMoveMessages.cxx
TestCommandDataSet.cxx
TestCompositeMessageFactory.cxx
TestCStoreMessages.cxx
#TestDIMSE.cxx
TestImplementationClassUIDSub.cxx
TestImplementationUIDSub.cxx
TestImplementationVersionNameSub.cxx
TestMaximumLengthSub.cxx
TestNetworkEvents.cxx
TestNetworkStateID.cxx
TestPatientRootQuery.cxx
#TestPDataPDU.cxx
TestPDataTFPDU.cxx
TestPDUFactory.cxx
TestPresentationContextAC.cxx
TestPresentationContext.cxx
TestPresentationDataValue.cxx
TestQueryBase.cxx
TestQueryFactory.cxx
TestQueryImage.cxx
TestQueryPatient.cxx
TestQuerySeries.cxx
TestQueryStudy.cxx
TestStudyRootQuery.cxx
TestTransferSyntaxSub.cxx
TestULActionAA.cxx
TestULActionAE.cxx
TestULActionAR.cxx
TestULActionDT.cxx
TestULAction.cxx
TestULConnection.cxx
TestULConnectionInfo.cxx
TestULConnectionManager.cxx
TestULEvent.cxx
TestULTransitionTable.cxx
TestUserInformation.cxx
)

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Testing/Source/Data"
  "${GDCM_BINARY_DIR}/Testing/Source/Data"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat"
  "${GDCM_SOURCE_DIR}/Source/MessageExchangeDefinition"
  )

CREATE_TEST_SOURCELIST(MEXDTests gdcmMEXDTests.cxx ${MEXD_TEST_SRCS}
  EXTRA_INCLUDE gdcmTestDriver.h
  )
ADD_EXECUTABLE(gdcmMEXDTests ${MEXDTests})
TARGET_LINK_LIBRARIES(gdcmMEXDTests gdcmMEXD)

#Don't understand why I need that ??
SET(GDCM_MEXD_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmMEXDTests")

# Loop over files and create executables
FOREACH(name ${MEXD_TEST_SRCS})
  ADD_TEST(${name} ${GDCM_MEXD_TESTS} ${name})
ENDFOREACH(name)
