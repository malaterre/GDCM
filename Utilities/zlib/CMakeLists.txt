IF(NOT ZLIB_NAMESPACE)
  SET(ZLIB_NAMESPACE "ZLIB")
  SET(ZLIB_STANDALONE 1)
ENDIF(NOT ZLIB_NAMESPACE)
# In all cases:
STRING(TOLOWER ${ZLIB_NAMESPACE} ZLIB_LIBRARY_NAME)

PROJECT(${ZLIB_NAMESPACE} C)
CMAKE_MINIMUM_REQUIRED(VERSION 2.2)

# Do full dependency headers.
INCLUDE_REGULAR_EXPRESSION("^.*$")

# source files for zlib
SET(ZLIB_SRCS
  adler32.c
  compress.c
  crc32.c
  deflate.c
  #example.c
  gzio.c
  infback.c
  inffast.c
  inflate.c
  inftrees.c
  #minigzip.c
  trees.c
  uncompr.c
  zutil.c
  )


# for windows add the .def and .rc files to the source list if building shared libs
IF(WIN32)
  IF(BUILD_SHARED_LIBS)
    SET(ZLIB_DLL 1)
    IF(NOT UNIX)
      IF(NOT BORLAND)
        IF(NOT MINGW)
          SET(ZLIB_SRCS ${ZLIB_SRCS} zlib.def zlib.rc  )
        ENDIF(NOT MINGW)
      ENDIF(NOT BORLAND) 
    ENDIF(NOT UNIX)   
  ENDIF(BUILD_SHARED_LIBS)
ENDIF(WIN32)

  CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/zconf.in.h
    ${CMAKE_CURRENT_BINARY_DIR}/zconf.h
  )
INCLUDE_DIRECTORIES(
 ${CMAKE_CURRENT_BINARY_DIR}
)


ADD_LIBRARY(${ZLIB_LIBRARY_NAME} ${ZLIB_SRCS})
INSTALL(TARGETS ${ZLIB_LIBRARY_NAME}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
	)
