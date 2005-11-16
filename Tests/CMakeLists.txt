# Define the tests
SET(TEST_SRCS
  TestTag
  TestFileIO
  TestFileChunk
  TestTagIO
  TestDataElement
  TestVRValueLength
  TestVR
  #TestSwap
  TestGroup
  #TestValueField
  TestVM
  TestTS
  TestDictEntry
  TestDict
  TestDataSet
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source"
  "${GDCM_SOURCE_DIR}/Source"
  )

CREATE_TEST_SOURCELIST(Tests gdcmTests.cxx ${TEST_SRCS})
ADD_EXECUTABLE(gdcmTests ${Tests})
TARGET_LINK_LIBRARIES(gdcmTests gdcm)

#Don't understand why I need that ??
SET(GDCM_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmTests")

# Loop over files and create executables
FOREACH(name ${TEST_SRCS})
  ADD_TEST(${name} ${GDCM_TESTS} ${name})
ENDFOREACH(name)

