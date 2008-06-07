# Define the srcs for Media Storage And FileFormat
# MSFF
SET(MSFF_SRCS
  gdcmAnonymizer.cxx
  gdcmRescaler.cxx
  gdcmOrientation.cxx
  gdcmSorter.cxx
  gdcmIPPSorter.cxx
  gdcmApplicationEntity.cxx
  gdcmDICOMDIR.cxx
  gdcmSpectroscopy.cxx
  gdcmEncapsulatedDocument.cxx
  gdcmFiducials.cxx
  gdcmWaveform.cxx
  gdcmPersonName.cxx
  gdcmIconImage.cxx
  gdcmUIDGenerator.cxx
  gdcmPrinter.cxx
  gdcmDictPrinter.cxx
  gdcmScanner.cxx
  gdcmImageReader.cxx
  gdcmImageWriter.cxx
  gdcmStringFilter.cxx
  gdcmImageHelper.cxx
  gdcmValidate.cxx
  gdcmDumper.cxx
  gdcmImage.cxx
  gdcmImageConverter.cxx
  gdcmImageCodec.cxx
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
  gdcmCurve.cxx
  gdcmPhotometricInterpretation.cxx
  gdcmPixelFormat.cxx
  gdcmSegmentedPaletteColorLookupTable.cxx
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
  )
IF(NOT GDCM_USE_SYSTEM_ZLIB)
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Utilities/gdcmzlib"
)
ENDIF(NOT GDCM_USE_SYSTEM_ZLIB)
IF(GDCM_USE_SYSTEM_UUID)
  INCLUDE_DIRECTORIES(
    ${UUID_INCLUDE_DIR}
  )
  SET(GDCMUUID ${UUID_LIBRARIES})
ELSE(GDCM_USE_SYSTEM_UUID)
  INCLUDE_DIRECTORIES(
    "${GDCM_BINARY_DIR}/Utilities/gdcmuuid" # uuid_mangle.h
  )
  SET(GDCMUUID gdcmuuid)
ENDIF(GDCM_USE_SYSTEM_UUID)

ADD_LIBRARY(gdcmMSFF ${MSFF_SRCS})
SET_TARGET_PROPERTIES(gdcmMSFF PROPERTIES ${GDCM_LIBRARY_PROPERTIES})
TARGET_LINK_LIBRARIES(gdcmMSFF gdcmDSED gdcmDICT
  gdcmjpeg8 gdcmjpeg12 gdcmjpeg16 gdcmopenjpeg)
#IF(HAVE_UUIDCREATE)
IF(WIN32)
  # For UuidCreate
  # http://msdn.microsoft.com/en-us/library/aa379205(VS.85).aspx
  TARGET_LINK_LIBRARIES(gdcmMSFF Rpcrt4)
#ENDIF(HAVE_UUIDCREATE)
ELSE(WIN32)
TARGET_LINK_LIBRARIES(gdcmMSFF ${GDCMUUID})
ENDIF(WIN32)
IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS gdcmMSFF
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime NAMELINK_SKIP
  )
  INSTALL(TARGETS gdcmMSFF
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development NAMELINK_ONLY
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
    )
ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)

IF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
  FILE(GLOB header_files "*.h" "*.txx")
  INSTALL(FILES ${header_files}
    DESTINATION ${GDCM_INSTALL_INCLUDE_DIR} COMPONENT Development
  )
ENDIF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
