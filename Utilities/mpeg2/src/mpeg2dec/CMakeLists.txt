INCLUDE_REGULAR_EXPRESSION("^.*$")

SET(MPEG2DEC_SRCS
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

ADD_LIBRARY(${MPEG2_LIBRARY_NAME} ${MPEG2DEC_SRCS} mpeg2dec.c)
#SET_TARGET_PROPERTIES(${MPEG2_LIBRARY_NAME} PROPERTIES ${GDCM_LIBRARY_PROPERTIES})
IF(UNIX)
  TARGET_LINK_LIBRARIES(${MPEG2_LIBRARY_NAME} -lm)
ENDIF(UNIX)
INSTALL(TARGETS ${MPEG2_LIBRARY_NAME}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
  ${CPACK_NAMELINK_TYPE}
	)

  FILE(GLOB header_files "*.h" )
  INSTALL(FILES ${header_files}
    DESTINATION include COMPONENT Development
  )

#ADD_DEFINITIONS(-DBUILD_MPEG2DEC)
#ADD_EXECUTABLE(mpeg2decode ${MPEG2DEC_SRCS} mpeg2dec.c)
#TARGET_LINK_LIBRARIES(mpeg2decode -lm)
