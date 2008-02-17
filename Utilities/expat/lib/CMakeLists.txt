
SET(EXPAT_SRCS
  xmlparse.c
  xmltok.c
  xmlrole.c
)

# for windows add the .def and .rc files to the source list if building shared libs
IF(WIN32)
  IF(BUILD_SHARED_LIBS)
    SET(EXPAT_DLL 1)
    IF(NOT UNIX)
      IF(NOT BORLAND)
        IF(NOT MINGW)
          SET(EXPAT_SRCS ${EXPAT_SRCS} libexpat.def )
        ENDIF(NOT MINGW)
      ENDIF(NOT BORLAND) 
    ENDIF(NOT UNIX)   
  ENDIF(BUILD_SHARED_LIBS)
ENDIF(WIN32)

ADD_LIBRARY(${EXPAT_LIBRARY_NAME} ${EXPAT_SRCS})
INSTALL(TARGETS ${EXPAT_LIBRARY_NAME}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
	)
