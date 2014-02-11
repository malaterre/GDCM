# Define the tests for Information Object Definition
# IOD
set(IOD_TEST_SRCS
  TestTableReader
  TestTable
  TestTableEntry
  TestType
  TestModule
  TestModules
  TestModuleEntry
  TestNestedModuleEntries
  TestIODEntry
  TestIOD
  TestIODs
  TestDefs
  TestPatient
  TestSeries
  TestStudy
  TestDefinedTerms
  TestEnumeratedValues
  TestUsage
  #TestXMLDictReader
  #TestXMLPrivateDictReader
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

#Don't understand why I need that ??
set(GDCM_IOD_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmIODTests")

# Loop over files and create executables
foreach(name ${IOD_TEST_SRCS})
  if(CMAKE_CROSSCOMPILING)
    add_test(${name} ${TARGET_SYSTEM_EMULATOR} ${GDCM_IOD_TESTS}${CMAKE_EXECUTABLE_SUFFIX} ${name})
  else()
    add_test(${name} ${GDCM_IOD_TESTS} ${name})
  endif()
endforeach()
