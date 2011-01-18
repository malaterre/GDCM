# Define the tests for Information Object Definition
# IOD
SET(IOD_TEST_SRCS
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
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Source/InformationObjectDefinition"
  "${GDCM_BINARY_DIR}/Source/InformationObjectDefinition" # gdcmTables.h
  )

CREATE_TEST_SOURCELIST(IODTests gdcmIODTests.cxx ${IOD_TEST_SRCS}
  EXTRA_INCLUDE gdcmTestDriver.h
  )
ADD_EXECUTABLE(gdcmIODTests ${IODTests})
TARGET_LINK_LIBRARIES(gdcmIODTests gdcmIOD gdcmMSFF)

#Don't understand why I need that ??
SET(GDCM_IOD_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmIODTests")

# Loop over files and create executables
FOREACH(name ${IOD_TEST_SRCS})
  ADD_TEST(${name} ${GDCM_IOD_TESTS} ${name})
ENDFOREACH(name)
