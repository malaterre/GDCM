IF(NOT JPEGLS_NAMESPACE)
  SET(JPEGLS_NAMESPACE "JPEGLS")
  SET(JPEGLS_STANDALONE 1)
ENDIF(NOT JPEGLS_NAMESPACE)
# In all cases:
STRING(TOLOWER ${JPEGLS_NAMESPACE} JPEGLS_LIBRARY_NAME)

PROJECT(${JPEGLS_NAMESPACE} C)
CMAKE_MINIMUM_REQUIRED(VERSION 2.2)

#-----------------------------------------------------------------------------
# JPEG-LS version number
SET(JPEGLS_MAJOR_VERSION 2)
SET(JPEGLS_MINOR_VERSION 2)
SET(JPEGLS_BUILD_VERSION 0)
SET(JPEGLS_VERSION 
      "${JPEGLS_MAJOR_VERSION}.${JPEGLS_MINOR_VERSION}.${JPEGLS_BUILD_VERSION}")

#-----------------------------------------------------------------------------
# Build shared lib by default
#OPTION(BUILD_SHARED_LIBS "Build JPEG-LS with shared libraries." ON)

#-----------------------------------------------------------------------------
SET (EXECUTABLE_OUTPUT_PATH ${JPEGLS_BINARY_DIR}/bin CACHE PATH "Single output directory for building all executables.")
SET (LIBRARY_OUTPUT_PATH ${JPEGLS_BINARY_DIR}/bin CACHE PATH "Single output directory for building all libraries.")
MARK_AS_ADVANCED(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)




INCLUDE (${CMAKE_ROOT}/Modules/CheckIncludeFile.cmake)
CHECK_INCLUDE_FILE("unistd.h"    HAVE_UNISTD_H)
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/jpegls_config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/jpegls_config.h"
  @ONLY IMMEDIATE)
SET(MANGLE_PREFIX ${JPEGLS_LIBRARY_NAME})
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/jpegls_mangle.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/jpegls_mangle.h
               @ONLY IMMEDIATE)

INCLUDE_DIRECTORIES(BEFORE
  ${CMAKE_CURRENT_BINARY_DIR}
  )
SUBDIRS(
  Decoder
  Encoder
  )

