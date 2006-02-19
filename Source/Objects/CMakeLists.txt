#-----------------------------------------------------------------------------
# Rebuild gdcm whenever a file starting with gdcm* is modified
INCLUDE_REGULAR_EXPRESSION("^gdcm.*$")

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Objects"
  "${GDCM_SOURCE_DIR}/Source/Parser"
  )

SET(SRCS
  gdcmAttribute.cxx
  )

ADD_LIBRARY(gdcmObjects ${SRCS})
TARGET_LINK_LIBRARIES(gdcmObjects gdcmCommon)
