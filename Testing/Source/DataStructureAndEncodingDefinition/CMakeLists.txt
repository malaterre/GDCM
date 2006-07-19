# Define the tests for Data Structure and Encoding Definitions
# DSED
SET(DSED_TEST_SRCS
  TestTag
  TestDataElement
  TestExplicitDataElement
  TestImplicitDataElement
  TestComposite
  TestElement
  TestVR
  TestVM
  TestDataSet
  TestItem
  TestValue
  TestVL
  #TestReadPatientName
  TestParser
  TestByteBuffer
  TestByteValue
  TestReader
  TestSequenceOfFragments
  TestSequenceOfItems
  TestCopyDataSet
  TestImageReader
  TestJPEGCodec
  TestRLECodec
  TestWriter
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
  "${GDCM_SOURCE_DIR}/Testing/Source/Data"
  "${GDCM_BINARY_DIR}/Testing/Source/Data"
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



