# Define the tests for gdcm-java
SET(GDCM_JAVA_TEST_SRCS
  TestReader
  )

# Do not change anything after here:
FIND_PACKAGE(Java REQUIRED) # javac, jar
FIND_PACKAGE(JNI REQUIRED)
INCLUDE_DIRECTORIES(
  ${JNI_INCLUDE_PATH}
  )

set(classfilesdep)

FOREACH(example ${GDCM_JAVA_TEST_SRCS})
  ADD_CUSTOM_COMMAND(
    OUTPUT ${EXECUTABLE_OUTPUT_PATH}/${example}.class
    COMMAND ${Java_JAVAC_EXECUTABLE} ARGS ${CMAKE_CURRENT_SOURCE_DIR}/${example}.java -d ${EXECUTABLE_OUTPUT_PATH} -classpath ${LIBRARY_OUTPUT_PATH}/gdcm.jar
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${example}.java
    COMMENT "javac ${example}.java"
    )
  list(APPEND classfilesdep ${EXECUTABLE_OUTPUT_PATH}/${example}.class)
  SET_SOURCE_FILES_PROPERTIES(${EXECUTABLE_OUTPUT_PATH}/${example}.class PROPERTIES CLASSPATH "${EXECUTABLE_OUTPUT_PATH}/gdcm.jar")
  ADD_JAVA_TEST(${example}Java ${EXECUTABLE_OUTPUT_PATH}/${example})
ENDFOREACH(example)

# 3. ok now add the target
ADD_CUSTOM_TARGET(GDCMJavaDSEDTests ALL
  DEPENDS ${classfilesdep}
  COMMENT "building gdcm java dsed tests"
)
# make sure gdcm.jar is built
ADD_DEPENDENCIES(GDCMJavaDSEDTests GDCMJavaJar)
