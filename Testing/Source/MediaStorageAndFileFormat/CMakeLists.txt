# Define the tests for Media Storage and File Format
# MSFF
SET(MSFF_TEST_SRCS
  TestStringFilter
  TestUID
  TestPrinter
  TestReader
  TestScanner
  TestReader2
  TestImageReader
  TestCopyDataSet
  TestImageWriter
  TestWriter
  TestCodec
  TestPDFCodec
  TestAudioCodec
  TestImage
  TestPhotometricInterpretation
  TestLookupTable
  TestOverlay
  TestPixelFormat
  TestPersonName
  TestImageValue
  TestImageCodec
  TestImageConverter
  TestJPEGCodec
  TestRAWCodec
  TestDICOMDIR
  TestPatient
  TestStudy
  TestSeries
  TestWaveform
  TestFiducials
  TestEncapsulatedDocument
  TestSpectroscopy
  )

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

#Don't understand why I need that ??
SET(GDCM_MSFF_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmMSFFTests")

# Loop over files and create executables
FOREACH(name ${MSFF_TEST_SRCS})
  ADD_TEST(${name} ${GDCM_MSFF_TESTS} ${name})
ENDFOREACH(name)


