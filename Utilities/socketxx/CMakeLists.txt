# http://www.linuxhacker.at/socketxx
PROJECT(socketxx)

INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR})

OPTION(BUILD_SHARED_LIBS "Build with shared libraries." ON)


SUBDIRS( socket++ doc )

