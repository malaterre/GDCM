# Build the GDCM applications
# Namely:
# gdcmdump
# gdcminfo

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

#ADD_EXECUTABLE(deflate deflate.cxx)
#TARGET_LINK_LIBRARIES(deflate gdcmzlib)

# gdcmrewrite
ADD_EXECUTABLE(gdcmrewrite gdcmrewrite.cxx)
TARGET_LINK_LIBRARIES(gdcmrewrite gdcmMSFF)
IF(WIN32 AND NOT CYGWIN)
  TARGET_LINK_LIBRARIES(gdcmrewrite gdcmgetopt)
ENDIF(WIN32 AND NOT CYGWIN)

