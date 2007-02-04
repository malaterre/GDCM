# Build the GDCM applications
# Namely:
# gdcmdump
# gdcminfo

SET(GDCMDUMP_APPS_SRCS
  gdcmdump.cxx
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat"
  )

ADD_EXECUTABLE(gdcmdump ${GDCMDUMP_APPS_SRCS})
TARGET_LINK_LIBRARIES(gdcmdump gdcmMSFF)

# gdcmraw
ADD_EXECUTABLE(gdcmraw gdcmraw.cxx)
TARGET_LINK_LIBRARIES(gdcmraw gdcmMSFF)

# gdcmrewrite
ADD_EXECUTABLE(gdcmrewrite gdcmrewrite.cxx)
TARGET_LINK_LIBRARIES(gdcmrewrite gdcmMSFF)

