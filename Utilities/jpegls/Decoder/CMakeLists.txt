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
      "${CMAKE_CURRENT_SOURCE_DIR}/${f}"
      PROPERTIES COMPILE_FLAGS -fno-common)
  ENDFOREACH(f)
ENDIF(APPLE)


ADD_LIBRARY(${JPEGLS_LIBRARY_NAME} ${JPEGLS_SRCS})
#ADD_EXECUTABLE(locod ${JPEGLS_SRCS})

# TODO must do the INSTALL_ blah thing
INSTALL(TARGETS ${JPEGLS_LIBRARY_NAME}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
	)
