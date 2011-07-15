# Define the tests for Media Storage and File Format
# MSFF
SET(MSFF_TEST_SRCS
  TestAnonymizer
  TestIconImageFilter
  TestIconImageGenerator
  TestIconImageGenerator2
  TestIconImageGenerator3
  TestParseXPATH
  TestValidate
  TestAnonymizeEvent
  TestFileDerivation
  TestSegmentedPaletteColorLookupTable
  TestPNMCodec
  TestSpacing
  TestSerieHelper
  TestFileExplicitFilter
  TestImageFragmentSplitter
  TestTagPath
  TestOrientation
  TestIconImage
  TestImageHelper
  TestImageToImageFilter
  TestImageChangeTransferSyntax1
  #TestImageChangePhotometricInterpretation
  #TestImageChangePhotometricInterpretation2 # does not compile on mingw...
  TestImageChangeTransferSyntax2
  TestImageChangeTransferSyntax3
  TestImageChangeTransferSyntax4
  # see below
  TestImageChangeTransferSyntax6
  TestImageChangeTransferSyntax7
  TestImageApplyLookupTable
  TestImageChangePlanarConfiguration
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
  TestPrint
  TestSorter
  TestImageReader
  TestStreamImageReader
  TestStreamImageWriter
  TestImageReaderRandomEmpty
  TestDirectionCosines
  TestImageWriter
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

IF(GDCM_DATA_ROOT)
  SET(MSFF_TEST_SRCS
    ${MSFF_TEST_SRCS}
    TestScanner
    TestPrinter2
    TestIPPSorter
    TestIPPSorter2
    TestCopyDataSet
    TestDataElementValueAsSQ
    TestImageWriter2
    TestDICOMDIRGenerator1 # Must be after TestImageChangeTransferSyntax4
    TestDICOMDIRGenerator2 # Must be after TestImageChangeTransferSyntax4
    )
    # Those tests requires that openssl be linked in:
    IF(GDCM_USE_SYSTEM_OPENSSL)
      SET(MSFF_TEST_SRCS
        ${MSFF_TEST_SRCS}
        TestAnonymizer2
        TestAnonymizer3
        )
    ENDIF(GDCM_USE_SYSTEM_OPENSSL)
ENDIF(GDCM_DATA_ROOT)

# gdcmDataExtra
IF(GDCM_DATA_EXTRA_ROOT)
  SET(MSFF_TEST_SRCS
    ${MSFF_TEST_SRCS}
    TestSplitMosaicFilter
    TestOverlay2
    )
ENDIF(GDCM_DATA_EXTRA_ROOT)

IF(GDCM_USE_JPEGLS)
  SET(MSFF_TEST_SRCS
    ${MSFF_TEST_SRCS}
    TestImageChangeTransferSyntax5
    )
ENDIF(GDCM_USE_JPEGLS)

IF(GDCM_HAVE_PTHREAD_H)
  SET(MSFF_TEST_SRCS
    ${MSFF_TEST_SRCS}
    TestUIDGenerator2
    )
ENDIF(GDCM_HAVE_PTHREAD_H)

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

CREATE_TEST_SOURCELIST(MSFFTests gdcmMSFFTests.cxx ${MSFF_TEST_SRCS}
  EXTRA_INCLUDE gdcmTestDriver.h
  )
ADD_EXECUTABLE(gdcmMSFFTests ${MSFFTests})
TARGET_LINK_LIBRARIES(gdcmMSFFTests gdcmMSFF)
IF(GDCM_HAVE_PTHREAD_H)
TARGET_LINK_LIBRARIES(gdcmMSFFTests pthread)
ENDIF(GDCM_HAVE_PTHREAD_H)

#Don't understand why I need that ??
SET(GDCM_MSFF_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmMSFFTests")

# Loop over files and create executables
FOREACH(name ${MSFF_TEST_SRCS})
  ADD_TEST(${name} ${GDCM_MSFF_TESTS} ${name})
ENDFOREACH(name)
IF(GDCM_DATA_ROOT)
  SET_TESTS_PROPERTIES(TestDICOMDIRGenerator2 PROPERTIES WILL_FAIL ON)
ENDIF(GDCM_DATA_ROOT)

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

FILE(MAKE_DIRECTORY "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax3/dcmdrle/")

FOREACH(filename ${gdcm_data_filenames_glob})
  GET_FILENAME_COMPONENT(filename_name ${filename} NAME)
  STRING(REGEX MATCH ${filename_name} bad_dicom ${black_list_reader})
  IF(NOT bad_dicom)
    IF(GDCM_TEST_DCMTK)
      IF(DCMTK_DCMDRLE_EXECUTABLE)
        ADD_TEST("DCMDRLE-${filename_name}" ${DCMTK_DCMDRLE_EXECUTABLE}
          "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax3/${filename_name}"
          "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax3/dcmdrle/${filename_name}")
        # Special handling of the DICOMDIR files:
        STRING(REGEX MATCH ${filename_name} is_dicomdir ${gdcm_data_dicomdir_filenames_glob})
        IF(is_dicomdir)
          #MESSAGE("IS DICOMDIR ${filename_name}")
          SET_TESTS_PROPERTIES("DCMDRLE-${filename_name}" PROPERTIES WILL_FAIL TRUE)
        ENDIF(is_dicomdir)
        #
      ENDIF(DCMTK_DCMDRLE_EXECUTABLE)
    ENDIF(GDCM_TEST_DCMTK)
  ENDIF(NOT bad_dicom)
ENDFOREACH(filename)

FILE(MAKE_DIRECTORY "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax5/dcmdjpls/")

FOREACH(filename ${gdcm_data_filenames_glob})
  GET_FILENAME_COMPONENT(filename_name ${filename} NAME)
  STRING(REGEX MATCH ${filename_name} bad_dicom ${black_list_reader})
  IF(NOT bad_dicom)
    IF(GDCM_TEST_DCMTK)
      IF(DCMTK_DCMDJPLS_EXECUTABLE)
        #if(EXISTS "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax5/${filename_name}")
        ADD_TEST("DCMDJPLS-${filename_name}" ${DCMTK_DCMDJPLS_EXECUTABLE}
          "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax5/${filename_name}"
          "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax5/dcmdjpls/${filename_name}")
        # Special handling of the DICOMDIR files:
        STRING(REGEX MATCH ${filename_name} is_dicomdir ${gdcm_data_dicomdir_filenames_glob})
        IF(is_dicomdir)
          #MESSAGE("IS DICOMDIR ${filename_name}")
          SET_TESTS_PROPERTIES("DCMDJPLS-${filename_name}" PROPERTIES WILL_FAIL TRUE)
        ENDIF(is_dicomdir)
        #endif(EXISTS "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax5/${filename_name}")
        #
      ENDIF(DCMTK_DCMDJPLS_EXECUTABLE)
    ENDIF(GDCM_TEST_DCMTK)
  ENDIF(NOT bad_dicom)
ENDFOREACH(filename)

# Need to SET_TESTS_PROPERTIES only *after* the loop is done (test need to have been declared first)
IF(GDCM_TEST_DCMTK)
  IF(GDCM_DATA_ROOT)
    IF(DCMTK_DCMDJPLS_EXECUTABLE)
      # No pixel data
      SET_TESTS_PROPERTIES("DCMDJPLS-ELSCINT1_PMSCT_RLE1.dcm" PROPERTIES WILL_FAIL TRUE)
    ENDIF(DCMTK_DCMDJPLS_EXECUTABLE)
    IF(DCMTK_DCMDJPEG_EXECUTABLE)
      # No pixel data
      SET_TESTS_PROPERTIES("DCMDJPEG-ELSCINT1_PMSCT_RLE1.dcm" PROPERTIES WILL_FAIL TRUE)
    ENDIF(DCMTK_DCMDJPEG_EXECUTABLE)
    IF(DCMTK_DCMDRLE_EXECUTABLE)
      # No pixel data
      SET_TESTS_PROPERTIES("DCMDRLE-ELSCINT1_PMSCT_RLE1.dcm" PROPERTIES WILL_FAIL TRUE)
      # It is missing the very last pixel, so technically is illegal
      SET_TESTS_PROPERTIES("DCMDRLE-ALOKA_SSD-8-MONO2-RLE-SQ.dcm" PROPERTIES WILL_FAIL TRUE)
    ENDIF(DCMTK_DCMDRLE_EXECUTABLE)
  ENDIF(GDCM_DATA_ROOT)
ENDIF(GDCM_TEST_DCMTK)
