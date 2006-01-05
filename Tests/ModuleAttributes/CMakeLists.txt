# Define the tests
SET(TEST_SRCS
  TestTableReader
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Parser"
  "${GDCM_SOURCE_DIR}/Source/ModuleAttributes"
  "${GDCM_BINARY_DIR}/Source/ModuleAttributes"
  "${GDCM_SOURCE_DIR}/Utilities"
  "${GDCM_BINARY_DIR}/Tests/ModuleAttributes"
  )

CREATE_TEST_SOURCELIST(TablesTests gdcmTablesTests.cxx ${TEST_SRCS})
ADD_EXECUTABLE(gdcmTablesTests ${TablesTests})
TARGET_LINK_LIBRARIES(gdcmTablesTests gdcmModuleAttributes)

#Don't understand why I need that ??
SET(GDCM_TABLES_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmTablesTests")

# Loop over files and create executables
FOREACH(name ${TEST_SRCS})
  ADD_TEST(${name} ${GDCM_TABLES_TESTS} ${name})
ENDFOREACH(name)


