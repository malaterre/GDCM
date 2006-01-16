# Define the tests
SET(TEST_SRCS
  #TestCompressor
  TestAttributeFactory
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Parser"
  "${GDCM_BINARY_DIR}/Source/Parser"
  "${GDCM_SOURCE_DIR}/Source/Objects"
  "${GDCM_SOURCE_DIR}/Utilities"
  "${GDCM_BINARY_DIR}/Tests/Objects"
  )

CREATE_TEST_SOURCELIST(ObjectsTests gdcmObjectsTests.cxx ${TEST_SRCS})
ADD_EXECUTABLE(gdcmObjectsTests ${ObjectsTests})
TARGET_LINK_LIBRARIES(gdcmObjectsTests gdcmParser)

#Don't understand why I need that ??
SET(GDCM_TABLES_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmObjectsTests")

# Loop over files and create executables
FOREACH(name ${TEST_SRCS})
  ADD_TEST(${name} ${GDCM_TABLES_TESTS} ${name})
ENDFOREACH(name)


