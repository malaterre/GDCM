# Define the srcs for Data Dictionary
# DICT
SET(DICT_SRCS
  gdcmDicts.cxx
  gdcmGroupDict.cxx
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  )

ADD_LIBRARY(gdcmDICT ${DICT_SRCS})
TARGET_LINK_LIBRARIES(gdcmDICT gdcmDSED)

#-----------------------------------------------------------------------------
# DICOM dictionary stuff
SET(DICT_SRCS
  ${GDCM_SOURCE_DIR}/Source/DataDictionary/gdcmDictConverter.cxx
  ${GDCM_SOURCE_DIR}/Source/DataDictionary/gdcmPrepDict.cxx
  )

ADD_EXECUTABLE(PrepDict ${DICT_SRCS}
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition/gdcmVR.cxx"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition/gdcmVM.cxx"
  )

ADD_EXECUTABLE(PrepGroupName
  ${GDCM_SOURCE_DIR}/Source/DataDictionary/gdcmPrepGroupName.cxx
  )

