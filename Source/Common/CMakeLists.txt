#-----------------------------------------------------------------------------
# Rebuild gdcm whenever a file starting with gdcm* is modified
INCLUDE_REGULAR_EXPRESSION("^gdcm.*$")

# configure the .h file
OPTION(GDCM_SUPPORT_BROKEN_IMPLEMENTATION "Handle broken DICOM" ON)
MARK_AS_ADVANCED(GDCM_SUPPORT_BROKEN_IMPLEMENTATION)
CONFIGURE_FILE(
  "${GDCM_SOURCE_DIR}/Source/Common/gdcmConfigure.h.in"
  "${GDCM_BINARY_DIR}/Source/Common/gdcmConfigure.h"
  IMMEDIATE
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Utilities/md5"
  "${GDCM_BINARY_DIR}/Utilities/md5"
  )

SET(Common_SRCS
  gdcmDirectory.cxx
  gdcmTrace.cxx
  gdcmSwapCode.cxx
  gdcmIOS.cxx
  gdcmIStream.cxx
  gdcmOStream.cxx
  gdcmIFStream.cxx
  gdcmOFStream.cxx
  gdcmStringStream.cxx
  gdcmImage.cxx
  gdcmImageIStream.cxx
  gdcmPixelType.cxx
  gdcmPhotometricInterpretation.cxx
  gdcmFilename.cxx
  gdcmSystem.cxx
  gdcmMemoryStream.cxx
  )

ADD_LIBRARY(gdcmCommon ${Common_SRCS})
TARGET_LINK_LIBRARIES(gdcmCommon gdcmmd5)
