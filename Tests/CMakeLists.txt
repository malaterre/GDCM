# Define the tests
SET(TEST_SRCS
  TestTag
  TestFileIO
  TestFileChunk
  TestTagIO
  TestDataElement
  TestVRValueLength
  TestVR
  TestSwap
  TestGroup
  #TestValueField
  TestVM
  TestTS
  TestDictEntry
  TestDict
  TestDataSet
  TestSequenceDataElement
  TestAllPrint
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Tests"
  "${GDCM_BINARY_DIR}/Source"
  "${GDCM_SOURCE_DIR}/Source"
  )

CREATE_TEST_SOURCELIST(Tests gdcmTests.cxx ${TEST_SRCS})
ADD_EXECUTABLE(gdcmTests ${Tests})
TARGET_LINK_LIBRARIES(gdcmTests gdcm)

#Don't understand why I need that ??
SET(GDCM_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmTests")

# Loop over files and create executables
FOREACH(name ${TEST_SRCS})
  ADD_TEST(${name} ${GDCM_TESTS} ${name})
ENDFOREACH(name)

#-----------------------------------------------------------------------------

# We need to test the reading of all dicom images in the gdcmData directory
# First parse this directory and extract all images

FILE(GLOB GDCM_DATA_IMAGES_GLOB
  "${GDCM_DATA_ROOT}/*.acr"
  "${GDCM_DATA_ROOT}/*.dcm"
  )
SET(BLACK_LIST
  #"diazpost.dcm" # This one is nasty
  )

SET(GDCM_DATA_IMAGES)
FOREACH(filename ${GDCM_DATA_IMAGES_GLOB})
  GET_FILENAME_COMPONENT(filename_name ${filename} NAME)
  #MESSAGE( ${filename_name} )
  STRING(REGEX MATCH ${filename_name} bad_dicom ${BLACK_LIST})
  IF(NOT bad_dicom)
    SET(GDCM_DATA_IMAGES "${GDCM_DATA_IMAGES}\n\"${filename}\",")
  ENDIF(NOT bad_dicom)
ENDFOREACH(filename)

# Populate GDCM_DATA_IMAGES:
CONFIGURE_FILE(
  "${GDCM_SOURCE_DIR}/Tests/gdcmDataImages.h.in"
  "${GDCM_BINARY_DIR}/Tests/gdcmDataImages.h"
  )

