INCLUDE_REGULAR_EXPRESSION("^.*$")


SET(SRCS 
  global.c 
  jpegmark.c 
  initialize.c 
  encoder.c 
  lossless_e.c 
  lossy_e.c 
  bitio.c 
  melcode.c 
  )

ADD_LIBRARY(gdcmjpegls2 ${SRCS})

