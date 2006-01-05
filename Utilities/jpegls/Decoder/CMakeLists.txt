INCLUDE_REGULAR_EXPRESSION("^.*$")

INCLUDE_DIRECTORIES("${GDCMJPEGLS_BINARY_DIR}")
INCLUDE_DIRECTORIES("${GDCMJPEGLS_SOURCE_DIR}/Decoder")

SET(GDCMJPEGLS_SRCS
  global.c 
  jpegmark.c 
  initialize.c 
  decoder.c 
  lossless_d.c 
  lossy_d.c 
  bitio.c 
  melcode.c)

# Do the -fno-common magic
IF(APPLE)
  FOREACH(f ${GDCMJPEGLS_SRCS})
    SET_SOURCE_FILES_PROPERTIES(
      "${GDCMJPEGLS_SOURCE_DIR}/Decoder/${f}"
      PROPERTIES COMPILE_FLAGS -fno-common)
  ENDFOREACH(f)
ENDIF(APPLE)

FOREACH(f ${GDCMJPEGLS_SRCS})
  SET( CXX_SOURCES ${CXX_SOURCES} ${GDCMJPEGLS_BINARY_DIR}/Decoder/${f}xx)
  CONFIGURE_FILE(${GDCMJPEGLS_SOURCE_DIR}/Decoder/${f} ${GDCMJPEGLS_BINARY_DIR}/Decoder/${f}xx COPYONLY)
ENDFOREACH(f)

SET(CXX_SOURCES
  ${CXX_SOURCES}
  gdcmfstream.cxx)

#ADD_LIBRARY(gdcmjpegls ${GDCMJPEGLS_SRCS})
ADD_LIBRARY(gdcmjpegls ${CXX_SOURCES})
ADD_EXECUTABLE(locod ${CXX_SOURCES})

# TODO must do the INSTALL_ blah thing
INSTALL_TARGETS(/lib/gdcm/ gdcmjpegls)
