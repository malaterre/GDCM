###########################################################
# The makefile for the JPEG program.
# There should be no changes for most UNIX compilers.
###########################################################
#
#  For sysv substitute the following terms: 
#  SYSV allows for SYSV system IO calls.  NOTRUNCATE allows
#  for UNIX emulators without the ftruncate() call.
#
#DEFINES = -DSYSV -DNOTRUNCATE
#

DEFINES = 
JFLAGS = -O
DEFS = system.h globals.h prototypes.h param.h
BASELINE =  jpeg.o codec.o huffman.o io.o chendct.o leedct.o lexer.o marker.o stream.o transform.o

.c.o:
	cc $(JFLAGS) $(DEFINES) -c $*.c 

.c.ln:
	lint -c $*.c 

all: jpeg

clean:
	rm *.o jpeg

jpeg: $(BASELINE) 
	cc $(DEFINES) $(JFLAGS) $(BASELINE) -lm -o jpeg

jpeg.o: jpeg.c $(DEFS) tables.h
codec.o: codec.c $(DEFS)
huffman.o: huffman.c $(DEFS) stream.h
io.o: io.c $(DEFS)
chendct.o: chendct.c $(DEFS)
leedct.o: leedct.c $(DEFS)
lexer.o: lexer.c $(DEFS) tables.h stream.h
marker.o: marker.c $(DEFS) marker.h stream.h
stream.o: stream.c $(DEFS) marker.h stream.h
transform.o: transform.c dct.h $(DEFS)

lcheck: jpeg.ln codec.ln huffman.ln io.ln chendct.ln leedct.ln lexer.ln marker.ln stream.ln transform.ln
	lint jpeg.ln codec.ln huffman.ln io.ln chendct.ln leedct.ln lexer.ln marker.ln stream.ln transform.ln

#
# Should you wish to modify the interpreter
# modify this portion here.
#
# Make sure that you move the first comment from the start to 
# within the braces %{ /* */ %} in lexer.l,
# otherwise it will give you a error (definitions too long). 
#
#  Caution: Sometimes -ll is required.
#
#
#lexer.c: lexer.l
#	lex lexer.l
#	mv lex.yy.c lexer.c
#
