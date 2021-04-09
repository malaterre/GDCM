# Define the tests for Media Storage and File Format
# MSFF
set(MSFF_TEST_SRCS
  TestAnonymizer.cxx
  TestDataSetHelper.cxx
  TestEquipmentManufacturer.cxx
  TestFileChangeTransferSyntax1.cxx
  TestFileChangeTransferSyntax2.cxx
  TestFileChangeTransferSyntax3.cxx
  TestFileChangeTransferSyntax4.cxx
  TestFileStreamer1.cxx
  TestFileStreamer2.cxx
  TestFileStreamer3.cxx
  TestFileStreamer4.cxx
  TestFileStreamer5.cxx
  TestFileStreamer6.cxx
  TestFileAnonymizer1.cxx
  TestFileAnonymizer2.cxx
  TestFileAnonymizer3.cxx
  TestFileAnonymizer4.cxx
  TestIconImageFilter.cxx
  #TestIconImageGenerator.cxx
  #TestIconImageGenerator2.cxx
  #TestIconImageGenerator3.cxx
  #TestIconImageGenerator4.cxx
  TestParseXPATH.cxx
  TestValidate.cxx
  TestAnonymizeEvent.cxx
  TestFileDerivation.cxx
  TestSegmentedPaletteColorLookupTable.cxx
  TestPNMCodec.cxx
  TestSpacing.cxx
  TestSerieHelper.cxx
  TestFileExplicitFilter.cxx
  TestImageFragmentSplitter.cxx
  TestTagPath.cxx
  TestOrientation.cxx
  TestIconImage.cxx
  TestImageHelper.cxx
  TestImageToImageFilter.cxx
  TestImageChangeTransferSyntax1.cxx
  #TestImageChangePhotometricInterpretation.cxx
  #TestImageChangePhotometricInterpretation2.cxx # does not compile on mingw...
  TestImageChangeTransferSyntax2.cxx
  TestImageChangeTransferSyntax3.cxx
  TestImageChangeTransferSyntax4.cxx
  # see below
  TestImageChangeTransferSyntax6.cxx
  TestImageChangeTransferSyntax7.cxx
  TestImageApplyLookupTable.cxx
  TestFileDecompressLookupTable.cxx
  TestImageChangePlanarConfiguration.cxx
  TestCoder.cxx
  TestDecoder.cxx
  TestRescaler1.cxx
  TestRescaler2.cxx
  TestDumper.cxx
  TestDictPrinter.cxx
  TestApplicationEntity.cxx
  TestStringFilter1.cxx
  TestStringFilter2.cxx
  TestStringFilter3.cxx
  TestStringFilter4.cxx
  TestUIDGenerator.cxx
  TestUUIDGenerator.cxx
  #TestUIDGenerator3.cxx
  TestXMLPrinter.cxx
  TestPrinter1.cxx
  TestPrint.cxx
  TestSorter.cxx
  TestImageReader.cxx
  TestStreamImageReader.cxx
  TestImageRegionReader1.cxx
  TestImageRegionReader2.cxx
  TestImageRegionReader3.cxx
  #TestStreamImageWriter.cxx
  TestImageReaderRandomEmpty.cxx
  TestDirectionCosines.cxx
  TestImageWriter.cxx
  TestCodec.cxx
  TestPDFCodec.cxx
  TestRLECodec.cxx
  TestAudioCodec.cxx
  TestImage.cxx
  TestPhotometricInterpretation.cxx
  TestLookupTable.cxx
  TestOverlay.cxx
  TestOverlay3.cxx
  TestCurve.cxx
  TestCurve2.cxx
  TestPixelFormat.cxx
  TestPersonName.cxx
  TestImageCodec.cxx
  TestImageConverter.cxx
  TestJPEGCodec.cxx
  TestRAWCodec.cxx
  TestDICOMDIR.cxx
  TestWaveform.cxx
  TestFiducials.cxx
  TestEncapsulatedDocument.cxx
  TestSpectroscopy.cxx
  TestSurfaceWriter.cxx
  TestSurfaceWriter2.cxx
  )

