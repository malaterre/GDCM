# Build the GDCM applications
# Namely:
# gdcmdump
# gdcminfo
# gdcmconv
# gdcmanon


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
  "${GDCM_SOURCE_DIR}/Source/InformationObjectDefinition"
  "${GDCM_SOURCE_DIR}/Source/MessageExchangeDefinition"
# FIXME:
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_SOURCE_DIR}/Utilities"

  "${GDCM_SOURCE_DIR}/Utilities/socketxx"
  "${GDCM_SOURCE_DIR}/Utilities/socketxx/socket++" # local.h
  "${GDCM_BINARY_DIR}/Utilities/socketxx/socket++" # config.h
  )

IF(WIN32)
  IF (BUILD_SHARED_LIBS)
    ADD_DEFINITIONS(-DGETOPT_DLL)
  ENDIF (BUILD_SHARED_LIBS)
ENDIF(WIN32)

SET(GDCM_EXECUTABLE_NAME
  gdcmdump
  gdcmraw
  gdcmscanner
  gdcmanon
  gdcmgendir
  #gdcmoverlay
  gdcmimg
  #deflate
  gdcmconv
  gdcmtar
  gdcminfo
  gdcmscu
  )
# poppler people have the worse API backward compatibility I know of.
# there is absolutely no way to check the version of poppler
# they change the API during a minor change of the version
IF(GDCM_USE_SYSTEM_POPPLER)
  INCLUDE(CheckCXXSourceCompiles)
  SET(CMAKE_REQUIRED_INCLUDES ${POPPLER_INCLUDE_DIRS})
  SET(CMAKE_REQUIRED_LIBRARIES ${POPPLER_LIBRARIES})
  CHECK_CXX_SOURCE_COMPILES(
    "\#include <poppler/GlobalParams.h>\nint main() { globalParams = new GlobalParams(0); return 0;}"
    LIBPOPPLER_GLOBALPARAMS_CSTOR_HAS_PARAM)
  set(libpoppler_flags)
  IF(LIBPOPPLER_GLOBALPARAMS_CSTOR_HAS_PARAM)
    list(APPEND libpoppler_flags -DLIBPOPPLER_GLOBALPARAMS_CSTOR_HAS_PARAM)
  ENDIF(LIBPOPPLER_GLOBALPARAMS_CSTOR_HAS_PARAM)
  CHECK_CXX_SOURCE_COMPILES(
    "\#include <poppler/PDFDoc.h>\nint main() { PDFDoc d((GooString*)NULL,(GooString*)NULL,(GooString*)NULL); d.getPDFVersion(); return 0;}"
    LIBPOPPLER_PDFDOC_HAS_PDFVERSION)
  IF(LIBPOPPLER_PDFDOC_HAS_PDFVERSION)
    list(APPEND libpoppler_flags -DLIBPOPPLER_PDFDOC_HAS_PDFVERSION)
  ENDIF(LIBPOPPLER_PDFDOC_HAS_PDFVERSION)
  IF(libpoppler_flags)
    SET_SOURCE_FILES_PROPERTIES(
      ${CMAKE_CURRENT_SOURCE_DIR}/gdcminfo.cxx
      PROPERTIES COMPILE_FLAGS ${libpoppler_flags})
    SET_SOURCE_FILES_PROPERTIES(
      ${CMAKE_CURRENT_SOURCE_DIR}/gdcmpdf.cxx
      PROPERTIES COMPILE_FLAGS ${libpoppler_flags})
  endif(libpoppler_flags)
  INCLUDE_DIRECTORIES(${POPPLER_INCLUDE_DIRS})
  SET(GDCM_EXECUTABLE_NAME
    ${GDCM_EXECUTABLE_NAME}
    gdcmpdf
  )
ENDIF(GDCM_USE_SYSTEM_POPPLER)

FOREACH(exename ${GDCM_EXECUTABLE_NAME})
  IF(${exename} STREQUAL "gdcminfo")
    ADD_EXECUTABLE(${exename} ${exename}.cxx puff.c)
  ELSE(${exename} STREQUAL "gdcminfo")
    ADD_EXECUTABLE(${exename} ${exename}.cxx)
  ENDIF(${exename} STREQUAL "gdcminfo")
  TARGET_LINK_LIBRARIES(${exename} gdcmMSFF)
  IF(${exename} STREQUAL "gdcmpdf")
    TARGET_LINK_LIBRARIES(${exename} ${POPPLER_LIBRARIES})
  ELSEIF(${exename} STREQUAL "gdcmscu")
    TARGET_LINK_LIBRARIES(${exename} gdcmMEXD socketxx)
  ELSEIF(${exename} STREQUAL "gdcminfo")
    IF(GDCM_USE_SYSTEM_PODOFO)
      TARGET_LINK_LIBRARIES(${exename} ${PODOFO_LIBRARIES})
    ENDIF(GDCM_USE_SYSTEM_PODOFO)
    IF(GDCM_USE_SYSTEM_POPPLER)
      TARGET_LINK_LIBRARIES(${exename} ${POPPLER_LIBRARIES})
    ENDIF(GDCM_USE_SYSTEM_POPPLER)
  ENDIF(${exename} STREQUAL "gdcmpdf")
  IF(GDCM_EXECUTABLE_PROPERTIES)
    SET_TARGET_PROPERTIES(${exename} PROPERTIES ${GDCM_EXECUTABLE_PROPERTIES})
  ENDIF(GDCM_EXECUTABLE_PROPERTIES)
  IF(WIN32 AND NOT CYGWIN)
    TARGET_LINK_LIBRARIES(${exename} gdcmgetopt)
  ENDIF(WIN32 AND NOT CYGWIN)
  IF(NOT GDCM_INSTALL_NO_RUNTIME)
    INSTALL(TARGETS ${exename}
      EXPORT ${GDCM_TARGETS_NAME}
      RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Applications
      LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Libraries
      ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
    )
  ENDIF(NOT GDCM_INSTALL_NO_RUNTIME)
ENDFOREACH(exename)

IF(BUILD_TESTING)
  # http://www.na-mic.org/Wiki/index.php/CTSC:ARRA:Mockup
  ADD_TEST(gdcmscu-echo-MI2B2 ${EXECUTABLE_OUTPUT_PATH}/gdcmscu --echo --call MI2B2 mi2b2.slicer.org 11112)
  ADD_TEST(gdcmscu-find-MI2B2 ${EXECUTABLE_OUTPUT_PATH}/gdcmscu --find --call MI2B2 mi2b2.slicer.org 11112 -k 8,52=PATIENT -k 10,10=X*)
ENDIF(BUILD_TESTING)
