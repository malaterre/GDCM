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
  gdcmdiff
  gdcmraw
  gdcmscanner
  gdcmanon
  gdcmgendir
  #gdcmoverlay
  gdcmimg
  #deflate
  gdcmconv
  gdcmstream
  gdcmtar
  gdcminfo
  gdcmscu
  gdcmxml
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

IF(GDCM_USE_SYSTEM_LIBXML2)
  INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIR})
ENDIF(GDCM_USE_SYSTEM_LIBXML2)


IF(GDCM_USE_SYSTEM_OPENJPEG)
  INCLUDE_DIRECTORIES(${OPENJPEG_INCLUDE_DIRS} )
ELSE(GDCM_USE_SYSTEM_OPENJPEG)
  INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Utilities/gdcmopenjpeg"
    )
ENDIF(GDCM_USE_SYSTEM_OPENJPEG)

IF(NOT BUILD_SHARED_LIBS)
  SET_SOURCE_FILES_PROPERTIES(gdcmstream.cxx
                              PROPERTIES
                              COMPILE_FLAGS -DOPJ_STATIC
                              )
ENDIF(NOT BUILD_SHARED_LIBS)

FOREACH(exename ${GDCM_EXECUTABLE_NAME})
  IF(${exename} STREQUAL "gdcminfo")
    ADD_EXECUTABLE(${exename} ${exename}.cxx puff.c)
  ELSE(${exename} STREQUAL "gdcminfo")
    ADD_EXECUTABLE(${exename} ${exename}.cxx)
  ENDIF(${exename} STREQUAL "gdcminfo")
  TARGET_LINK_LIBRARIES(${exename} gdcmMSFF)
  IF(${exename} STREQUAL "gdcmpdf")
    TARGET_LINK_LIBRARIES(${exename} ${POPPLER_LIBRARIES})
  ELSEIF(${exename} STREQUAL "gdcmxml")
    TARGET_LINK_LIBRARIES(${exename} ${LIBXML2_LIBRARIES})
  ELSEIF(${exename} STREQUAL "gdcmscu")
    TARGET_LINK_LIBRARIES(${exename} gdcmMEXD socketxx)
  ELSEIF(${exename} STREQUAL "gdcmstream")
    TARGET_LINK_LIBRARIES(${exename} ${GDCM_OPENJPEG_LIBRARIES})
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
    )
  ENDIF(NOT GDCM_INSTALL_NO_RUNTIME)
ENDFOREACH(exename)

#IF(BUILD_TESTING)
#  IF(GDCM_DATA_ROOT)
#    FILE(MAKE_DIRECTORY ${GDCM_TEMP_DIRECTORY}/gdcmanon-gdcmdata)
#    ADD_TEST(gdcmanon-gdcmdata ${EXECUTABLE_OUTPUT_PATH}/gdcmanon
#      --continue  # skip LIBIDO-16-ACR_NEMA-Volume.dcm
#      --certificate ${GDCM_SOURCE_DIR}/Testing/Source/Data/certificate.pem
#      ${GDCM_DATA_ROOT}
#      ${GDCM_TEMP_DIRECTORY}/gdcmanon-gdcmdata
#      )
#  ENDIF(GDCM_DATA_ROOT)
#ENDIF(BUILD_TESTING)

