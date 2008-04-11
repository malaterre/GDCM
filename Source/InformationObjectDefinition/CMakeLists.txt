# Define the srcs for the Information Object Definition
# IOD
SET(IOD_SRCS
  gdcmModule.cxx
  gdcmTableReader.cxx
  gdcmTable.cxx
  gdcmSeries.cxx
  gdcmDefinedTerms.cxx
  gdcmEnumeratedValues.cxx
  gdcmStudy.cxx
  gdcmPatient.cxx
  gdcmType.cxx
  gdcmXMLDictReader.cxx
  gdcmXMLPrivateDictReader.cxx
  )

# expat stuff
IF(NOT BUILD_SHARED_LIBS)
  SET_SOURCE_FILES_PROPERTIES(gdcmTableReader.cxx
                              PROPERTIES 
                              COMPILE_FLAGS -DXML_STATIC
                              )
ENDIF(NOT BUILD_SHARED_LIBS)

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Utilities"
  )

ADD_LIBRARY(gdcmIOD ${IOD_SRCS})
#TARGET_LINK_LIBRARIES(gdcmIOD gdcmCommon gdcmexpat)
TARGET_LINK_LIBRARIES(gdcmIOD gdcmDSED gdcmCommon) # gdcmexpat)
IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS gdcmIOD
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
  )
ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)

IF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
  FILE(GLOB header_files "*.h" "*.txx")
  INSTALL(FILES ${header_files}
    DESTINATION ${GDCM_INSTALL_INCLUDE_DIR} COMPONENT Development
  )
ENDIF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
#-----------------------------------------------------------------------------
FILE(GLOB GDCM_XML_TABLES_GLOB
  "${CMAKE_CURRENT_SOURCE_DIR}/*.xml"
  )

SET(GDCM_XML_TABLES)
FOREACH(filename ${GDCM_XML_TABLES_GLOB})
  SET(GDCM_XML_TABLES "${GDCM_XML_TABLES}\n\"${filename}\",")
ENDFOREACH(filename)

# Populate GDCM_DATA_IMAGES:
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/gdcmTables.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/gdcmTables.h"
  )

