# Define the tests for Common
# Common
SET(Common_TEST_SRCS
  TestVersion
  TestTesting
  TestSwapper
  TestByteSwap
  TestString
  TestDirectory
  TestTerminal
  TestFilename
  TestFilenameGenerator
  TestObject
  TestSmartPointer
  TestSwapCode
  TestSystem
  TestTrace
  TestUnpacker12Bits
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  )

CREATE_TEST_SOURCELIST(CommonTests gdcmCommonTests.cxx ${Common_TEST_SRCS})
ADD_EXECUTABLE(gdcmCommonTests ${CommonTests})
TARGET_LINK_LIBRARIES(gdcmCommonTests gdcmCommon)

#Don't understand why I need that ??
SET(GDCM_Common_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmCommonTests")

# Loop over files and create executables
FOREACH(name ${Common_TEST_SRCS})
  ADD_TEST(${name} ${GDCM_Common_TESTS} ${name})
ENDFOREACH(name)


