#-----------------------------------------------------------------------------
# Rebuild gdcm whenever a file starting with gdcm* is modified
INCLUDE_REGULAR_EXPRESSION("^gdcm.*$")

# configure the .h file
OPTION(GDCM_SUPPORT_BROKEN_IMPLEMENTATION "Handle broken DICOM" ON)
OPTION(GDCM_WRITE_ODD_LENGTH "Do not change" OFF)
MARK_AS_ADVANCED(
  GDCM_SUPPORT_BROKEN_IMPLEMENTATION 
  GDCM_WRITE_ODD_LENGTH
  )

# Big endian thing:
INCLUDE (${CMAKE_ROOT}/Modules/TestBigEndian.cmake)
TEST_BIG_ENDIAN(GDCM_WORDS_BIGENDIAN)

CONFIGURE_FILE(
  "${GDCM_SOURCE_DIR}/Source/Common/gdcmConfigure.h.in"
  "${GDCM_BINARY_DIR}/Source/Common/gdcmConfigure.h"
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Utilities/md5"
  "${GDCM_BINARY_DIR}/Utilities/md5"

  "${GDCM_SOURCE_DIR}/Utilities"
  )

SET(Common_SRCS
  gdcmDirectory.cxx
  gdcmFilename.cxx
  gdcmFilenameGenerator.cxx
  gdcmSwapCode.cxx
  gdcmSystem.cxx
  gdcmTrace.cxx
  gdcmException.cxx
  gdcmDeflateStream.cxx
  gdcmByteSwap.cxx
  #gdcmSwapper.cxx
  )

ADD_LIBRARY(gdcmCommon ${Common_SRCS})
TARGET_LINK_LIBRARIES(gdcmCommon gdcmmd5 gdcmzlib)
