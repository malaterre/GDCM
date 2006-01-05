PROJECT(GDCMJPEGLS)

#-----------------------------------------------------------------------------
# Test if os defines a lenght for sockaddr
# only doing the test when we have sys/socket
IF("HAVE_C_INLINE" MATCHES "^HAVE_C_INLINE$")
  STRING(ASCII 35 POUND)
  FILE(WRITE ${GDCMJPEGLS_BINARY_DIR}/gdcmTestInline.c
    "inline int foo() { return 0; }\n
    int main() { return foo(); }")
  MESSAGE(STATUS "Checking if C compiler has inline keyword")
  TRY_COMPILE(HAVE_C_INLINE
    ${GDCMJPEGLS_BINARY_DIR}
    ${GDCMJPEGLS_BINARY_DIR}/gdcmTestInline.c
    OUTPUT_VARIABLE OUTPUT)
  IF(HAVE_C_INLINE)
    MESSAGE(STATUS "Checking if C compiler has inline keyword -- yes")
    SET(HAVE_C_INLINE 1 CACHE INTERNAL "Support if C compiler has inline keyword")
    WRITE_FILE(${CMAKE_BINARY_DIR}/CMakeOutput.log
      "Determining if C compiler has inline keyword"
      "passed with the following output:\n"
      "${OUTPUT}\n" APPEND)
  ELSE(HAVE_C_INLINE)
    MESSAGE(STATUS "Checking if C compiler has inline keyword -- no")
    SET(HAVE_C_INLINE 0 CACHE INTERNAL "Support if C compiler has inline keyword")
    WRITE_FILE(${CMAKE_BINARY_DIR}/CMakeError.log
      "Determining if C compiler has inline keyword"
      "failed with the following output:\n"
      "${OUTPUT}\n" APPEND)
  ENDIF(HAVE_C_INLINE)
ENDIF("HAVE_C_INLINE" MATCHES "^HAVE_C_INLINE$")

INCLUDE (${CMAKE_ROOT}/Modules/CheckIncludeFile.cmake)
CHECK_INCLUDE_FILE("unistd.h"    HAVE_UNISTD_H)
CONFIGURE_FILE(
  "${GDCMJPEGLS_SOURCE_DIR}/jpegls_config.h.in"
  "${GDCMJPEGLS_BINARY_DIR}/jpegls_config.h"
  @ONLY IMMEDIATE)

SUBDIRS(Decoder
  # Encoder
  )
