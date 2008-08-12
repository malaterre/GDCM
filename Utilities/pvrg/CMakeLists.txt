SET(
  PVRG_SRCS
  jpeg.c
  codec.c
  huffman.c
  io.c
  chendct.c
  leedct.c
  lexer.c
  marker.c
  stream.c
  transform.c
)

ADD_EXECUTABLE(pvrgjpeg ${PVRG_SRCS})

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