if(GDCM_DATA_ROOT)
  set(MSFF_TEST_SRCS
    ${MSFF_TEST_SRCS}
    TestSplitMosaicFilter3.cxx
    TestStrictScanner1.cxx
    TestStrictScanner2.cxx
    TestScanner1.cxx
    TestScanner2.cxx
    TestImageHelper2.cxx
    TestPrinter2.cxx
    TestIPPSorter.cxx
    TestIPPSorter2.cxx
    TestIPPSorter3.cxx
    TestCopyDataSet.cxx
    TestDataElementValueAsSQ.cxx
    TestImageWriter2.cxx
    TestDICOMDIRGenerator1.cxx # Must be after TestImageChangeTransferSyntax4
    TestDICOMDIRGenerator2.cxx # Must be after TestImageChangeTransferSyntax4
    )
    # Those tests requires that openssl be linked in:
    if(GDCM_USE_SYSTEM_OPENSSL)
      set(MSFF_TEST_SRCS
        ${MSFF_TEST_SRCS}
        TestAnonymizer2.cxx
        TestAnonymizer3.cxx
        )
    endif()
    if(GDCM_USE_SYSTEM_JSON)
      set(MSFF_TEST_SRCS
        ${MSFF_TEST_SRCS}
        TestJSON1.cxx
      )
    endif()
endif()

# gdcmDataExtra
if(GDCM_DATA_EXTRA_ROOT)
  set(MSFF_TEST_SRCS
    ${MSFF_TEST_SRCS}
    TestSplitMosaicFilter.cxx
    TestSplitMosaicFilter2.cxx
    TestOverlay2.cxx
    TestImageRegionReader4.cxx
    )
endif()

if(GDCM_USE_JPEGLS)
  set(MSFF_TEST_SRCS
    ${MSFF_TEST_SRCS}
    TestImageChangeTransferSyntax5.cxx
    )
endif()

if(GDCM_HAVE_PTHREAD_H)
  set(MSFF_TEST_SRCS
    ${MSFF_TEST_SRCS}
    TestUIDGenerator2.cxx
    )
endif()

if(GDCM_PIXEL_SPACING_DATA_ROOT)
  set(MSFF_TEST_SRCS
    ${MSFF_TEST_SRCS}
    TestImageReaderPixelSpacing.cxx
    )
endif()

# Add the include paths
include_directories(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Testing/Source/Data"
  "${GDCM_BINARY_DIR}/Testing/Source/Data"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat"
  )

create_test_sourcelist(MSFFTests gdcmMSFFTests.cxx ${MSFF_TEST_SRCS}
  EXTRA_INCLUDE gdcmTestDriver.h
  )
add_executable(gdcmMSFFTests ${MSFFTests})
target_link_libraries(gdcmMSFFTests gdcmMSFF)
if(GDCM_HAVE_PTHREAD_H)
  target_link_libraries(gdcmMSFFTests pthread)
endif()

# Loop over files and create executables
foreach(name ${MSFF_TEST_SRCS})
  get_filename_component(testname ${name} NAME_WE)
  add_test(NAME ${testname} COMMAND gdcmMSFFTests ${testname})
endforeach()
if(GDCM_DATA_ROOT)
  set_tests_properties(TestDICOMDIRGenerator2 PROPERTIES WILL_FAIL ON)
endif()

# We can only run the dcmtk cross-checking test *only* after all the tests have run
# in particular once the TestWriter is done.
foreach(filename ${gdcm_data_filenames_glob})
  get_filename_component(filename_name ${filename} NAME)
  string(REGEX MATCH ${filename_name} bad_dicom ${black_list_reader})
  if(NOT bad_dicom)
    if(GDCM_TEST_DCMTK)
      if(DCMTK_DCMDUMP_EXECUTABLE)
        # -M : load short tags
        # -dc: disable correction
        add_test(NAME "DCMDUMP-${filename_name}" COMMAND ${DCMTK_DCMDUMP_EXECUTABLE} -M -dc
          "${GDCM_TEMP_DIRECTORY}/TestWriter/${filename_name}")
      endif()
    endif()
  endif()
endforeach()

# Repeat for dcdump
foreach(filename ${gdcm_data_filenames_glob})
  get_filename_component(filename_name ${filename} NAME)
  string(REGEX MATCH ${filename_name} bad_dicom ${black_list_reader})
  if(NOT bad_dicom)
    if(GDCM_TEST_DICOM3TOOLS)
      if(DCDUMP_EXECUTABLE)
        add_test(NAME "DCDUMP-${filename_name}" COMMAND "${DCDUMP_EXECUTABLE}"
          "${GDCM_TEMP_DIRECTORY}/TestWriter/${filename_name}")
      endif()
    endif()
  endif()
endforeach()

# There is a new test that compress all images using the jpeg compression alg:
# try to decompress them with dcmtk:
file(MAKE_DIRECTORY "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax/dcmdjpeg/")

