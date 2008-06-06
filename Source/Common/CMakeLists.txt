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

CHECK_INCLUDE_FILE_CONCAT("sys/time.h"     HAVE_SYS_TIME_H)
CHECK_INCLUDE_FILE_CONCAT("winsock.h"       HAVE_WINSOCK_H)
CHECK_INCLUDE_FILE_CONCAT("byteswap.h"       HAVE_BYTESWAP_H)
CHECK_INCLUDE_FILE("rpc.h"       HAVE_RPC_H)
  
INCLUDE(CheckFunctionExists)
#C99
CHECK_FUNCTION_EXISTS(strcasecmp  HAVE_STRCASECMP)
CHECK_FUNCTION_EXISTS(strncasecmp HAVE_STRNCASECMP)
CHECK_FUNCTION_EXISTS(snprintf    HAVE_SNPRINTF)
#M$ extension:
CHECK_FUNCTION_EXISTS(_stricmp    HAVE__STRICMP)
CHECK_FUNCTION_EXISTS(_strnicmp   HAVE__STRNICMP)
CHECK_FUNCTION_EXISTS(_snprintf   HAVE__SNPRINTF)

CONFIGURE_FILE(
  "${GDCM_SOURCE_DIR}/Source/Common/gdcmConfigure.h.in"
  "${GDCM_BINARY_DIR}/Source/Common/gdcmConfigure.h"
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"

  "${GDCM_BINARY_DIR}/Testing/Source/Data"
  "${GDCM_SOURCE_DIR}/Testing/Source/Data"

  "${GDCM_SOURCE_DIR}/Utilities"
  )

IF(GDCM_BUILD_TESTING)
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Utilities/gdcmmd5"
)
ENDIF(GDCM_BUILD_TESTING)

IF(NOT GDCM_USE_SYSTEM_ZLIB)
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Utilities/gdcmzlib"
)
ENDIF(NOT GDCM_USE_SYSTEM_ZLIB)

SET(Common_SRCS
  gdcmVersion.cxx
  gdcmObject.cxx
  gdcmDirectory.cxx
  gdcmTerminal.cxx
  gdcmString.cxx
  gdcmFilename.cxx
  gdcmFilenameGenerator.cxx
  gdcmSwapCode.cxx
  gdcmSystem.cxx
  gdcmTrace.cxx
  gdcmException.cxx
  gdcmDeflateStream.cxx
  gdcmByteSwap.cxx
  #gdcmSwapper.cxx
  gdcmUnpacker12Bits.cxx
  )

IF(GDCM_BUILD_TESTING)
SET(Common_SRCS ${Common_SRCS}
  gdcmTesting.cxx
)
ENDIF(GDCM_BUILD_TESTING)

ADD_LIBRARY(gdcmCommon ${Common_SRCS})
SET_TARGET_PROPERTIES(gdcmCommon PROPERTIES ${GDCM_LIBRARY_PROPERTIES})
TARGET_LINK_LIBRARIES(gdcmCommon ${GDCM_ZLIB_LIBRARIES})
IF(GDCM_BUILD_TESTING)
TARGET_LINK_LIBRARIES(gdcmCommon gdcmmd5 )
ENDIF(GDCM_BUILD_TESTING)

IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS gdcmCommon
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
  ${CPACK_NAMELINK_TYPE}
  )
ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)

IF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
  FILE(GLOB header_files "*.h" "*.txx")
  INSTALL(FILES ${header_files}
    "${GDCM_BINARY_DIR}/Source/Common/gdcmConfigure.h"
    DESTINATION ${GDCM_INSTALL_INCLUDE_DIR} COMPONENT Development
  )
ENDIF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
