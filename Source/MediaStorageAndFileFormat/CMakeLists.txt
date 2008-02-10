# Define the srcs for Media Storage And FileFormat
# MSFF
SET(MSFF_SRCS
  gdcmUIDGenerator.cxx
  gdcmPrinter.cxx
  gdcmDictPrinter.cxx
  gdcmReader.cxx
  gdcmScanner.cxx
  gdcmImageReader.cxx
  gdcmImageWriter.cxx
  gdcmStringFilter.cxx
  gdcmSpacingHelper.cxx
  gdcmWriter.cxx
  gdcmValidate.cxx
  gdcmDumper.cxx
  gdcmImage.cxx
  gdcmImageConverter.cxx
  gdcmImageCodec.cxx
  gdcmImageValue.cxx
  gdcmJPEG12Codec.cxx
  gdcmRLECodec.cxx
  gdcmPDFCodec.cxx
  gdcmAudioCodec.cxx
  gdcmJPEG16Codec.cxx
  gdcmJPEG2000Codec.cxx
  gdcmJPEG8Codec.cxx
  gdcmJPEGCodec.cxx
  gdcmRAWCodec.cxx
  gdcmLookupTable.cxx
  gdcmOverlay.cxx
  gdcmPhotometricInterpretation.cxx
  gdcmPixelFormat.cxx

  )

# Do the proper thing when building static...if only there was configured
# headers or def files instead
IF(NOT BUILD_SHARED_LIBS)
  SET_SOURCE_FILES_PROPERTIES(gdcmJPEG2000Codec.cxx
                              PROPERTIES 
                              COMPILE_FLAGS -DOPJ_STATIC
                              )
ENDIF(NOT BUILD_SHARED_LIBS)


# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"

  # FIXME:
  "${GDCM_SOURCE_DIR}/Utilities"
  "${GDCM_BINARY_DIR}/Utilities"
  #"${GDCM_BINARY_DIR}/Utilities/jpeg/8"
  #"${GDCM_SOURCE_DIR}/Utilities/jpeg"
  #"${GDCM_SOURCE_DIR}/Utilities/openjpeg/libopenjpeg"
  "${GDCM_BINARY_DIR}/Utilities/openjpeg"
  "${GDCM_BINARY_DIR}/Utilities/zlib"
 
  )

ADD_LIBRARY(gdcmMSFF ${MSFF_SRCS})
TARGET_LINK_LIBRARIES(gdcmMSFF gdcmDSED gdcmDICT
  gdcmjpeg8 gdcmjpeg12 gdcmjpeg16 gdcmopenjpeg)
