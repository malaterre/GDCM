INCLUDE_REGULAR_EXPRESSION("^.*$")

SET(JPEGLS_ENC_SRCS 
  global.c 
  jpegmark.c 
  initialize.c 
  encoder.c 
  lossless_e.c 
  lossy_e.c 
  bitio.c 
  melcode.c 
  )

ADD_LIBRARY(jpegls_enc ${JPEGLS_ENC_SRCS})

