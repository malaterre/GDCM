INCLUDE_REGULAR_EXPRESSION("^.*$")

SET(JPEGLS_SRCS
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
  FOREACH(f ${JPEGLS_SRCS})
    SET_SOURCE_FILES_PROPERTIES(
      "${JPEGLS_SOURCE_DIR}/Decoder/${f}"
      PROPERTIES COMPILE_FLAGS -fno-common)
  ENDFOREACH(f)
ENDIF(APPLE)


ADD_LIBRARY(${JPEGLS_LIBRARY_NAME} ${JPEGLS_SRCS})
#ADD_EXECUTABLE(locod ${JPEGLS_SRCS})

# TODO must do the INSTALL_ blah thing
#INSTALL_TARGETS(/lib/ jpegls)
