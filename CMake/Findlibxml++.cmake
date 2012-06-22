#
#  Copyright (c) 2006-2011 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

#locate libxml++ library

# This module defines
#  LIBXMLPP_LIBRARY
#  LIBXMLPP_FOUND
#  LIBXMLPP_INCLUDE_DIR
#  LIBXMLPP_CFLAGS
#  LIBXMLPP_LINKFLAGS


IF(LIBXMLPP_LIBRARY AND LIBXMLPP_INCLUDE_DIR)
	SET(LIBXMLPP_FOUND TRUE)
ELSE(LIBXMLPP_LIBRARY AND LIBXMLPP_INCLUDE_DIR)
	INCLUDE(UsePkgConfig)
	PKGCONFIG("libxml++-2.6" _LibXmlppIncDir _LibXmlppLibDir _LibXmlppLinkFlags _LibXmlppCflags)

	# set additional flags needed to compile/link against libxml++
	SET(LIBXMLPP_CFLAGS ${_LibXmlppCFlags} CACHE STRING "CFLAGS required for libxml++")
	SET(LIBXMLPP_LINKFLAGS ${_LibXmlppLinkFlags} CACHE STRING "Flags used for linking against libxml++")

	# search for include and library path
	FIND_PATH(LIBXMLPP_INCLUDE_DIR libxml++/libxml++.h PATHS ${_LibXmlppIncDir} ${_LibXmlppIncDir}/libxml++-2.6)
	FIND_LIBRARY(LIBXMLPP_LIBRARY xml++-2.6 PATHS ${_LibXmlppLibDir})

	IF(LIBXMLPP_INCLUDE_DIR AND LIBXMLPP_LIBRARY)
		SET(LIBXMLPP_FOUND TRUE)
		MESSAGE(STATUS "Found LibXml++: ${LIBXMLPP_LIBRARY}")

	ELSE(LIBXMLPP_INCLUDE_DIR AND LIBXMLPP_LIBRARY)
		SET(LIBXMLPP_FOUND FALSE)
		MESSAGE(SEND_ERROR "Could NOT find LibXml++")
	ENDIF(LIBXMLPP_INCLUDE_DIR AND LIBXMLPP_LIBRARY)
ENDIF(LIBXMLPP_LIBRARY AND LIBXMLPP_INCLUDE_DIR)
