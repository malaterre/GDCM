INCLUDE_REGULAR_EXPRESSION("^.*$")

SET(MPEG2ENC_SRCS
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

ADD_LIBRARY(mpeg2enc ${MPEG2ENC_SRCS} )
IF(UNIX)
  TARGET_LINK_LIBRARIES(mpeg2enc -lm)
ENDIF(UNIX)

#ADD_EXECUTABLE(mpeg2encode mpeg2enc.c)
#TARGET_LINK_LIBRARIES(mpeg2encode mpeg2enc)
