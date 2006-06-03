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
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
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


