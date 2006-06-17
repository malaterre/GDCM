#-----------------------------------------------------------------------------
# Rebuild gdcm whenever a file starting with gdcm* is modified
INCLUDE_REGULAR_EXPRESSION("^gdcm.*$")

# configure the .h file
CONFIGURE_FILE(
  "${GDCM_SOURCE_DIR}/Source/Common/gdcmConfigure.h.in"
  "${GDCM_BINARY_DIR}/Source/Common/gdcmConfigure.h"
  IMMEDIATE
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
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
  )

ADD_LIBRARY(gdcmCommon ${Common_SRCS})
