# TODO:
# SWIG is really a pain in the neck to use, a better alternative is Py++ which is using
# gccxml for the C++ parser and allow a full ANSI C++ support
# http://mvidner.blogspot.com/2007/07/first-time-with-mono.html
# http://www.nabble.com/CMake-file-for-Qyoto-Kimono-td7547960.html
# https://svn.osgeo.org/mapserver/trunk/mapserver/mapscript/csharp/Makefile.in
FIND_PACKAGE(SWIG REQUIRED)
MARK_AS_ADVANCED(SWIG_DIR SWIG_EXECUTABLE SWIG_VERSION)
INCLUDE(${SWIG_USE_FILE})

INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/InformationObjectDefinition"
  "${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  #${CMAKE_CURRENT_SOURCE_DIR}
)

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

SET(CMAKE_SWIG_FLAGS "-namespace gdcm")
SEPARATE_ARGUMENTS(CMAKE_SWIG_FLAGS)
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
  ${CPACK_NAMELINK_TYPE}
  )

ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)

IF(UNIX)
  FIND_PACKAGE(MONO REQUIRED)

  ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gdcm_csharp.dll
    # $(CSC) /t:library /out:mapscript_csharp.dll *.cs config/AssemblyInfo.cs
    COMMAND ${GMCS_EXECUTABLE} ARGS "/t:library" "/out:gdcm_csharp.dll" "*.cs" ${CMAKE_CURRENT_SOURCE_DIR}/AssemblyInfo.cs
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS "${swig_generated_file_fullname}"
    COMMENT "mcs *.cs"
  )

# building HelloWorld:
  ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/HelloWorld.exe
#$(CSC) /r:mapscript_csharp.dll /out:shpdump.exe examples/shpdump.cs
    COMMAND ${GMCS_EXECUTABLE} ARGS "/r:gdcm_csharp.dll" "/out:HelloWorld.exe" ${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld.cs
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/gdcm_csharp.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld.cs
    COMMENT "Create HelloWorld.exe"
  )

ADD_CUSTOM_TARGET(GDCMCSharp ALL
  DEPENDS 
    ${CMAKE_CURRENT_BINARY_DIR}/gdcm_csharp.dll
    ${CMAKE_CURRENT_BINARY_DIR}/HelloWorld.exe
  COMMENT "building gdcm_csharp.dll"
)

IF(BUILD_TESTING)
  ADD_TEST(HelloWorldCSharp ${MONO_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/HelloWorld.exe ${GDCM_DATA_ROOT}/test.acr)
ENDIF(BUILD_TESTING)

ENDIF(UNIX)

