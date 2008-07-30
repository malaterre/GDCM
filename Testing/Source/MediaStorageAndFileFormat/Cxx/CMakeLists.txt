# Define the tests for Media Storage and File Format
# MSFF
SET(MSFF_TEST_SRCS
  TestAnonymizer
  TestTagPath
  TestOrientation
  TestIconImage
  TestImageHelper
  TestImageToImageFilter
  TestImageChangeTransferSyntax
  TestImageChangeTransferSyntax2
  TestImageChangeTransferSyntax3
  TestCoder
  TestDecoder
  TestRescaler
  TestDumper
  TestDictPrinter
  TestApplicationEntity
  TestStringFilter
  TestUIDGenerator
  #TestUIDGenerator3
  TestPrinter
  TestScanner
  TestSorter
  TestIPPSorter
  TestImageReader
  TestCopyDataSet
  TestDirectionCosines
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

# There is a new test that compress all images using the jpeg compression alg:
# try to decompress them with dcmtk:
FILE(MAKE_DIRECTORY "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax/dcmdjpeg/")

FOREACH(filename ${gdcm_data_filenames_glob})
  GET_FILENAME_COMPONENT(filename_name ${filename} NAME)
  STRING(REGEX MATCH ${filename_name} bad_dicom ${black_list_reader})
  IF(NOT bad_dicom)
    IF(GDCM_TEST_DCMTK)
      IF(DCMTK_DCMDJPEG_EXECUTABLE)
        ADD_TEST("DCMDJPEG-${filename_name}" ${DCMTK_DCMDJPEG_EXECUTABLE}
          "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax/${filename_name}"
          "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax/dcmdjpeg/${filename_name}")
        # Special handling of the DICOMDIR files:
        STRING(REGEX MATCH ${filename_name} is_dicomdir ${gdcm_data_dicomdir_filenames_glob})
        IF(is_dicomdir)
          #MESSAGE("IS DICOMDIR ${filename_name}")
          SET_TESTS_PROPERTIES("DCMDJPEG-${filename_name}" PROPERTIES WILL_FAIL TRUE)
        ENDIF(is_dicomdir)
      ENDIF(DCMTK_DCMDJPEG_EXECUTABLE)
    ENDIF(GDCM_TEST_DCMTK)
  ENDIF(NOT bad_dicom)
ENDFOREACH(filename)

