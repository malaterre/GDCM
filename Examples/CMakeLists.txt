# Build the GDCM examples

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

ADD_EXECUTABLE(csa2img csa2img.cxx)
TARGET_LINK_LIBRARIES(csa2img gdcmMSFF)

ADD_EXECUTABLE(rle2img rle2img.cxx)
TARGET_LINK_LIBRARIES(rle2img gdcmMSFF)

ADD_EXECUTABLE(uid_unique uid_unique.cxx)
TARGET_LINK_LIBRARIES(uid_unique gdcmMSFF)

