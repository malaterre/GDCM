# Define the tests for Data Structure and Encoding Definitions
# DSED
SET(DSED_TEST_SRCS
  TestAttribute
  TestCodeString
  TestAttribute1
  TestAttribute7
  #TestReadPatientName
  TestLO
  TestCSAElement
  #TestByteBuffer
  #TestByteValue
  TestPreamble
  TestReader
  TestReaderUpToTag
  TestReaderUpToTag2
  TestReaderSelectedTags
  TestReaderSelectedPrivateGroups
  TestReaderCanRead
  TestWriter
  TestWriter2
  TestCSAHeader
  TestByteSwapFilter
  TestBasicOffsetTable
  TestComposite
  TestDataElement
  TestDataSet
  #TestVRDS
  TestDS
  TestVRLT
  TestVRUI
  TestElement
  #TestExplicitDataElement
  TestFileMetaInformation
  TestFile
  TestFileSet
  TestFragment
  #TestImplicitDataElement
  TestItem
  #TestParser
  TestSequenceOfFragments
  TestSequenceOfItems
  TestTag
  TestPrivateTag
  TestTransferSyntax
  TestMediaStorage
  TestVL
  TestVM
  TestVR
  #TestValue
  #TestTorture
  TestElement2
  TestElement4
  TestElement5
  )
IF(GDCM_TESTING_USE_LC_NUMERIC)
# The test expect to be able to set fr as locale only turn if user
# set the appropriate & hidden cmake variable
SET(DSED_TEST_SRCS
  ${DSED_TEST_SRCS}
  TestLCNumeric
)
ENDIF(GDCM_TESTING_USE_LC_NUMERIC)
IF(GDCM_DATA_ROOT)
SET(DSED_TEST_SRCS
  ${DSED_TEST_SRCS}
  TestReader2
  TestAttribute8
  TestPDBHeader
  TestSequenceOfItems2
  )
ENDIF(GDCM_DATA_ROOT)
IF(GDCM_DATA_EXTRA_ROOT)
SET(DSED_TEST_SRCS
  ${DSED_TEST_SRCS}
  TestInvalidDICOMFiles
  )
ENDIF(GDCM_DATA_EXTRA_ROOT)

CHECK_INCLUDE_FILE("sys/mman.h"   GDCM_HAVE_SYS_MMAN_H)

# Need mmap
IF(GDCM_HAVE_SYS_MMAN_H)
  SET(DSED_TEST_SRCS ${DSED_TEST_SRCS}
    TestReader3
  )
ENDIF(GDCM_HAVE_SYS_MMAN_H)

OPTION(SHARED_PTR "shared_ptr" OFF)
MARK_AS_ADVANCED(SHARED_PTR)
IF(SHARED_PTR)
  SET(DSED_TEST_SRCS
    ${DSED_TEST_SRCS}
    TestCopyValue
    )
ENDIF(SHARED_PTR)

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_BINARY_DIR}/Utilities/zlib"
  "${GDCM_SOURCE_DIR}/Utilities"
  )

CREATE_TEST_SOURCELIST(DSEDTests gdcmDSEDTests.cxx ${DSED_TEST_SRCS}
  EXTRA_INCLUDE gdcmTestDriver.h
  )
ADD_EXECUTABLE(gdcmDSEDTests ${DSEDTests})
TARGET_LINK_LIBRARIES(gdcmDSEDTests gdcmDSED)
IF(CMAKE_COMPILER_IS_GNUCXX AND MINGW)
  SET_TARGET_PROPERTIES( gdcmDSEDTests PROPERTIES LINK_FLAGS "-Wl,--allow-multiple-definition")
ENDIF(CMAKE_COMPILER_IS_GNUCXX AND MINGW)

#Don't understand why I need that ??
SET(GDCM_DSED_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmDSEDTests")

# Loop over files and create executables
FOREACH(name ${DSED_TEST_SRCS})
if(CMAKE_CROSSCOMPILING)
  ADD_TEST(${name} ${TARGET_LINK_LIBRARIES} ${GDCM_DSED_TESTS}${CMAKE_EXECUTABLE_SUFFIX} ${name})
else()
  ADD_TEST(${name} ${GDCM_DSED_TESTS} ${name})
endif()
ENDFOREACH(name)

# FIXME
#ADD_EXECUTABLE(TestAttribute2 TestAttribute2.cxx)
#ADD_EXECUTABLE(TestAttribute3 TestAttribute3.cxx)
#ADD_EXECUTABLE(TestAttribute4 TestAttribute4.cxx)
#ADD_EXECUTABLE(TestAttribute5 TestAttribute5.cxx)
