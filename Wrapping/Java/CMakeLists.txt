# TODO:
# SWIG is really a pain in the neck to use, a better alternative is Py++ which is using
# gccxml for the C++ parser and allow a full ANSI C++ support
FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/InformationObjectDefinition"
  "${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
)

# $ export JAVA_HOME=/usr/lib/j2sdk1.6-sun/ 
# $ export JAVA_HOME=/usr/lib/jvm/java-1.5.0-sun/
FIND_PACKAGE(Java REQUIRED) # javac, jar
FIND_PACKAGE(JNI REQUIRED)
INCLUDE_DIRECTORIES(
  #${JNI_INCLUDE_PATH}
  ${JAVA_INCLUDE_PATH}
  ${JAVA_INCLUDE_PATH2}
  ${JAVA_AWT_INCLUDE_PATH}
  )
SET_SOURCE_FILES_PROPERTIES(gdcm.i PROPERTIES CPLUSPLUS ON)
#INCLUDE(${GDCM_SOURCE_DIR}/CMake/UseSWIGExtra.cmake)

# Some old swig 1.3 did not support this option:
#SET(CMAKE_SWIG_OUTDIR "${CMAKE_CURRENT_BINARY_DIR}/swig-java")

SET(CMAKE_SWIG_FLAGS "-package gdcm")
SEPARATE_ARGUMENTS(CMAKE_SWIG_FLAGS)
SWIG_ADD_MODULE(gdcm java gdcm.i)
SWIG_LINK_LIBRARIES(gdcm gdcmMSFF
  #${JNI_LIBRARIES}
  ${JAVA_AWT_LIB_PATH}
  ${JAVA_JVM_LIB_PATH}
) 
# Stupid cmake-swig module is doing that for us, when not needed
IF(UNIX)
  SET_TARGET_PROPERTIES(${SWIG_MODULE_gdcm_REAL_NAME} PROPERTIES PREFIX "lib")
ENDIF(UNIX)

# swig-java dummy run:
# the following execute_process is a dummy run and generate all *.java files in a directory
# we can then glob all *.java to build rules in case the java wrapper becomes broken
#EXECUTE_PROCESS(COMMAND ${SWIG_EXECUTABLE} 
#  -java
#  -I${GDCM_BINARY_DIR}/Source/Common
#  -I${GDCM_SOURCE_DIR}/Source/Common
#  -I${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition
#  -I${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat
#  -I${GDCM_SOURCE_DIR}/Source/DataDictionary
#  -c++ 
#  -o dummy.o
#  ${CMAKE_CURRENT_SOURCE_DIR}/gdcm.i
#  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#  RESULT_VARIABLE res
#)
#MESSAGE("res:${res}")
#FILE(GLOB javafiles "${CMAKE_CURRENT_BINARY_DIR}/*.java")
#MESSAGE("javafile:${javafiles}")

# This is kindda hackish:
# 1. run the custom command only when the gdcmJAVA_wrap.cxx has been generated (which means all *.java should be there)
ADD_CUSTOM_COMMAND(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gdcm.class
  COMMAND ${JAVA_COMPILE} ARGS "*.java" #${javafiles}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS "${swig_generated_file_fullname}"
  COMMENT "javac *.java"
)

# 2. now that the *.class have been generated construct the jar file. We can only rely on the gdcm.java / gdcm.class
# to build dependencie, I am pretty sure it will break parallel builds... oh well
ADD_CUSTOM_COMMAND(
  OUTPUT ${LIBRARY_OUTPUT_PATH}/gdcm.jar
  COMMAND ${JAVA_ARCHIVE} ARGS cvf ${LIBRARY_OUTPUT_PATH}/gdcm.jar *.class
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/gdcm.class
  COMMENT "jar cvf -> gdcm.jar"
)

# 3. ok now add the target
ADD_CUSTOM_TARGET(GDCMJavaJar ALL
  DEPENDS ${LIBRARY_OUTPUT_PATH}/gdcm.jar
  COMMENT "building gdcm.jar"
)

# 4. gdcm.jar has been generated, let's put it right next to libgdcm.so:
#ADD_CUSTOM_COMMAND(
#  TARGET   GDCMJavaJar
#  POST_BUILD
#  COMMAND   ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/gdcm.jar ${LIBRARY_OUTPUT_PATH}
#  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/gdcm.jar
#  COMMENT   "Copy gdcm.jar into ${LIBRARY_OUTPUT_PATH}"
#)

# Module are always place in the library destination
# but for poor win32 user I decided to place them
# right next to the other dlls
IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS ${SWIG_MODULE_gdcm_REAL_NAME}
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
  ${CPACK_NAMELINK_TYPE}
  )
  # because gdcm.jar is constructed with custom commands, it need the INSTALL(FILES signature:
  INSTALL(FILES ${LIBRARY_OUTPUT_PATH}/gdcm.jar
    DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime
  )
ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)

