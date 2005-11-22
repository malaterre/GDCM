#-----------------------------------------------------------------------------
# Rebuild gdcm whenever a file starting with gdcm* is modified
INCLUDE_REGULAR_EXPRESSION("^gdcm.*$")

# configure the .h file
CONFIGURE_FILE(
  "${GDCM_SOURCE_DIR}/Source/gdcmConfigure.h.in"
  "${GDCM_BINARY_DIR}/Source/gdcmConfigure.h"
  IMMEDIATE
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source"
  "${GDCM_SOURCE_DIR}/Source"
  )

ADD_CUSTOM_COMMAND(
  OUTPUT    ${GDCM_BINARY_DIR}/Source/gdcmDefaultDicts.cxx
  COMMAND   ${EXECUTABLE_OUTPUT_PATH}/PrepDict
  ARGS      ${GDCM_SOURCE_DIR}/Dicts/DataDict.dic
            ${GDCM_BINARY_DIR}/Source/gdcmDefaultDicts.cxx
  DEPENDS   ${GDCM_SOURCE_DIR}/Dicts/DataDict.dic
  COMMENT   "Generating gdcmDefaultDicts.cxx based on DataDict.dic"
  )

# Since the file gdcmDefaultDicts.cxx does not exist, mark it as GENERATED:
#SET_SOURCE_FILES_PROPERTIES(
#  "${GDCM_BINARY_DIR}/Source/gdcmDefaultDicts.cxx" GENERATED)


SET(SRCS
  gdcmIStream.cxx
  gdcmDICOMIStream.cxx
  gdcmOStream.cxx
  gdcmDICOMOStream.cxx
  gdcmVR.cxx
  gdcmVM.cxx
  gdcmTS.cxx
  #gdcmTag.cxx
  gdcmExplicitDataElement.cxx
  gdcmImplicitDataElement.cxx
  #gdcmSequenceDataElement.cxx
  #gdcmSequenceItem.cxx
  "${GDCM_BINARY_DIR}/Source/gdcmDefaultDicts.cxx"
  )

ADD_LIBRARY(gdcm ${SRCS})
