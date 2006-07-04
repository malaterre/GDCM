CC=cc
PKGNAME=loco
OPTFLAGS= -Aa $(CFL) -DBIG_ENDIAN

CFLAGS  = $(OPTFLAGS) $(VFL) $(DFL) -DPGMPREFIX=\"$(PREFIX)\" -DMELCODE -DEXTERNDISTRIB -Dinline="" -DNDEBUG

LNKFLAGS = -lm

SRCS = global.c jpegmark.c initialize.c encoder.c lossless_e.c lossy_e.c bitio.c melcode.c 
INCL = global.h jpegmark.h bitio.h

EOBJS = global.o jpegmark.o initialize.o encoder.o lossless_e.o lossy_e.o bitio.o melcode.o

loco:
	$(MAKE) -$(MAKEFLAGS) VFL="" PREFIX="loco" codec

ENCODER = $(PREFIX)e

codec: $(ENCODER)

jpegmark.o: jpegmark.c jpegmark.h bitio.h global.h

global.o: global.h global.c

initialize.o: initialize.c bitio.h global.h

lossless_e.o: global.h lossless_e.c bitio.h 

lossy_e.o: global.h lossy_e.c bitio.h

encoder.o: encoder.c jpegmark.c global.h 

bitio.o: bitio.c bitio.h global.h

melcode.o: melcode.c bitio.h global.h


$(ENCODER): $(EOBJS)
	$(CC) $(CFLAGS) -o $@ $(EOBJS) $(LNKFLAGS)

lint:
	lint $(SRCS)
clean:
	-rm -f *.o core loco* *.out
