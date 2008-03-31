# Build the GDCM applications
# Namely:
# gdcmdump
# gdcminfo
# gdcmconv

CHECK_INCLUDE_FILE("fcntl.h"      CMAKE_HAVE_FCNTL_H)
CHECK_INCLUDE_FILE("sched.h"      CMAKE_HAVE_SHED_H)
CHECK_INCLUDE_FILE("sys/mman.h"   CMAKE_HAVE_SYS_MMAN_H)

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
# FIXME:
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
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
  gdcmoverlay
  gdcmimg
  #deflate
  gdcmconv
  gdcminfo
  #csa2img
  )
# Need mmap
IF(CMAKE_HAVE_SYS_MMAN_H)
  SET(GDCM_EXECUTABLE_NAME ${GDCM_EXECUTABLE_NAME}
    gdcmmmap
    gdcmfile
  )
ENDIF(CMAKE_HAVE_SYS_MMAN_H)

FOREACH(exename ${GDCM_EXECUTABLE_NAME})
  ADD_EXECUTABLE(${exename} ${exename}.cxx)
  IF(${exename} STREQUAL "gdcminfo")
    TARGET_LINK_LIBRARIES(${exename} gdcmDSED gdcmDICT)
  ELSE(${exename} STREQUAL "gdcminfo")
    TARGET_LINK_LIBRARIES(${exename} gdcmMSFF)
  ENDIF(${exename} STREQUAL "gdcminfo")
  IF(WIN32 AND NOT CYGWIN)
    TARGET_LINK_LIBRARIES(${exename} gdcmgetopt)
  ENDIF(WIN32 AND NOT CYGWIN)
  INSTALL(TARGETS ${exename}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
	)
ENDFOREACH(exename)

#ADD_EXECUTABLE(deflate deflate.cxx)
#TARGET_LINK_LIBRARIES(deflate gdcmzlib)

# Special daemon
# C program only, no link to gdcm to make it as lightweight as possible
# it uses the readahead func from linux kernel
IF(CMAKE_HAVE_FCNTL_H AND CMAKE_HAVE_SHED_H)
  IF(NOT CYGWIN)
  ADD_EXECUTABLE(gdcmreadahead gdcmreadahead.c)
  INSTALL(TARGETS gdcmreadahead
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
	)
  ENDIF(NOT CYGWIN)
ENDIF(CMAKE_HAVE_FCNTL_H AND CMAKE_HAVE_SHED_H)

# At that point Testing subdirectory should have been done in which case datafiles are set:
