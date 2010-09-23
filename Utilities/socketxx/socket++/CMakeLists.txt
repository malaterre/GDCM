# common
SET(VERSION "1.12.12")
SET(PACKAGE "socket++")

# specific
IF(WIN32)
ELSE(WIN32)
  # FIXME this should be try_compile:
  SET(EXTERN_C_BEGIN)
  SET(SYS_SIGLIST sys_siglist)
  SET(SIGHND_ARGTYPE int)
  SET(SYS_ERRLIST sys_errlist)
  SET(SYS_ERRLIST_DECLARED 1)
  SET(_S_LIBGXX 0)
  SET(HAVE_DLFCN_H 1)
  SET(HAVE_FORK 1)
  SET(HAVE_MEMORY_H 1)
  SET(HAVE_SELECT 1)
  SET(HAVE_SSTREAM 1)
  SET(HAVE_STDINT_H 1)
  SET(HAVE_STDLIB_H 1)
  SET(HAVE_STRING 1)
  SET(HAVE_STRINGS_H 1)
  SET(HAVE_STRING_H 1)
  SET(HAVE_SYS_STAT_H 1)
  SET(HAVE_SYS_TYPES_H 1)
  SET(HAVE_SYS_WAIT_H 1)
  SET(HAVE_UNISTD_H 1)
  SET(HAVE_VFORK 1)
  SET(HAVE_VFORK_H 0)
  SET(HAVE_WORKING_FORK 1)
  SET(HAVE_WORKING_VFORK 1)
  SET(RETSIGTYPE void)
  SET(STDC_HEADERS 1)
ENDIF(WIN32)

CONFIGURE_FILE(
  ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/config.h
  )

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
#target_link_libraries(${SOCKETXX_LIBRARY_NAME} wsock32)
target_link_libraries(${SOCKETXX_LIBRARY_NAME} ws2_32.lib)
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

