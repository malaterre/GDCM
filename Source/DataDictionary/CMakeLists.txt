# Define the srcs for Data Dictionary
# DICT
SET(DICT_SRCS
  gdcmDicts.cxx
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  )

ADD_LIBRARY(gdcmDICT ${DICT_SRCS})
TARGET_LINK_LIBRARIES(gdcmDICT gdcmDSED)

