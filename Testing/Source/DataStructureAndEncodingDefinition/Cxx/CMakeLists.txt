# Define the tests for Data Structure and Encoding Definitions
# DSED
set(DSED_TEST_SRCS
  TestAttribute.cxx
  TestCodeString.cxx
  TestAttribute1.cxx
  TestAttribute7.cxx
  #TestReadPatientName.cxx
  TestLO.cxx
  TestCSAElement.cxx
  #TestByteBuffer.cxx
  #TestByteValue.cxx
  TestPreamble.cxx
  TestReader.cxx
  #TestReader4.cxx # FIXME
  TestReaderUpToTag1.cxx
  TestReaderUpToTag2.cxx
  TestReaderSelectedTags.cxx
  TestReaderSelectedPrivateGroups.cxx
  TestReaderCanRead.cxx
  TestWriter.cxx
  TestWriter2.cxx
  TestCSAHeader.cxx
  TestByteSwapFilter.cxx
  TestBasicOffsetTable.cxx
  TestComposite.cxx
  TestDataElement.cxx
  TestDataSet.cxx
  #TestVRDS.cxx
  TestDS.cxx
  TestVRLT.cxx
  TestVRUI.cxx
  TestElement1.cxx
  #TestExplicitDataElement.cxx
  TestFile.cxx
  TestFileSet.cxx
  TestFragment.cxx
  #TestImplicitDataElement.cxx
  TestItem.cxx
  #TestParser.cxx
  TestSequenceOfFragments.cxx
  TestSequenceOfItems.cxx
  TestTag.cxx
  TestPrivateTag.cxx
  TestTransferSyntax.cxx
  TestMediaStorage.cxx
  TestVL.cxx
  TestVM.cxx
  TestVR.cxx
  #TestValue.cxx
  #TestTorture.cxx
  TestElement2.cxx
  TestElement4.cxx
  TestElement5.cxx
  TestElement6.cxx
  )
if(GDCM_TESTING_USE_LC_NUMERIC)
# The test expect to be able to set fr as locale only turn if user
# set the appropriate & hidden cmake variable
set(DSED_TEST_SRCS
  ${DSED_TEST_SRCS}
  TestLCNumeric.cxx
)
endif()
if(GDCM_DATA_ROOT)
set(DSED_TEST_SRCS
  ${DSED_TEST_SRCS}
  TestFileMetaInformation.cxx
  TestReader2.cxx
  TestAttribute8.cxx
  TestPDBHeader.cxx
  TestSequenceOfItems2.cxx
  TestSequenceOfItems3.cxx
  )
endif()
if(GDCM_DATA_EXTRA_ROOT)
set(DSED_TEST_SRCS
  ${DSED_TEST_SRCS}
  TestInvalidDICOMFiles.cxx
  )
endif()

CHECK_INCLUDE_FILE("sys/mman.h"   GDCM_HAVE_SYS_MMAN_H)

# Need mmap
if(GDCM_HAVE_SYS_MMAN_H)
  set(DSED_TEST_SRCS ${DSED_TEST_SRCS}
    TestReader3.cxx
  )
endif()

option(SHARED_PTR "shared_ptr" OFF)
mark_as_advanced(SHARED_PTR)
if(SHARED_PTR)
  set(DSED_TEST_SRCS
    ${DSED_TEST_SRCS}
    TestCopyValue.cxx
    )
endif()

# Add the include paths
include_directories(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_BINARY_DIR}/Utilities/zlib"
  "${GDCM_SOURCE_DIR}/Utilities"
  )

create_test_sourcelist(DSEDTests gdcmDSEDTests.cxx ${DSED_TEST_SRCS}
  EXTRA_INCLUDE gdcmTestDriver.h
  )
add_executable(gdcmDSEDTests ${DSEDTests})
target_link_libraries(gdcmDSEDTests gdcmDSED)
if(CMAKE_COMPILER_IS_GNUCXX AND MINGW)
  set_target_properties( gdcmDSEDTests PROPERTIES LINK_FLAGS "-Wl,--allow-multiple-definition")
endif()

# Loop over files and create executables
foreach(name ${DSED_TEST_SRCS})
  get_filename_component(testname ${name} NAME_WE)
  add_test(NAME ${testname} COMMAND gdcmDSEDTests ${testname})
endforeach()

# FIXME
#add_executable(TestAttribute2 TestAttribute2.cxx)
#add_executable(TestAttribute3 TestAttribute3.cxx)
#add_executable(TestAttribute4 TestAttribute4.cxx)
#add_executable(TestAttribute5 TestAttribute5.cxx)
