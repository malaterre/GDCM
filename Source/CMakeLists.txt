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

IF(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 2.1)
  GET_TARGET_PROPERTY( PREP_DICT
    PrepDict
    LOCATION
    )
  GET_TARGET_PROPERTY( PREP_GROUPNAME
    PrepDict
    LOCATION
    )
ELSE(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 2.1)
  SET( PREP_DICT
    "${EXECUTABLE_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/PrepDict"
    )
  SET(PREP_GROUPNAME
    "${EXECUTABLE_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/PrepGroupName"
    )
ENDIF(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 2.1)

ADD_CUSTOM_COMMAND(
  OUTPUT    ${GDCM_BINARY_DIR}/Source/gdcmDefaultDicts.cxx
  COMMAND   ${PREP_DICT}
  ARGS      ${GDCM_SOURCE_DIR}/Dicts/DataDict.dic
            ${GDCM_BINARY_DIR}/Source/gdcmDefaultDicts.cxx
  DEPENDS   ${GDCM_SOURCE_DIR}/Dicts/DataDict.dic
            ${GDCM_SOURCE_DIR}/Dicts/gdcmPrepDict.cxx
  COMMENT   "Generating gdcmDefaultDicts.cxx based on DataDict.dic"
  )

ADD_CUSTOM_COMMAND(
  OUTPUT    ${GDCM_BINARY_DIR}/Source/gdcmDefaultGroupNames.cxx
  COMMAND   ${PREP_GROUPNAME}
  ARGS      ${GDCM_SOURCE_DIR}/Dicts/GroupName.dic
            ${GDCM_BINARY_DIR}/Source/gdcmDefaultGroupNames.cxx
  DEPENDS   ${GDCM_SOURCE_DIR}/Dicts/GroupName.dic
            ${GDCM_SOURCE_DIR}/Dicts/gdcmPrepGroupName.cxx
  COMMENT   "Generating gdcmDefaultGroupNames.cxx based on GroupName.dic"
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
  gdcmTag.cxx
  gdcmGroupDict.cxx
  gdcmExplicitDataElement.cxx
  gdcmImplicitDataElement.cxx
  #gdcmSequenceDataElement.cxx
  #gdcmSequenceItem.cxx
  "${GDCM_BINARY_DIR}/Source/gdcmDefaultDicts.cxx"
  "${GDCM_BINARY_DIR}/Source/gdcmDefaultGroupNames.cxx"
  )

ADD_LIBRARY(gdcm ${SRCS})