foreach(filename ${gdcm_data_filenames_glob})
  get_filename_component(filename_name ${filename} NAME)
  string(REGEX MATCH ${filename_name} bad_dicom ${black_list_reader})
  if(NOT bad_dicom)
    if(GDCM_TEST_DCMTK)
      if(DCMTK_DCMDJPEG_EXECUTABLE)
        add_test(NAME "DCMDJPEG-${filename_name}" COMMAND ${DCMTK_DCMDJPEG_EXECUTABLE}
          "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax/${filename_name}"
          "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax/dcmdjpeg/${filename_name}")
        # Special handling of the DICOMDIR files:
        string(REGEX MATCH ${filename_name} is_dicomdir ${gdcm_data_dicomdir_filenames_glob})
        if(is_dicomdir)
          #message("IS DICOMDIR ${filename_name}")
          set_tests_properties("DCMDJPEG-${filename_name}" PROPERTIES WILL_FAIL TRUE)
        endif()
      endif()
    endif()
  endif()
endforeach()

file(MAKE_DIRECTORY "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax3/dcmdrle/")

foreach(filename ${gdcm_data_filenames_glob})
  get_filename_component(filename_name ${filename} NAME)
  string(REGEX MATCH ${filename_name} bad_dicom ${black_list_reader})
  if(NOT bad_dicom)
    if(GDCM_TEST_DCMTK)
      if(DCMTK_DCMDRLE_EXECUTABLE)
        add_test(NAME "DCMDRLE-${filename_name}" COMMAND ${DCMTK_DCMDRLE_EXECUTABLE}
          "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax3/${filename_name}"
          "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax3/dcmdrle/${filename_name}")
        # Special handling of the DICOMDIR files:
        string(REGEX MATCH ${filename_name} is_dicomdir ${gdcm_data_dicomdir_filenames_glob})
        if(is_dicomdir)
          #message("IS DICOMDIR ${filename_name}")
          set_tests_properties("DCMDRLE-${filename_name}" PROPERTIES WILL_FAIL TRUE)
        endif()
        #
      endif()
    endif()
  endif()
endforeach()

file(MAKE_DIRECTORY "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax5/dcmdjpls/")

foreach(filename ${gdcm_data_filenames_glob})
  get_filename_component(filename_name ${filename} NAME)
  string(REGEX MATCH ${filename_name} bad_dicom ${black_list_reader})
  if(NOT bad_dicom)
    if(GDCM_TEST_DCMTK)
      if(DCMTK_DCMDJPLS_EXECUTABLE)
        #if(EXISTS "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax5/${filename_name}")
        add_test(NAME "DCMDJPLS-${filename_name}" COMMAND ${DCMTK_DCMDJPLS_EXECUTABLE}
          "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax5/${filename_name}"
          "${GDCM_TEMP_DIRECTORY}/TestImageChangeTransferSyntax5/dcmdjpls/${filename_name}")
        # Special handling of the DICOMDIR files:
        string(REGEX MATCH ${filename_name} is_dicomdir ${gdcm_data_dicomdir_filenames_glob})
        if(is_dicomdir)
          #message("IS DICOMDIR ${filename_name}")
          set_tests_properties("DCMDJPLS-${filename_name}" PROPERTIES WILL_FAIL TRUE)
        endif()
        #endif()
        #
      endif()
    endif()
  endif()
endforeach()

# Need to SET_TESTS_PROPERTIES only *after* the loop is done (test need to have been declared first)
if(GDCM_TEST_DCMTK)
  if(GDCM_DATA_ROOT)
    if(DCMTK_DCMDJPLS_EXECUTABLE)
      # No pixel data
      set_tests_properties("DCMDJPLS-ELSCINT1_PMSCT_RLE1.dcm" PROPERTIES WILL_FAIL TRUE)
    endif()
    if(DCMTK_DCMDJPEG_EXECUTABLE)
      # No pixel data
      set_tests_properties("DCMDJPEG-ELSCINT1_PMSCT_RLE1.dcm" PROPERTIES WILL_FAIL TRUE)
    endif()
    if(DCMTK_DCMDRLE_EXECUTABLE)
      # No pixel data
      set_tests_properties("DCMDRLE-ELSCINT1_PMSCT_RLE1.dcm" PROPERTIES WILL_FAIL TRUE)
      # It is missing the very last pixel, so technically is illegal
      set_tests_properties("DCMDRLE-ALOKA_SSD-8-MONO2-RLE-SQ.dcm" PROPERTIES WILL_FAIL TRUE)
    endif()
  endif()
endif()
