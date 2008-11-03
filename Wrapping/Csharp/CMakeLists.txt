# TODO:
# http://www.disconnectd.com/?p=21
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



##IF(UNIX)
##  FIND_PACKAGE(MONO REQUIRED)
#FIND_PACKAGE(CSharp REQUIRED)
#INCLUDE(${CSharp_USE_FILE})
#
#  CONFIGURE_FILE(
#    ${CMAKE_CURRENT_SOURCE_DIR}/AssemblyInfo.cs.in
#    ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs
#    @ONLY)
##  ADD_CUSTOM_COMMAND(
##    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gdcm_csharp.dll
##    # $(CSC) /t:library /out:mapscript_csharp.dll *.cs config/AssemblyInfo.cs
##    COMMAND ${MCS_EXECUTABLE} ARGS "/t:library" "/out:gdcm_csharp.dll" "*.cs" ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs
##    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
##    DEPENDS "${swig_generated_file_fullname}"
##      ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs
##    COMMENT "mcs *.cs"
##  )
#
## building HelloWorld:
##$(CSC) /r:mapscript_csharp.dll /out:shpdump.exe examples/shpdump.cs
## Cannot use glob since files are not generated yet...
##FILE(GLOB bla "${CMAKE_CURRENT_BINARY_DIR}/*.cs")
#CSHARP_ADD_LIBRARY(gdcm_csharp ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs \"*.cs\")
#ADD_CUSTOM_TARGET(CSharp_gdcm_sharp ALL
#    DEPENDS ${SWIG_MODULE_gdcm_REAL_NAME}
#  )
#
## For some reason csc v1.1.4322 does not like full path, so I need to locally copy it to the binary dir
#IF(WIN32)
#  CONFIGURE_FILE(
#    ${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld.cs
#    ${CMAKE_CURRENT_BINARY_DIR}/HelloWorld.cs
#  )
#ENDIF(WIN32)
##CSHARP_ADD_EXECUTABLE(HelloWorld HelloWorld.cs)
##CSHARP_LINK_LIBRARIES(HelloWorld gdcm_csharp)
##ADD_CUSTOM_TARGET(CSHARP_EXECUTABLE_HelloWorld ALL
##    DEPENDS 
##      ${CMAKE_CURRENT_BINARY_DIR}/gdcm_csharp.dll
##    # CSharp_gdcm_csharp
##  )
#
#
#
##  $ export MONO_LOG_LEVEL="debug"; export MONO_LOG_MASK="dll"
## $ export LD_LIBRARY_PATH=/home/mmalaterre/Projects/gdcm/debug-gcc43/Wrapping/Csharp/:/home/mmalaterre/Projects/gdcm/debug-gcc43/bin   
##ADD_CUSTOM_TARGET(GDCMCSharp ALL
##  DEPENDS 
##    ${CMAKE_CURRENT_BINARY_DIR}/gdcm_csharp.dll
##    ${CMAKE_CURRENT_BINARY_DIR}/HelloWorld.exe
##  COMMENT "building gdcm_csharp.dll"
##)
#
#IF(BUILD_TESTING)
#  ADD_TEST(HelloWorldCSharp ${CMAKE_CSHARP_INTERPRETER} ${CMAKE_CURRENT_BINARY_DIR}/HelloWorld.exe ${GDCM_DATA_ROOT}/test.acr)
#ENDIF(BUILD_TESTING)
#
##ENDIF(UNIX)


FIND_PACKAGE(CSharp REQUIRED)
INCLUDE(${CSharp_USE_FILE})
  CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/AssemblyInfo.cs.in
    ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs
    @ONLY)
  ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gdcm_csharp.dll
    # $(CSC) /t:library /out:mapscript_csharp.dll *.cs config/AssemblyInfo.cs
    COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/t:library" "/out:gdcm_csharp.dll" "*.cs" 
#${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS "${swig_generated_file_fullname}"
      ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs
    COMMENT "csc *.cs"
  )

# building HelloWorld:
  ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/HelloWorld.exe
#$(CSC) /r:mapscript_csharp.dll /out:shpdump.exe examples/shpdump.cs
    COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/r:gdcm_csharp.dll" "/out:HelloWorld.exe" ${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld.cs
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/gdcm_csharp.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld.cs
    COMMENT "Create HelloWorld.exe"
  )

IF(WIN32)
  CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld.cs
    ${CMAKE_CURRENT_BINARY_DIR}/HelloWorld.cs
  )
ENDIF(WIN32)

#  $ export MONO_LOG_LEVEL="debug"; export MONO_LOG_MASK="dll"
# $ export LD_LIBRARY_PATH=/home/mmalaterre/Projects/gdcm/debug-gcc43/Wrapping/Csharp/:/home/mmalaterre/Projects/gdcm/debug-gcc43/bin   
ADD_CUSTOM_TARGET(GDCMCSharp ALL
  DEPENDS 
    ${CMAKE_CURRENT_BINARY_DIR}/gdcm_csharp.dll
    ${CMAKE_CURRENT_BINARY_DIR}/HelloWorld.exe
  COMMENT "building gdcm_csharp.dll"
)

IF(BUILD_TESTING)
  ADD_TEST(HelloWorldCSharp ${CMAKE_CSHARP_INTERPRETER} ${CMAKE_CURRENT_BINARY_DIR}/HelloWorld.exe ${GDCM_DATA_ROOT}/012345.002.050.dcm)
ENDIF(BUILD_TESTING)

IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS ${SWIG_MODULE_gdcm_REAL_NAME}
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
  ${CPACK_NAMELINK_TYPE}
  )
  # because gdcm_csharp.dll is constructed with custom commands, it need the INSTALL(FILES signature:
  INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/gdcm_csharp.dll
    DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime
  )
ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)

