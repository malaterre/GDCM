INCLUDE_REGULAR_EXPRESSION("^.*$")
# Create the lib
SET(openjpeg_SRCS
  bio.c  cio.c  dwt.c  event.c  fix.c  image.c  int.c  j2k.c  j2k_lib.c  jp2.c  jpt.c  mct.c  mqc.c  openjpeg.c  pi.c  raw.c  t1.c  t2.c  tcd.c  tgt.c
)

IF (WIN32)
  IF (BUILD_SHARED_LIBS)
    ADD_DEFINITIONS(-DOPENJPEGDLL)
    #SET(JPEGDLL 1)
  ELSE (BUILD_SHARED_LIBS)
    ADD_DEFINITIONS(-DOPENJPEGSTATIC)
    #SET(JPEGSTATIC 1)
  ENDIF (BUILD_SHARED_LIBS)
ENDIF (WIN32)


ADD_LIBRARY(gdcmopenjpeg ${openjpeg_SRCS})

