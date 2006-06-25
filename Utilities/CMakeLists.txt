# Wrapping and stuff

SUBDIRS(Wrapping)
# Do jpeg (8,12, 16 lossly lossless)
SET(JPEG_NAMESPACE "GDCMJPEG")
SUBDIRS(jpeg)

# Do expat
SET(EXPAT_NAMESPACE "GDCMEXPAT")
SUBDIRS(expat)
