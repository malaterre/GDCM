# Build the GDCM applications
# Namely:
# gdcmdump
# gdcminfo
# gdcmconv


IF(WIN32 AND NOT CYGWIN)
  INCLUDE_DIRECTORIES(
    "${GDCM_SOURCE_DIR}/Utilities/getopt"
  )
ENDIF(WIN32 AND NOT CYGWIN)

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat"
  "${GDCM_SOURCE_DIR}/Source/InformationObjectDefinition"
# FIXME:
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Utilities"
  )

IF(WIN32)
  IF (BUILD_SHARED_LIBS)
    ADD_DEFINITIONS(-DGETOPT_DLL)
  ENDIF (BUILD_SHARED_LIBS)
ENDIF(WIN32)

SET(GDCM_EXECUTABLE_NAME
  gdcmdump
  gdcmraw
  gdcmscanner
  #gdcmoverlay
  gdcmimg
  #deflate
  gdcmconv
  gdcmtar
  gdcminfo
  )
IF(GDCM_USE_SYSTEM_POPPLER)
  INCLUDE_DIRECTORIES(${POPPLER_INCLUDE_DIRS})
  SET(GDCM_EXECUTABLE_NAME
  ${GDCM_EXECUTABLE_NAME}
  gdcmpdf
)
ENDIF(GDCM_USE_SYSTEM_POPPLER)

FOREACH(exename ${GDCM_EXECUTABLE_NAME})
  IF(${exename} STREQUAL "gdcminfo")
    ADD_EXECUTABLE(${exename} ${exename}.cxx puff.c)
  ELSE(${exename} STREQUAL "gdcminfo")
    ADD_EXECUTABLE(${exename} ${exename}.cxx)
  ENDIF(${exename} STREQUAL "gdcminfo")
  TARGET_LINK_LIBRARIES(${exename} gdcmMSFF)
  IF(${exename} STREQUAL "gdcmpdf")
    TARGET_LINK_LIBRARIES(${exename} ${POPPLER_LIBRARIES})
  ENDIF(${exename} STREQUAL "gdcmpdf")
  SET_TARGET_PROPERTIES(${exename} PROPERTIES ${GDCM_EXECUTABLE_PROPERTIES})
  IF(WIN32 AND NOT CYGWIN)
    TARGET_LINK_LIBRARIES(${exename} gdcmgetopt)
  ENDIF(WIN32 AND NOT CYGWIN)
  IF(NOT GDCM_INSTALL_NO_RUNTIME)
    INSTALL(TARGETS ${exename}
      RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
      LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime
      ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
    )
  ENDIF(NOT GDCM_INSTALL_NO_RUNTIME)
ENDFOREACH(exename)

#IF(GDCM_USE_PVRG)
#  ADD_EXECUTABLE(gdcmpvrg gdcmpvrg.cxx)
#  TARGET_LINK_LIBRARIES(gdcmpvrg pvrg)
#ENDIF(GDCM_USE_PVRG)

#ADD_EXECUTABLE(deflate deflate.cxx)
#TARGET_LINK_LIBRARIES(deflate gdcmzlib)

