#-----------------------------------------------------------------------------
# Rebuild gdcm whenever a file starting with gdcm* is modified
INCLUDE_REGULAR_EXPRESSION("^gdcm.*$")

#-----------------------------------------------------------------------------
# DICOM dictionary stuff
SET(DICT_SRCS
  ${GDCM_SOURCE_DIR}/Dicts/gdcmPrepDict.cxx
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source"
  "${GDCM_SOURCE_DIR}/Source"
  )

ADD_EXECUTABLE(PrepDict ${DICT_SRCS}
  "${GDCM_SOURCE_DIR}/Source/gdcmVR.cxx"
  "${GDCM_SOURCE_DIR}/Source/gdcmVM.cxx"
  )

ADD_EXECUTABLE(PrepGroupName
  ${GDCM_SOURCE_DIR}/Dicts/gdcmPrepGroupName.cxx
  )

