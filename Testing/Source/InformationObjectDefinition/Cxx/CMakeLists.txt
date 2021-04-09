# Define the tests for Information Object Definition
# IOD
set(IOD_TEST_SRCS
  TestTableReader.cxx
  TestTable.cxx
  TestTableEntry.cxx
  TestType.cxx
  TestModule.cxx
  TestModules.cxx
  TestModuleEntry.cxx
  TestNestedModuleEntries.cxx
  TestIODEntry.cxx
  TestIOD.cxx
  TestIODs.cxx
  TestDefs.cxx
  TestPatient.cxx
  TestSeries.cxx
  TestStudy.cxx
  TestDefinedTerms.cxx
  TestEnumeratedValues.cxx
  TestUsage.cxx
  #TestXMLDictReader.cxx
  #TestXMLPrivateDictReader.cxx
  )

# Add the include paths
include_directories(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Source/InformationObjectDefinition"
  "${GDCM_BINARY_DIR}/Source/InformationObjectDefinition" # gdcmTables.h
  )

create_test_sourcelist(IODTests gdcmIODTests.cxx ${IOD_TEST_SRCS}
  EXTRA_INCLUDE gdcmTestDriver.h
  )
add_executable(gdcmIODTests ${IODTests})
target_link_libraries(gdcmIODTests gdcmIOD gdcmMSFF)

# Loop over files and create executables
foreach(name ${IOD_TEST_SRCS})
  get_filename_component(testname ${name} NAME_WE)
  add_test(NAME ${testname} COMMAND gdcmIODTests ${testname})
endforeach()
