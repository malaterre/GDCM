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

SET(EXAMPLES_SRCS
  CheckBigEndianBug
  CompressImage
  FixBrokenJ2K
  GenFakeImage
  HelloVizWorld
  HelloWorld
  MergeTwoFiles
  MrProtocol
  PatchFile
  ReadExplicitLengthSQIVR
  SortImage
  VolumeSorter
  csa2img
  rle2img
  uid_unique
)

FOREACH(example ${EXAMPLES_SRCS})
  ADD_EXECUTABLE(${example} ${example}.cxx)
  TARGET_LINK_LIBRARIES(${example} gdcmMSFF)
ENDFOREACH(example)

