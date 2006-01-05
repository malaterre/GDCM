INCLUDE_REGULAR_EXPRESSION("^.*$")

SET(GDCM_MPEG2ENC_SOURCES
  conform.c
  putseq.c
  putpic.c
  puthdr.c
  putmpg.c
  putvlc.c
  putbits.c
  motion.c
  predict.c
  readpic.c
  writepic.c
  transfrm.c
  fdctref.c
  idct.c
  quantize.c
  ratectl.c
  stats.c
  )
ADD_LIBRARY(gdcmmpeg2enc ${GDCM_MPEG2ENC_SOURCES} )
IF(UNIX)
  TARGET_LINK_LIBRARIES(gdcmmpeg2enc -lm)
ENDIF(UNIX)

#ADD_EXECUTABLE(mpeg2encode mpeg2enc.c)
#TARGET_LINK_LIBRARIES(mpeg2encode gdcmmpeg2enc)
