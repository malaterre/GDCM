# Define the srcs for Data Structure and Encoding Definitions
# DSED
SET(DSED_SRCS
  gdcmVR.cxx
  gdcmVM.cxx
  gdcmExplicitDataElement.cxx
  gdcmImplicitDataElement.cxx
  gdcmDataSet.cxx
  gdcmTS.cxx
  gdcmParser.cxx
  gdcmReader.cxx
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_BINARY_DIR}/Source/Common"
  )

ADD_LIBRARY(gdcmDSED ${DSED_SRCS})
TARGET_LINK_LIBRARIES(gdcmDSED gdcmCommon)

