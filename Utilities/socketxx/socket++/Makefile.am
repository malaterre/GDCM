INCLUDES = -I$(top_srcdir) -I$(top_builddir)

lib_LTLIBRARIES = libsocket++.la
libsocket___la_SOURCES = sockstream.cpp sockstream.h \
	sockinet.cpp sockinet.h \
	sockunix.cpp sockunix.h\
	pipestream.cpp pipestream.h \
	fork.cpp fork.h \
	protocol.cpp protocol.h \
	echo.cpp echo.h \
	smtp.cpp smtp.h \
	ftp.cpp ftp.h \
	sig.cpp sig.h

libsocketincludedir=$(includedir)/socket++
libsocketinclude_HEADERS = \
	sockstream.h \
	sockinet.h \
	sockunix.h\
	pipestream.h \
	fork.h \
	protocol.h \
	echo.h \
	smtp.h \
	ftp.h \
	sig.h
libsocket___la_LDFLAGS = -version-info @LIBSOCKET_SO_VERSION@
libsocket___la_LIBADD =

