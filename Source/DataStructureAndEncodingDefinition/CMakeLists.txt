# Define the srcs for Data Structure and Encoding Definitions
# DSED
SET(DSED_SRCS
  gdcmVR.cxx
  gdcmVM.cxx
  gdcmExplicitDataElement.cxx
  gdcmImplicitDataElement.cxx
  gdcmDataSet.cxx
  gdcmTS.cxx
  gdcmParser.cxx
  gdcmReader.cxx
  gdcmFileMetaInformation.cxx
  gdcmSequenceOfFragments.cxx
  gdcmSequenceOfItems.cxx
  gdcmImageReader.cxx
  gdcmImageValue.cxx
  gdcmJPEGCodec.cxx
  gdcmJPEG2000Codec.cxx
  gdcmRAWCodec.cxx
  gdcmRLECodec.cxx
  gdcmImageConverter.cxx
  gdcmItem.cxx
  gdcmWriter.cxx
  gdcmFragment.cxx
  #gdcmJPEGDataSrc.cxx
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_BINARY_DIR}/Source/Common"

  # FIXME:
  "${GDCM_SOURCE_DIR}/Utilities"
  #"${GDCM_BINARY_DIR}/Utilities"
  "${GDCM_BINARY_DIR}/Utilities/jpeg/8"
  "${GDCM_SOURCE_DIR}/Utilities/jpeg"
  #"${GDCM_SOURCE_DIR}/Utilities/openjpeg/libopenjpeg"
  "${GDCM_BINARY_DIR}/Utilities/openjpeg"
  )

ADD_LIBRARY(gdcmDSED ${DSED_SRCS})
TARGET_LINK_LIBRARIES(gdcmDSED gdcmCommon
  gdcmjpeg8 gdcmjpeg12 gdcmjpeg16 gdcmopenjpeg)

