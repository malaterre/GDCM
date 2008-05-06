# Define the tests for Media Storage and File Format
# MSFF
SET(MSFF_TEST_SRCS
  TestAnonymizer
  TestOrientation
  TestIconImage
  TestSpacingHelper
  TestCoder
  TestDecoder
  TestRescaler
  TestDumper
  TestDictPrinter
  TestApplicationEntity
  TestStringFilter
  TestUIDGenerator
  TestUIDGenerator3
  TestPrinter
  TestScanner
  TestSorter
  TestIPPSorter
  TestImageReader
  TestCopyDataSet
  TestImageWriter
  #TestImageWriter2
  TestCodec
  TestPDFCodec
  TestRLECodec
  TestAudioCodec
  TestImage
  TestPhotometricInterpretation
  TestLookupTable
  TestOverlay
  TestCurve
  TestPixelFormat
  TestPersonName
  TestImageValue
  TestImageCodec
  TestImageConverter
  TestJPEGCodec
  TestRAWCodec
  TestDICOMDIR
  TestWaveform
  TestFiducials
  TestEncapsulatedDocument
  TestSpectroscopy
  )

IF(CMAKE_HAVE_PTHREAD_H)
SET(MSFF_TEST_SRCS ${MSFF_TEST_SRCS}
  TestUIDGenerator2
  )
ENDIF(CMAKE_HAVE_PTHREAD_H)
IF(GDCM_PIXEL_SPACING_DATA_ROOT)
  SET(MSFF_TEST_SRCS
    ${MSFF_TEST_SRCS}
    TestImageReaderPixelSpacing
  )
ENDIF(GDCM_PIXEL_SPACING_DATA_ROOT)


# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Testing/Source/Data"
  "${GDCM_BINARY_DIR}/Testing/Source/Data"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat"
  )

CREATE_TEST_SOURCELIST(MSFFTests gdcmMSFFTests.cxx ${MSFF_TEST_SRCS})
ADD_EXECUTABLE(gdcmMSFFTests ${MSFFTests})
TARGET_LINK_LIBRARIES(gdcmMSFFTests gdcmMSFF)
IF(CMAKE_HAVE_PTHREAD_H)
TARGET_LINK_LIBRARIES(gdcmMSFFTests pthread)
ENDIF(CMAKE_HAVE_PTHREAD_H)

#Don't understand why I need that ??
SET(GDCM_MSFF_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmMSFFTests")

# Loop over files and create executables
FOREACH(name ${MSFF_TEST_SRCS})
  ADD_TEST(${name} ${GDCM_MSFF_TESTS} ${name})
ENDFOREACH(name)

# We can only run the dcmtk cross-checking test *only* after all the tests have run
# in particular once the TestWriter is done.
FOREACH(filename ${gdcm_data_filenames_glob})
  GET_FILENAME_COMPONENT(filename_name ${filename} NAME)
  STRING(REGEX MATCH ${filename_name} bad_dicom ${black_list_reader})
  IF(NOT bad_dicom)
    IF(GDCM_TEST_DCMTK)
      IF(DCMTK_DCMDUMP_EXECUTABLE)
        # -M : load short tags
        # -dc: disable correction
        ADD_TEST("DCMDUMP-${filename_name}" ${DCMTK_DCMDUMP_EXECUTABLE} -M -dc
          "${GDCM_TEMP_DIRECTORY}/TestWriter/${filename_name}")
      ENDIF(DCMTK_DCMDUMP_EXECUTABLE)
    ENDIF(GDCM_TEST_DCMTK)
  ENDIF(NOT bad_dicom)
ENDFOREACH(filename)

# Repeat for dcdump
FOREACH(filename ${gdcm_data_filenames_glob})
  GET_FILENAME_COMPONENT(filename_name ${filename} NAME)
  STRING(REGEX MATCH ${filename_name} bad_dicom ${black_list_reader})
  IF(NOT bad_dicom)
    IF(GDCM_TEST_DICOM3TOOLS)
      IF(DCDUMP_EXECUTABLE)
        ADD_TEST("DCDUMP-${filename_name}" "${DCDUMP_EXECUTABLE}"
          "${GDCM_TEMP_DIRECTORY}/TestWriter/${filename_name}")
      ENDIF(DCDUMP_EXECUTABLE)
    ENDIF(GDCM_TEST_DICOM3TOOLS)
  ENDIF(NOT bad_dicom)
ENDFOREACH(filename)

