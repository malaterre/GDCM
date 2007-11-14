# Define the srcs for Media Storage And FileFormat
# MSFF
SET(MSFF_SRCS
  gdcmPrinter.cxx
  gdcmDictPrinter.cxx
  gdcmReader.cxx
  gdcmImageReader.cxx
  gdcmImageWriter.cxx
  gdcmWriter.cxx
  gdcmValidate.cxx
  gdcmDumper.cxx
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  )

ADD_LIBRARY(gdcmMSFF ${MSFF_SRCS})
TARGET_LINK_LIBRARIES(gdcmMSFF gdcmDSED gdcmDICT)

