# FIXME:
#CONFIGURE_FILE(
#  ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
#  ${CMAKE_CURRENT_BINARY_DIR}/config.h
#  )

INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	)

SET(libsocket___la_SOURCES
  sockstream.cpp sockstream.h
  sockinet.cpp sockinet.h
  pipestream.cpp pipestream.h
  fork.cpp fork.h
  protocol.cpp protocol.h
  echo.cpp echo.h
  smtp.cpp smtp.h
  ftp.cpp ftp.h
  #sig.cpp sig.h
  )

IF(UNIX)
  SET(libsocket___la_SOURCES
    ${libsocket___la_SOURCES}
    #sockunix.cpp sockunix.h
    )
ENDIF(UNIX)

ADD_LIBRARY(${SOCKETXX_LIBRARY_NAME} ${libsocket___la_SOURCES})
SET_TARGET_PROPERTIES(${SOCKETXX_LIBRARY_NAME} PROPERTIES ${SOCKETXX_LIBRARY_PROPERTIES} LINK_INTERFACE_LIBRARIES "")
if(WIN32)
target_link_libraries(${SOCKETXX_LIBRARY_NAME} wsock32)
endif(WIN32)
#libsocketincludedir=$(includedir)/socket++
#libsocketinclude_HEADERS = \
#	sockstream.h \
#	sockinet.h \
#	sockunix.h\
#	pipestream.h \
#	fork.h \
#	protocol.h \
#	echo.h \
#	smtp.h \
#	ftp.h \
#	sig.h
#libsocket___la_LDFLAGS = -version-info @LIBSOCKET_SO_VERSION@
#libsocket___la_LIBADD =

# Install library
IF(NOT SOCKETXX_INSTALL_NO_LIBRARIES)
  # Runtime
  INSTALL(TARGETS ${SOCKETXX_LIBRARY_NAME}
    EXPORT GDCMTargets
    RUNTIME DESTINATION ${SOCKETXX_INSTALL_BIN_DIR} COMPONENT Applications
    LIBRARY DESTINATION ${SOCKETXX_INSTALL_LIB_DIR} COMPONENT Libraries ${NAMELINK_SKIP}
    ARCHIVE DESTINATION ${SOCKETXX_INSTALL_LIB_DIR} COMPONENT Development
  )
  #Development
  if(NAMELINK_ONLY)
    INSTALL(TARGETS ${SOCKETXX_LIBRARY_NAME}
    EXPORT GDCMTargets
      LIBRARY DESTINATION ${SOCKETXX_INSTALL_LIB_DIR} COMPONENT Development ${NAMELINK_ONLY}
    )
  endif(NAMELINK_ONLY)
ENDIF(NOT SOCKETXX_INSTALL_NO_LIBRARIES)

IF(NOT SOCKETXX_INSTALL_NO_DEVELOPMENT)
  FILE(GLOB header_files "*.h")
  INSTALL(FILES ${header_files}
    DESTINATION ${SOCKETXX_INSTALL_INCLUDE_DIR}/gdcmcharls COMPONENT Headers
  )
ENDIF(NOT SOCKETXX_INSTALL_NO_DEVELOPMENT)

