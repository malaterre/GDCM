# Define the tests for Common
# Common
set(Common_TEST_SRCS
  TestVersion
  TestCommand
  TestCryptographicMessageSyntax
  TestDummyValueGenerator
  TestASN1
  TestTesting
  TestSystem3
  TestSwapper
  TestByteSwap
  TestString
  TestString2
  TestTerminal
  TestFilenameGenerator
  TestObject
  TestSmartPointer
  TestSwapCode
  TestSystem1
  TestSystem2
  TestTrace
  TestTypes
  TestUnpacker12Bits
  TestBase64
  )

if(GDCM_DATA_ROOT)
list(APPEND Common_TEST_SRCS
  TestDirectory
  TestFilename
  TestMD5
  )
if(GDCM_USE_SYSTEM_OPENSSL)
  list(APPEND Common_TEST_SRCS TestSHA1)
endif()
endif()

# Add the include paths
include_directories(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  )

create_test_sourcelist(CommonTests gdcmCommonTests.cxx ${Common_TEST_SRCS}
  EXTRA_INCLUDE gdcmTestDriver.h
  )
add_executable(gdcmCommonTests ${CommonTests})
target_link_libraries(gdcmCommonTests gdcmCommon)

#Don't understand why I need that ??
set(GDCM_Common_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmCommonTests")

# Loop over files and create executables
foreach(name ${Common_TEST_SRCS})
if(CMAKE_CROSSCOMPILING)
  add_test(${name} ${TARGET_SYSTEM_EMULATOR} ${GDCM_Common_TESTS}${CMAKE_EXECUTABLE_SUFFIX} ${name})
else()
  add_test(${name} ${GDCM_Common_TESTS} ${name})
endif()
endforeach()
