
SET(
  PVRG_SRCS
  jpeg.c
  codec.c
  huffman.c
  io.c
  chendct.c
  leedct.c
  marker.c
  stream.c
  transform.c
  lexer.c
)


# might not be portable, so simply rename the function in the code itself...
#SET_SOURCE_FILES_PROPERTIES(jpeg.c
#  PROPERTIES
#  COMPILE_FLAGS -Dmain=pvrgmain
#)
IF(MSVC)
ADD_DEFINITIONS(-DNOTRUNCATE)
ELSE(MSVC)
ADD_DEFINITIONS(-DSYSV -DNOTRUNCATE)
ENDIF(MSVC)
#ADD_DEFINITIONS(-DIO_DEBUG)
#ADD_LIBRARY(pvrg ${PVRG_SRCS})

ADD_EXECUTABLE(gdcmjpeg ${PVRG_SRCS})
#TARGET_LINK_LIBRARIES(pvrgjpeg pvrg)


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
