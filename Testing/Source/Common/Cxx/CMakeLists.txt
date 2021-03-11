# Define the tests for Common
# Common
set(Common_TEST_SRCS
  TestVersion.cxx
  TestCommand.cxx
  TestCryptographicMessageSyntax.cxx
  TestDummyValueGenerator.cxx
  TestASN1.cxx
  TestTesting.cxx
  TestSystem3.cxx
  TestSwapper.cxx
  TestByteSwap.cxx
  TestString1.cxx
  TestString2.cxx
  TestTerminal.cxx
  TestFilenameGenerator.cxx
  TestObject.cxx
  TestSmartPointer.cxx
  TestSwapCode.cxx
  TestSystem1.cxx
  TestSystem2.cxx
  TestTrace.cxx
  TestTypes.cxx
  TestUnpacker12Bits.cxx
  TestBase64.cxx
  TestLog2.cxx
  )

if(GDCM_DATA_ROOT)
list(APPEND Common_TEST_SRCS
  TestDirectory.cxx
  TestFilename.cxx
  TestMD5.cxx
  )
if(GDCM_USE_SYSTEM_OPENSSL)
  list(APPEND Common_TEST_SRCS TestSHA1.cxx)
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

# Loop over files and create executables
foreach(name ${Common_TEST_SRCS})
  get_filename_component(testname ${name} NAME_WE)
  add_test(NAME ${testname} COMMAND gdcmCommonTests ${testname})
endforeach()
