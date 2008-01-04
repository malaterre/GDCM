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

ADD_EXECUTABLE(gdcmdump ${GDCMDUMP_APPS_SRCS})
TARGET_LINK_LIBRARIES(gdcmdump gdcmMSFF)
IF(WIN32 AND NOT CYGWIN)
  TARGET_LINK_LIBRARIES(gdcmdump gdcmgetopt)
ENDIF(WIN32 AND NOT CYGWIN)

# gdcmraw
ADD_EXECUTABLE(gdcmraw gdcmraw.cxx)
TARGET_LINK_LIBRARIES(gdcmraw gdcmMSFF) # gdcmgetopt)

# gdcmoverlay
ADD_EXECUTABLE(gdcmoverlay gdcmoverlay.cxx)
TARGET_LINK_LIBRARIES(gdcmoverlay gdcmMSFF) # gdcmgetopt)

#ADD_EXECUTABLE(deflate deflate.cxx)
#TARGET_LINK_LIBRARIES(deflate gdcmzlib)

# gdcmconv
ADD_EXECUTABLE(gdcmconv gdcmconv.cxx)
TARGET_LINK_LIBRARIES(gdcmconv gdcmMSFF)
IF(WIN32 AND NOT CYGWIN)
  TARGET_LINK_LIBRARIES(gdcmconv gdcmgetopt)
ENDIF(WIN32 AND NOT CYGWIN)

