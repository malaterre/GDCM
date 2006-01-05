#-----------------------------------------------------------------------------
# Rebuild gdcm whenever a file starting with gdcm* is modified
INCLUDE_REGULAR_EXPRESSION("^gdcm.*$")

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_SOURCE_DIR}/Source"
  "${GDCM_BINARY_DIR}/Source"
  "${GDCM_SOURCE_DIR}/Utilities"
  )

SET(SRCS
  gdcmTableReader.cxx
  )

ADD_LIBRARY(gdcmTable ${SRCS})
TARGET_LINK_LIBRARIES(gdcmTable gdcm gdcmexpat)

#-----------------------------------------------------------------------------
FILE(GLOB GDCM_XML_TABLES_GLOB
  "${GDCM_SOURCE_DIR}/Tables/*.xml"
  )

SET(GDCM_XML_TABLES)
FOREACH(filename ${GDCM_XML_TABLES_GLOB})
  SET(GDCM_XML_TABLES "${GDCM_XML_TABLES}\n\"${filename}\",")
ENDFOREACH(filename)

# Populate GDCM_DATA_IMAGES:
CONFIGURE_FILE(
  "${GDCM_SOURCE_DIR}/Tables/gdcmTables.h.in"
  "${GDCM_BINARY_DIR}/Tables/gdcmTables.h"
  )

