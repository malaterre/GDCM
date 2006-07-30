PROJECT(RLE)

ADD_LIBRARY(rle rle.c)

ADD_EXECUTABLE(example example.c)
TARGET_LINK_LIBRARIES(example rle)
