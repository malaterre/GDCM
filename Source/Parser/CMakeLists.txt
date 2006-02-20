#-----------------------------------------------------------------------------
# Rebuild gdcm whenever a file starting with gdcm* is modified
INCLUDE_REGULAR_EXPRESSION("^gdcm.*$")

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_BINARY_DIR}/Source/Parser"
  "${GDCM_SOURCE_DIR}/Source/Parser"
  #"${GDCM_SOURCE_DIR}/Source/Objects"
  )

IF(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 2.1)
  GET_TARGET_PROPERTY( PREP_DICT
    PrepDict
    LOCATION
    )
  GET_TARGET_PROPERTY( PREP_GROUPNAME
    PrepGroupName
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
  OUTPUT    ${GDCM_BINARY_DIR}/Source/Parser/gdcmDefaultDicts.cxx
  COMMAND   ${PREP_DICT}
  ARGS      ${GDCM_SOURCE_DIR}/Source/Dicts/DataDict.dic
            ${GDCM_BINARY_DIR}/Source/Parser/gdcmDefaultDicts.cxx
  DEPENDS   ${GDCM_SOURCE_DIR}/Source/Dicts/DataDict.dic
            ${GDCM_SOURCE_DIR}/Source/Dicts/gdcmPrepDict.cxx
  COMMENT   "Generating gdcmDefaultDicts.cxx based on DataDict.dic"
  )

ADD_CUSTOM_COMMAND(
  OUTPUT    ${GDCM_BINARY_DIR}/Source/Parser/gdcmDefaultGroupNames.cxx
  COMMAND   ${PREP_GROUPNAME}
  ARGS      ${GDCM_SOURCE_DIR}/Source/Dicts/GroupName.dic
            ${GDCM_BINARY_DIR}/Source/Parser/gdcmDefaultGroupNames.cxx
  DEPENDS   ${GDCM_SOURCE_DIR}/Source/Dicts/GroupName.dic
            ${GDCM_SOURCE_DIR}/Source/Dicts/gdcmPrepGroupName.cxx
  COMMENT   "Generating gdcmDefaultGroupNames.cxx based on GroupName.dic"
  )


# Since the file gdcmDefaultDicts.cxx does not exist, mark it as GENERATED:
#SET_SOURCE_FILES_PROPERTIES(
#  "${GDCM_BINARY_DIR}/Source/gdcmDefaultDicts.cxx" GENERATED)


SET(SRCS
  gdcmDICOMIStream.cxx
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
  gdcmFileSeeker.cxx
  gdcmLoader.cxx
  gdcmPrinter.cxx
  gdcmAttribute.cxx
  "${GDCM_BINARY_DIR}/Source/Parser/gdcmDefaultDicts.cxx"
  "${GDCM_BINARY_DIR}/Source/Parser/gdcmDefaultGroupNames.cxx"
  )

ADD_LIBRARY(gdcmParser ${SRCS})
TARGET_LINK_LIBRARIES(gdcmParser gdcmCommon gdcmObjects)
