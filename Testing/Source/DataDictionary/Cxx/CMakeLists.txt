# Define the tests for Data Dictionary
# DICT
SET(DICT_TEST_SRCS
  TestDictEntry
  TestDict
  TestGlobal
  TestDicts
  TestGroupDict
  TestTagToType
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  )

CREATE_TEST_SOURCELIST(DICTTests gdcmDICTTests.cxx ${DICT_TEST_SRCS})
ADD_EXECUTABLE(gdcmDICTTests ${DICTTests})
TARGET_LINK_LIBRARIES(gdcmDICTTests gdcmDICT)

#Don't understand why I need that ??
SET(GDCM_DICT_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmDICTTests")

# Loop over files and create executables
FOREACH(name ${DICT_TEST_SRCS})
  ADD_TEST(${name} ${GDCM_DICT_TESTS} ${name})
ENDFOREACH(name)


