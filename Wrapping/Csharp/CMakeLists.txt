# TODO:
# SWIG is really a pain in the neck to use, a better alternative is Py++ which is using
# gccxml for the C++ parser and allow a full ANSI C++ support
FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
)
# Provide some C99 compatilities for all win system...hopefully there won't be no collision
IF(WIN32)
  INCLUDE_DIRECTORIES(
    "${GDCM_SOURCE_DIR}/Utilities/C99"
  )
ENDIF(WIN32)

# $ export JAVA_HOME=/usr/lib/j2sdk1.6-sun/ 
# $ export JAVA_HOME=/usr/lib/jvm/java-1.5.0-sun/
#FIND_PACKAGE(JNI REQUIRED)
#INCLUDE_DIRECTORIES(
#  #${JNI_INCLUDE_PATH}
#  ${JAVA_INCLUDE_PATH}
#  ${JAVA_INCLUDE_PATH2}
#  ${JAVA_AWT_INCLUDE_PATH}
#  )
SET_SOURCE_FILES_PROPERTIES(gdcm.i PROPERTIES CPLUSPLUS ON)

# Some old swig 1.3 did not support this option:
#SET(CMAKE_SWIG_OUTDIR "${CMAKE_CURRENT_BINARY_DIR}")

#SET(CMAKE_SWIG_FLAGS "-package gdcm")
#SEPARATE_ARGUMENTS(CMAKE_SWIG_FLAGS)
SWIG_ADD_MODULE(gdcm csharp gdcm.i)
SWIG_LINK_LIBRARIES(gdcm gdcmMSFF
  #${JNI_LIBRARIES}
#  ${JAVA_AWT_LIB_PATH}
#  ${JAVA_JVM_LIB_PATH}
) 
# Stupid cmake-swig module is doing that for us, when not needed
IF(UNIX)
  SET_TARGET_PROPERTIES(${SWIG_MODULE_gdcm_REAL_NAME} PROPERTIES PREFIX "lib")
ENDIF(UNIX)


#Module are always place in the library destination
#but for poor win32 user I decided to place them
# right next to the other dlls
IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS ${SWIG_MODULE_gdcm_REAL_NAME}
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
  )

ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)
