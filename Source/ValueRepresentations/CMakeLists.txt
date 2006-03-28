#-----------------------------------------------------------------------------
# Rebuild gdcm whenever a file starting with gdcm* is modified
INCLUDE_REGULAR_EXPRESSION("^gdcm.*$")

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_BINARY_DIR}/Source/Common"
  )

SET(ValueRepresentations_SRCS
  gdcmPersonName.cxx
  )

ADD_LIBRARY(gdcmValueRepresentations ${ValueRepresentations_SRCS})
TARGET_LINK_LIBRARIES(gdcmValueRepresentations gdcmCommon)

