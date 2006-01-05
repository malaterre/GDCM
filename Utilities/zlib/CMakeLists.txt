PROJECT(GDCMZLIB)
INCLUDE_REGULAR_EXPRESSION("^(gdcm|deflate|inf|trees|zconf|zlib|zutil).*$")

INCLUDE_DIRECTORIES(${GDCMZLIB_SOURCE_DIR})

# source files for zlib
SET(ZLIB_SRCS
  adler32.c  compress.c  crc32.c  deflate.c  gzio.c  infback.c  inffast.c  inflate.c  inftrees.c  minigzip.c  trees.c  uncompr.c  zutil.c
  )

# for windows add the .def and .rc files to the source list if building shared libs
#IF(WIN32)
#  IF(BUILD_SHARED_LIBS)
#    SET(ZLIB_DLL 1)
#    IF(NOT UNIX)
#      IF(NOT BORLAND)
#        IF(NOT MINGW)
#          SET(ZLIB_SRCS ${ZLIB_SRCS} zlib.def zlib.rc  )
#        ENDIF(NOT MINGW)
#      ENDIF(NOT BORLAND) 
#    ENDIF(NOT UNIX)   
#  ENDIF(BUILD_SHARED_LIBS)
#ENDIF(WIN32)

#CONFIGURE_FILE(${VTKZLIB_SOURCE_DIR}/zlibDllConfig.h.in
#  ${VTKZLIB_BINARY_DIR}/zlibDllConfig.h)


ADD_LIBRARY(gdcmzlib ${ZLIB_SRCS})
