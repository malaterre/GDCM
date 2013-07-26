# Define the tests for Data Dictionary
# DICT
SET(DICT_TEST_SRCS
  TestDictEntry
  TestDict
  TestGlobal
  TestUIDs
  TestDicts
  TestGroupDict
  TestTagToType
  TestSOPClassUIDToIOD
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Source/InformationObjectDefinition"
  )

CREATE_TEST_SOURCELIST(DICTTests gdcmDICTTests.cxx ${DICT_TEST_SRCS}
  EXTRA_INCLUDE gdcmTestDriver.h
  )
ADD_EXECUTABLE(gdcmDICTTests ${DICTTests})
TARGET_LINK_LIBRARIES(gdcmDICTTests gdcmDICT gdcmMSFF)

#Don't understand why I need that ??
SET(GDCM_DICT_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmDICTTests")

# Loop over files and create executables
FOREACH(name ${DICT_TEST_SRCS})
if(CMAKE_CROSSCOMPILING)
  ADD_TEST(${name} ${TARGET_SYSTEM_EMULATOR} ${GDCM_DICT_TESTS}${CMAKE_EXECUTABLE_SUFFIX} ${name})
else()
  ADD_TEST(${name} ${GDCM_DICT_TESTS} ${name})
endif()
ENDFOREACH(name)
