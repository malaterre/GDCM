#-----------------------------------------------------------------------------
# Rebuild gdcm whenever a file starting with gdcm* is modified
INCLUDE_REGULAR_EXPRESSION("^gdcm.*$")

# configure the .h file
CONFIGURE_FILE(
  "${GDCM_SOURCE_DIR}/Source/gdcmConfigure.h.in"
  "${GDCM_BINARY_DIR}/Source/gdcmConfigure.h"
  IMMEDIATE
  )

# add the include path to find the .h
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source"
  "${GDCM_SOURCE_DIR}/Source"
  )


SET(SRCS
  gdcmIStream.cxx
  gdcmOStream.cxx
  gdcmVR.cxx
  gdcmVM.cxx
  gdcmTS.cxx
  gdcmExplicitDataElement.cxx
  "${GDCM_BINARY_DIR}/Source/gdcmDefaultDicts.cxx"
  )

ADD_LIBRARY(gdcm ${SRCS})
