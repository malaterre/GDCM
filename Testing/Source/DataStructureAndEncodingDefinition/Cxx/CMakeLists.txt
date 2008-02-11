# Define the tests for Data Structure and Encoding Definitions
# DSED
SET(DSED_TEST_SRCS
	TestAttribute
	#TestAttributeWriteFile
  #TestReadPatientName
  TestByteBuffer
  #TestByteValue
  TestComposite
  #TestDataElement
  TestDataSet
  TestElement
  #TestExplicitDataElement
  TestFileMetaInformation
  TestFile
  TestFileSet
  TestFragment
  #TestImplicitDataElement
  #TestItem
  TestParser
  TestRLECodec
  TestSequenceOfFragments
  TestSequenceOfItems
  #TestTag
  TestTransferSyntax
  TestMediaStorage
  TestVL
  TestVM
  TestVR
  #TestValue
  #TestTorture
  TestElement2
  TestElement4
  TestElement5
  )

OPTION(SHARED_PTR "shared_ptr" OFF)
MARK_AS_ADVANCED(SHARED_PTR)
IF(SHARED_PTR)
  SET(DSED_TEST_SRCS
    ${DSED_TEST_SRCS}
    TestCopyValue
    )
ENDIF(SHARED_PTR)

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  )

CREATE_TEST_SOURCELIST(DSEDTests gdcmDSEDTests.cxx ${DSED_TEST_SRCS})
ADD_EXECUTABLE(gdcmDSEDTests ${DSEDTests})
TARGET_LINK_LIBRARIES(gdcmDSEDTests gdcmDSED)

#Don't understand why I need that ??
SET(GDCM_DSED_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmDSEDTests")

# Loop over files and create executables
FOREACH(name ${DSED_TEST_SRCS})
  ADD_TEST(${name} ${GDCM_DSED_TESTS} ${name})
ENDFOREACH(name)

# FIXME
#ADD_EXECUTABLE(TestAttribute TestAttribute.cxx)
#ADD_EXECUTABLE(TestAttribute2 TestAttribute2.cxx)
ADD_EXECUTABLE(TestAttribute3 TestAttribute3.cxx)
TARGET_LINK_LIBRARIES(TestAttribute3 gdcmDSED)
#ADD_EXECUTABLE(TestElement3 TestElement3.cxx)

ADD_EXECUTABLE(TestAttribute5 TestAttribute5.cxx)
TARGET_LINK_LIBRARIES(TestAttribute5 gdcmDSED)

