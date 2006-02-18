# Define the tests
SET(TEST_SRCS
  TestAllLoadMinimumStuff
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
  TestSequenceOfItems
  #TestAllPrint
  TestGroupDict
  TestPrintGroup
  TestGroupSet
  #TestAllReadGroup
  TestItem
  TestFileSeeker
  TestDirectory
  TestAllPrintUID
  TestLoader
  TestPrinter
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Tests" # for gdcmDataImages.h
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Parser"
  )

CREATE_TEST_SOURCELIST(Tests gdcmTests.cxx ${TEST_SRCS})
ADD_EXECUTABLE(gdcmTests ${Tests})
TARGET_LINK_LIBRARIES(gdcmTests gdcmParser)

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
  "dummy.dcm"
  "diazpost.dcm" # This one is nasty
  #"CT-MONO2-12-lomb-an2.acr" # contains wrong group length !!
  #"MR-MONO2-12-angio-an1.acr" # idem
  "Siemens-leonardo-bugged.dcm"
  "NM_FromJulius_Caesar.dcm"
  "1075235AnouncedAsBigEndianButIsLittleEndian.dcm"
  "deflate_image_dfl.dcm" # Nasty compressed dataset
  "deflate_wave_dfl.dcm"
  "deflate_report_dfl.dcm"
  "ExplicitVRforPublicElementsImplicitVRforShadowElements.dcm"
  )

SET(GDCM_DATA_IMAGES)
SET(GDCM_BLACK_LIST_DATA_IMAGES)
FOREACH(filename ${GDCM_DATA_IMAGES_GLOB})
  GET_FILENAME_COMPONENT(filename_name ${filename} NAME)
  #MESSAGE( ${filename_name} )
  STRING(REGEX MATCH ${filename_name} bad_dicom ${BLACK_LIST})
  IF(NOT bad_dicom)
    SET(GDCM_DATA_IMAGES "${GDCM_DATA_IMAGES}\n\"${filename}\",")
  ELSE(NOT bad_dicom)
    SET(GDCM_BLACK_LIST_DATA_IMAGES "${GDCM_BLACK_LIST_DATA_IMAGES}\n\"${filename}\",")
  ENDIF(NOT bad_dicom)
ENDFOREACH(filename)

# Populate GDCM_DATA_IMAGES:
CONFIGURE_FILE(
  "${GDCM_SOURCE_DIR}/Tests/gdcmDataImages.h.in"
  "${GDCM_BINARY_DIR}/Tests/gdcmDataImages.h"
  )

