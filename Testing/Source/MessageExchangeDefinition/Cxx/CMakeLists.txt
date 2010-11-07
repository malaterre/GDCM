SET(MEXD_TEST_SRCS
TestBaseRootQuery
TestPatientRootQuery
TestPresentationContext
TestQueryFactory
TestStudyRootQuery
TestULConnectionManager
TestAllFunctions
)

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Testing/Source/Data"
  "${GDCM_BINARY_DIR}/Testing/Source/Data"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat"
  "${GDCM_SOURCE_DIR}/Source/MessageExchangeDefinition"
  )

CREATE_TEST_SOURCELIST(MEXDTests gdcmMEXDTests.cxx ${MEXD_TEST_SRCS}
  EXTRA_INCLUDE gdcmTestDriver.h
  )
ADD_EXECUTABLE(gdcmMEXDTests ${MEXDTests})
TARGET_LINK_LIBRARIES(gdcmMEXDTests gdcmMEXD gdcmDSED gdcmCommon)

#Don't understand why I need that ??
SET(GDCM_MEXD_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmMEXDTests")

# Loop over files and create executables
FOREACH(name ${MEXD_TEST_SRCS})
  ADD_TEST(${name} ${GDCM_MEXD_TESTS} ${name})
ENDFOREACH(name)

set(DCMQRSCP_HOSTNAME gotlib)
set(DCMQRSCP_PORT 5677)
set(DCMQRSCP_DIRECTORY ${GDCM_TEMP_DIRECTORY})
configure_file(
  ${GDCM_SOURCE_DIR}/CMake/dcmqrscp.cfg.in
  ${CMAKE_CURRENT_BINARY_DIR}/dcmqrscp.cfg
  )
# execute_process(COMMAND ${DCMTK_DCMQRSCP_EXECUTABLE}
#   --verbose --debug -c ${CMAKE_CURRENT_BINARY_DIR}/dcmqrscp.cfg)
