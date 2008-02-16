# Build the GDCM applications
# Namely:
# gdcmdump
# gdcminfo
# gdcmconv

SET(GDCMDUMP_APPS_SRCS
  gdcmdump.cxx
  )

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
  gdcmoverlay
  gdcmimg
  #deflate
  gdcmconv
  )

FOREACH(exename ${GDCM_EXECUTABLE_NAME})
  ADD_EXECUTABLE(${exename} ${exename}.cxx)
  TARGET_LINK_LIBRARIES(${exename} gdcmMSFF)
  IF(WIN32 AND NOT CYGWIN)
    TARGET_LINK_LIBRARIES(${exename} gdcmgetopt)
  ENDIF(WIN32 AND NOT CYGWIN)
ENDFOREACH(exename)

#ADD_EXECUTABLE(deflate deflate.cxx)
#TARGET_LINK_LIBRARIES(deflate gdcmzlib)


