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
  )

ADD_EXECUTABLE(gdcmdump ${GDCMDUMP_APPS_SRCS})
TARGET_LINK_LIBRARIES(gdcmdump gdcmDSED)

ADD_EXECUTABLE(gdcmraw gdcmraw.cxx)
TARGET_LINK_LIBRARIES(gdcmraw gdcmDSED)
