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
#SET_TARGET_PROPERTIES(${MPEG2_LIBRARY_NAME} PROPERTIES ${GDCM_LIBRARY_PROPERTIES})
IF(UNIX)
  TARGET_LINK_LIBRARIES(mpeg2enc -lm)
ENDIF(UNIX)

#ADD_EXECUTABLE(mpeg2encode mpeg2enc.c)
#TARGET_LINK_LIBRARIES(mpeg2encode mpeg2enc)

INSTALL(TARGETS mpeg2enc
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
  ${CPACK_NAMELINK_TYPE}
	)

  FILE(GLOB header_files "*.h" )
  INSTALL(FILES ${header_files}
    DESTINATION include COMPONENT Development
  )

