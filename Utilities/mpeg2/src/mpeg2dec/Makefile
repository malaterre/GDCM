# Makefile for mpeg2decode

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

#WARNINGS = -Wall
#VERIFY = -DVERIFY

#disable this flag if you do not want bitstream element tracing 
#this will speed up the decoder some since it does not have to test
#the trace flag at several critical inner loop locations.
TRACE = -DTRACE

#disable this flag if you do not need verbose trace, such as
#header information
VERBOSE = -DVERBOSE

# uncomment the following two lines if you want to include X11 support

#USE_DISP = -DDISPLAY
#LIBS = -lX11

# uncomment the following two lines if you want to use shared memory
# (faster display if server and client run on the same machine)

#USE_SHMEM = -DSH_MEM
#LIBS = -lXext -lX11

# if your X11 include files / libraries are in a non standard location:
# set INCLUDEDIR to -I followed by the appropriate include file path and
# set LIBRARYDIR to -L followed by the appropriate library path and

#INCLUDEDIR = -I/usr/openwin/include
#LIBRARYDIR = -L/usr/openwin/lib

#
# GNU gcc
#
CC = gcc
CFLAGS = -O2 $(USE_DISP) $(USE_SHMEM) $(INCLUDEDIR) $(TRACE) $(VERBOSE) $(VERIFY) $(WARNINGS)

OBJ = mpeg2dec.o getpic.o motion.o getvlc.o gethdr.o getblk.o getbits.o store.o recon.o spatscal.o idct.o idctref.o display.o systems.o subspic.o verify.o

all: mpeg2decode

pc: mpeg2dec.exe

clean:
	rm -f *.o *% core mpeg2decode

mpeg2dec.exe: mpeg2decode
	coff2exe mpeg2dec

mpeg2decode: $(OBJ)
	$(CC) $(CFLAGS) $(LIBRARYDIR) -o mpeg2decode $(OBJ) -lm $(LIBS)

display.o : display.c config.h global.h mpeg2dec.h 
getbits.o : getbits.c config.h global.h mpeg2dec.h 
getblk.o : getblk.c config.h global.h mpeg2dec.h 
gethdr.o : gethdr.c config.h global.h mpeg2dec.h 
getpic.o : getpic.c config.h global.h mpeg2dec.h 
getvlc.o : getvlc.c config.h global.h mpeg2dec.h getvlc.h 
idct.o : idct.c config.h 
idctref.o : idctref.c config.h 
motion.o : motion.c config.h global.h mpeg2dec.h 
mpeg2dec.o : mpeg2dec.c config.h global.h mpeg2dec.h 
recon.o : recon.c config.h global.h mpeg2dec.h 
spatscal.o : spatscal.c config.h global.h mpeg2dec.h 
store.o : store.c config.h global.h mpeg2dec.h 

# additions since July 4, 1994 edition
systems.o : systems.c config.h global.h mpeg2dec.h 
subspic.o : subspic.c config.h global.h mpeg2dec.h 
verify.o:   verify.c config.h global.h mpeg2dec.h
