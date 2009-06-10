FIND_PACKAGE(Java REQUIRED) # javac, jar
FIND_PACKAGE(JNI REQUIRED)
INCLUDE_DIRECTORIES(
  #${JNI_INCLUDE_PATH}
  ${JAVA_INCLUDE_PATH}
  ${JAVA_INCLUDE_PATH2}
  ${JAVA_AWT_INCLUDE_PATH}
  )

ADD_CUSTOM_COMMAND(
  OUTPUT ${EXECUTABLE_OUTPUT_PATH}/gdcm.jar
# 1. run the custom command only when the gdcmJAVA_wrap.cxx has been generated (which means all *.java should be there)
  COMMAND ${JAVA_COMPILE} ARGS "gdcm/*.java" #${javafiles}
# 2. now that the *.class have been generated construct the jar file. We can only rely on the gdcm.java / gdcm.class
# to build dependencie, I am pretty sure it will break parallel builds... oh well
  COMMAND ${JAVA_ARCHIVE} ARGS cvf ${LIBRARY_OUTPUT_PATH}/gdcm.jar gdcm/*.class
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/java
  DEPENDS "${swig_generated_file_fullname}"
  COMMENT "javac *.java; jar cvf -> gdcm.jar"
)

# 3. ok now add the target
ADD_CUSTOM_TARGET(GDCMJavaJar ALL
  DEPENDS ${LIBRARY_OUTPUT_PATH}/gdcm.jar
  COMMENT "building gdcm.jar"
)

