# Define the tests for Data Dictionary
# DICT
set(DICT_TEST_SRCS
  TestDictEntry.cxx
  TestDict.cxx
  TestGlobal.cxx
  TestUIDs.cxx
  TestDicts.cxx
  TestGroupDict.cxx
  TestTagToType.cxx
  TestSOPClassUIDToIOD.cxx
  TestTagKeywords.cxx
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

# Loop over files and create executables
foreach(name ${DICT_TEST_SRCS})
  get_filename_component(testname ${name} NAME_WE)
  add_test(NAME ${testname} COMMAND gdcmDICTTests ${testname})
endforeach()
