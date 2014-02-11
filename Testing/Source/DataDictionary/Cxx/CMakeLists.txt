# Define the tests for Data Dictionary
# DICT
set(DICT_TEST_SRCS
  TestDictEntry
  TestDict
  TestGlobal
  TestUIDs
  TestDicts
  TestGroupDict
  TestTagToType
  TestSOPClassUIDToIOD
  TestTagKeywords
  )

# Add the include paths
include_directories(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Source/InformationObjectDefinition"
  )

create_test_sourcelist(DICTTests gdcmDICTTests.cxx ${DICT_TEST_SRCS}
  EXTRA_INCLUDE gdcmTestDriver.h
  )
add_executable(gdcmDICTTests ${DICTTests})
target_link_libraries(gdcmDICTTests gdcmDICT gdcmMSFF)

#Don't understand why I need that ??
set(GDCM_DICT_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmDICTTests")

# Loop over files and create executables
foreach(name ${DICT_TEST_SRCS})
if(CMAKE_CROSSCOMPILING)
  add_test(${name} ${TARGET_SYSTEM_EMULATOR} ${GDCM_DICT_TESTS}${CMAKE_EXECUTABLE_SUFFIX} ${name})
else()
  add_test(${name} ${GDCM_DICT_TESTS} ${name})
endif()
endforeach()