IF(BUILD_TESTING)
  # http://www.na-mic.org/Wiki/index.php/CTSC:ARRA:Mockup
  # http://www.dicomserver.co.uk/
  # the NAMIC server is offline, Steve Pieper has volunteered his servers, but they are intermittent
  # IP Address: common.bwh.harvard.edu (155.52.248.49)
  # Port: 11112
  # AE Title: CTK_AE
  # and
  # IP Address: joe.bwh.harvard.edu (155.52.248.50)
  # Port: 5678
  # AE Title: CONQUESTSRV1
  #since these servers have no guaranteed uptime, these tests should be changed to some other, known-to-be-up server
  #ADD_TEST(gdcmscu-echo-CONQUEST ${EXECUTABLE_OUTPUT_PATH}/gdcmscu --echo --call CONQUESTSRV1 joe.bwh.harvard.edu 5678)
  ADD_TEST(gdcmscu-echo-dicomserver ${EXECUTABLE_OUTPUT_PATH}/gdcmscu --echo www.dicomserver.co.uk 11112)
  IF(GDCM_DATA_ROOT)
    # CR-MONO1-10-chest.dcm gets rejected by www.dicomserver.co.uk:
    # Tag 0x0,0x902 reported as Incorrect VM (1) - Minimum value is 2 : 'Array of N Elements' (error 42752)
    # CR-MONO1-10-chest.dcm gets rejected by mi2b2.slicer.org
    # Tag 0x0,0x902 reported as Acceptance of objects without Patient ID is disabled (error 43264)
    #ADD_TEST(gdcmscu-store-CONQUEST ${EXECUTABLE_OUTPUT_PATH}/gdcmscu --store --call CONQUESTSRV1 joe.bwh.harvard.edu 11112 ${GDCM_DATA_ROOT}/SIEMENS_MAGNETOM-12-MONO2-FileSeq1.dcm)
    ADD_TEST(gdcmscu-store-dicomserver ${EXECUTABLE_OUTPUT_PATH}/gdcmscu --store www.dicomserver.co.uk 11112 ${GDCM_DATA_ROOT}/SIEMENS_MAGNETOM-12-MONO2-FileSeq1.dcm)
  ENDIF(GDCM_DATA_ROOT)
  #ADD_TEST(gdcmscu-find-CONQUEST ${EXECUTABLE_OUTPUT_PATH}/gdcmscu --find --patient --call CONQUESTSRV1 joe.bwh.harvard.edu 11112 --patientroot -k 10,10=X*)
  ADD_TEST(gdcmscu-find-dicomserver ${EXECUTABLE_OUTPUT_PATH}/gdcmscu --find --patient www.dicomserver.co.uk 11112 --patientroot -k 10,20=*)

  IF(GDCM_DICOM_SERVER_AETITLE)
  IF(GDCM_DATA_ROOT)
    # Let's C-STORE a limited subset of gdcmData for now:
    SET(CSTORE_DATA_FILES
      CR-MONO1-10-chest.dcm # Implicit VR Little Endian: Default Transfer Syntax for DICOM
      012345.002.050.dcm    # JPEG Lossless, Non-Hierarchical, First-Order Prediction
      )
    FOREACH(cstorefile ${CSTORE_DATA_FILES})
    ADD_TEST(gdcmscu-echo-${cstorefile}  ${EXECUTABLE_OUTPUT_PATH}/gdcmscu --echo  --aetitle ${GDCM_DICOM_CLIENT_AETITLE} --call ${GDCM_DICOM_SERVER_AETITLE} ${GDCM_DICOM_SERVER_PEER} ${GDCM_DICOM_SERVER_PORT})
    ADD_TEST(gdcmscu-store-${cstorefile} ${EXECUTABLE_OUTPUT_PATH}/gdcmscu --store --aetitle ${GDCM_DICOM_CLIENT_AETITLE} --call ${GDCM_DICOM_SERVER_AETITLE} ${GDCM_DICOM_SERVER_PEER} ${GDCM_DICOM_SERVER_PORT} ${GDCM_DATA_ROOT}/${cstorefile})
    ADD_TEST(gdcmscu-find-${cstorefile}  ${EXECUTABLE_OUTPUT_PATH}/gdcmscu --find --patient --aetitle ${GDCM_DICOM_CLIENT_AETITLE} --call ${GDCM_DICOM_SERVER_AETITLE} ${GDCM_DICOM_SERVER_PEER} ${GDCM_DICOM_SERVER_PORT} --patientroot -k 10,10=A* -k 10,20)
    ADD_TEST(gdcmscu-move-${cstorefile}  ${EXECUTABLE_OUTPUT_PATH}/gdcmscu --move  --patient --aetitle ${GDCM_DICOM_CLIENT_AETITLE} --call ${GDCM_DICOM_SERVER_AETITLE} ${GDCM_DICOM_SERVER_PEER} ${GDCM_DICOM_SERVER_PORT} -o ${CMAKE_CURRENT_BINARY_DIR} --patientroot -k 10,10=Anonymized --port-scp ${GDCM_DICOM_CLIENT_PORT})
    ADD_TEST(gdcmscu-move-${cstorefile}  ${EXECUTABLE_OUTPUT_PATH}/gdcmscu --move  --patient --aetitle ${GDCM_DICOM_CLIENT_AETITLE} --call ${GDCM_DICOM_SERVER_AETITLE} ${GDCM_DICOM_SERVER_PEER} ${GDCM_DICOM_SERVER_PORT} -o ${CMAKE_CURRENT_BINARY_DIR} --patientroot -k 10,10=X* --port-scp ${GDCM_DICOM_CLIENT_PORT})
    ENDFOREACH(cstorefile)
  ENDIF(GDCM_DATA_ROOT)
  ENDIF(GDCM_DICOM_SERVER_AETITLE)

ENDIF(BUILD_TESTING)
