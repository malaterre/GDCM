IF(NOT POLARSSL_NAMESPACE)
  SET(POLARSSL_NAMESPACE "POLARSSL")
  SET(POLARSSL_STANDALONE 1)
ENDIF(NOT POLARSSL_NAMESPACE)
# In all cases:
STRING(TOLOWER ${POLARSSL_NAMESPACE} POLARSSL_LIBRARY_NAME)

PROJECT(${POLARSSL_NAMESPACE} C)
CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

APPEND_COPYRIGHT(${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)

# Do full dependency headers.
INCLUDE_REGULAR_EXPRESSION("^.*$")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include/)
subdirs(library)
#
#DESTDIR=/usr/local
#PREFIX=polarssl_
#
#.SILENT:
#
#all:
#	cd library  && make all && cd ..
#	cd programs && make all && cd ..
#
#install:
#	mkdir -p $(DESTDIR)/include/polarssl
#	cp -r include/polarssl $(DESTDIR)/include
#	
#	mkdir -p $(DESTDIR)/lib
#	cp library/libpolarssl.* $(DESTDIR)/lib
#	
#	mkdir -p $(DESTDIR)/bin
#	for p in programs/*/* ; do              \
#	    if [ -x $$p ] && [ ! -d $$p ] ;     \
#	    then                                \
#	        f=$(PREFIX)`basename $$p` ;     \
#	        cp $$p $(DESTDIR)/bin/$$f ;     \
#	    fi                                  \
#	done
#
#clean:
#	cd library  && make clean && cd ..
#	cd programs && make clean && cd ..
#
