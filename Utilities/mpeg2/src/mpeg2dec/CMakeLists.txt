INCLUDE_REGULAR_EXPRESSION("^.*$")

SET(GDCM_MPEG2DEC_SOURCES
  getpic.c
  motion.c
  getvlc.c
  gethdr.c
  getblk.c
  getbits.c
  store.c
  recon.c
  spatscal.c
  idct.c
  idctref.c
  #  display.c
  systems.c
  subspic.c
  #  verify.c
  )

ADD_LIBRARY(gdcmmpeg2 ${GDCM_MPEG2DEC_SOURCES} mpeg2dec.c)
IF(UNIX)
  TARGET_LINK_LIBRARIES(gdcmmpeg2 -lm)
ENDIF(UNIX)

#ADD_DEFINITIONS(-DGDCM_BUILD_MPEG2DEC)
#ADD_EXECUTABLE(mpeg2decode ${GDCM_MPEG2DEC_SOURCES} mpeg2dec.c)
#TARGET_LINK_LIBRARIES(mpeg2decode -lm)
