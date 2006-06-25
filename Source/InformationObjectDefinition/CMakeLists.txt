#-----------------------------------------------------------------------------
# Rebuild gdcm whenever a file starting with gdcm* is modified
INCLUDE_REGULAR_EXPRESSION("^gdcm.*$")

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Parser"
  "${GDCM_BINARY_DIR}/Source/Parser"
  "${GDCM_SOURCE_DIR}/Utilities"
  )

SET(SRCS
  gdcmTableReader.cxx
  )

ADD_LIBRARY(gdcmModuleAttributes ${SRCS})
TARGET_LINK_LIBRARIES(gdcmModuleAttributes gdcmParser gdcmexpat)

#-----------------------------------------------------------------------------
FILE(GLOB GDCM_XML_TABLES_GLOB
  "${GDCM_SOURCE_DIR}/Source/ModuleAttributes/*.xml"
  )

SET(GDCM_XML_TABLES)
FOREACH(filename ${GDCM_XML_TABLES_GLOB})
  SET(GDCM_XML_TABLES "${GDCM_XML_TABLES}\n\"${filename}\",")
ENDFOREACH(filename)

# Populate GDCM_DATA_IMAGES:
CONFIGURE_FILE(
  "${GDCM_SOURCE_DIR}/Source/ModuleAttributes/gdcmTables.h.in"
  "${GDCM_BINARY_DIR}/Source/ModuleAttributes/gdcmTables.h"
  )

