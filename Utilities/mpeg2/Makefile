# Makefile for mpeg2decode / mpeg2encode

# Copyright (C) 1996, MPEG Software Simulation Group. All Rights Reserved.

#
# Disclaimer of Warranty
#
# These software programs are available to the user without any license fee or
# royalty on an "as is" basis.  The MPEG Software Simulation Group disclaims
# any and all warranties, whether express, implied, or statuary, including any
# implied warranties or merchantability or of fitness for a particular
# purpose.  In no event shall the copyright-holder be liable for any
# incidental, punitive, or consequential damages of any kind whatsoever
# arising from the use of these programs.
#
# This disclaimer of warranty extends to the user of these programs and user's
# customers, employees, agents, transferees, successors, and assigns.
#
# The MPEG Software Simulation Group does not represent or warrant that the
# programs furnished hereunder are free of infringement of any third-party
# patents.
#
# Commercial implementations of MPEG-1 and MPEG-2 video, including shareware,
# are subject to royalty fees to patent holders.  Many of these patents are
# general enough such that they are unavoidable regardless of implementation
# design.
#
#

# uncomment the following two lines if you want to include X11 support
# (mpeg2decode)

#USE_DISP = -DDISPLAY
#LIBS = -lX11

# uncomment the following two lines if you want to use shared memory
# (faster display if server and client run on the same machine)
# (mpeg2decode)

#USE_SHMEM = -DSH_MEM
#LIBS = -lXext -lX11

# if your X11 include files / libraries are in a non standard location:
# set INCLUDEDIR to -I followed by the appropriate include file path and
# set LIBRARYDIR to -L followed by the appropriate library path
# (mpeg2decode)

#INCLUDEDIR = -I/usr/openwin/include
#LIBRARYDIR = -L/usr/openwin/lib

# select one of the following CC CFLAGS settings

#
# GNU gcc
#
CC = gcc
CFLAGS = -O2

all: mpeg2decode mpeg2encode

mpeg2decode:
	cd src/mpeg2dec; make 'CC=$(CC)' \
	'CFLAGS=$(CFLAGS) $(USE_DISP) $(USE_SHMEM) $(INCLUDEDIR)' \
	'LIBS=$(LIBS)' 'LIBRARYDIR=$(LIBRARYDIR)'

mpeg2encode:
	cd src/mpeg2enc; make 'CC=$(CC)' 'CFLAGS=$(CFLAGS)'

pc:
	cd src/mpeg2dec; make pc 'CC=$(CC)' 'CFLAGS=$(CFLAGS)'
	cd src/mpeg2enc; make pc 'CC=$(CC)' 'CFLAGS=$(CFLAGS)'

clean:
	cd src/mpeg2dec; make clean
	cd src/mpeg2enc; make clean

test:
	cd verify; ./verify
