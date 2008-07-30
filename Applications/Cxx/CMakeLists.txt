# Build the GDCM applications
# Namely:
# gdcmdump
# gdcminfo
# gdcmconv


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
# FIXME:
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  "${GDCM_BINARY_DIR}/Utilities/zlib"
  "${GDCM_SOURCE_DIR}/Utilities"
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
  #gdcmoverlay
  gdcmimg
  #deflate
  gdcmconv
  gdcminfo
  )

FOREACH(exename ${GDCM_EXECUTABLE_NAME})
  IF(${exename} STREQUAL "gdcminfo")
  ADD_EXECUTABLE(${exename} ${exename}.cxx puff.c)
  ELSE(${exename} STREQUAL "gdcminfo")
  ADD_EXECUTABLE(${exename} ${exename}.cxx)
  ENDIF(${exename} STREQUAL "gdcminfo")
    TARGET_LINK_LIBRARIES(${exename} gdcmMSFF)
  SET_TARGET_PROPERTIES(${exename} PROPERTIES ${GDCM_EXECUTABLE_PROPERTIES})
  IF(WIN32 AND NOT CYGWIN)
    TARGET_LINK_LIBRARIES(${exename} gdcmgetopt)
  ENDIF(WIN32 AND NOT CYGWIN)
  INSTALL(TARGETS ${exename}
	RUNTIME DESTINATION bin COMPONENT Runtime
	LIBRARY DESTINATION lib COMPONENT Runtime
	ARCHIVE DESTINATION lib/static COMPONENT Development
	)
ENDFOREACH(exename)

#ADD_EXECUTABLE(deflate deflate.cxx)
#TARGET_LINK_LIBRARIES(deflate gdcmzlib)

