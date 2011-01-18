# Makefile for mpeg2encode (user contribution, untested)
#
# WATCOM C/386++
#
INC      = C:\OR386\INCLUDE

LINKFILE = temp.lnk
CC = WCC386P
LL = WLINKP system dos4g

!ifdef DEBUG
CFLAGS = -w4 -zq -4r -d2 -I$(INC)
!else
CFLAGS = -w4 -zq -4r -oaxt -I$(INC)
!endif

OBJ = mpeg2enc.obj conform.obj putseq.obj putpic.obj puthdr.obj putmpg.obj 
putvlc.obj putbits.obj motion.obj predict.obj readpic.obj 
writepic.obj transfrm.obj fdctref.obj idct.obj quantize.obj 
ratectl.obj stats.obj

mpeg2enc.exe: $(OBJ)
        %create $(LINKFILE)
    %append $(LINKFILE) debug all
    %append $(LINKFILE) opt stack=32000
        %append $(LINKFILE) opt caseexact
        %append $(LINKFILE) opt map=$^&.MAP
    %append $(LINKFILE) NAME $^&
        for %i in ($(OBJ)) do %append $(LINKFILE) FILE %i
        $(LL) @$(LINKFILE)

conform.obj: conform.c config.h mpeg2enc.h global.h
       $(CC) $(CFLAGS) $*.c

fdctref.obj: fdctref.c config.h
       $(CC) $(CFLAGS) $*.c

idct.obj: idct.c config.h
       $(CC) $(CFLAGS) $*.c

motion.obj: motion.c config.h mpeg2enc.h global.h
       $(CC) $(CFLAGS) $*.c

mpeg2enc.obj: mpeg2enc.c config.h mpeg2enc.h global.h
       $(CC) $(CFLAGS) $*.c

predict.obj: predict.c config.h mpeg2enc.h global.h
       $(CC) $(CFLAGS) $*.c

putbits.obj: putbits.c config.h
       $(CC) $(CFLAGS) $*.c

puthdr.obj: puthdr.c config.h mpeg2enc.h global.h
       $(CC) $(CFLAGS) $*.c

putmpg.obj: putmpg.c config.h mpeg2enc.h global.h
       $(CC) $(CFLAGS) $*.c

putpic.obj: putpic.c config.h mpeg2enc.h global.h
       $(CC) $(CFLAGS) $*.c

putseq.obj: putseq.c config.h mpeg2enc.h global.h
       $(CC) $(CFLAGS) $*.c

putvlc.obj: putvlc.c config.h mpeg2enc.h global.h vlc.h
       $(CC) $(CFLAGS) $*.c

quantize.obj: quantize.c config.h mpeg2enc.h global.h
       $(CC) $(CFLAGS) $*.c

ratectl.obj: ratectl.c config.h mpeg2enc.h global.h
       $(CC) $(CFLAGS) $*.c

readpic.obj: readpic.c config.h mpeg2enc.h global.h
       $(CC) $(CFLAGS) $*.c

stats.obj: stats.c config.h mpeg2enc.h global.h
       $(CC) $(CFLAGS) $*.c

transfrm.obj: transfrm.c config.h mpeg2enc.h global.h
       $(CC) $(CFLAGS) $*.c

writepic.obj: writepic.c config.h mpeg2enc.h global.h
       $(CC) $(CFLAGS) $*.c

