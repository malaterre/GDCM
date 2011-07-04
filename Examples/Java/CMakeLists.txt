FIND_PACKAGE(Java REQUIRED) # javac, jar
FIND_PACKAGE(JNI REQUIRED)
INCLUDE_DIRECTORIES(
  #${JNI_INCLUDE_PATH}
  ${JAVA_INCLUDE_PATH}
  ${JAVA_INCLUDE_PATH2}
  ${JAVA_AWT_INCLUDE_PATH}
  )

set(classfilesdep)
set(examples
  HelloSimple
  DecompressPixmap
  ScanDirectory
  ReadFiles
  )
FOREACH(example ${examples})
  ADD_CUSTOM_COMMAND(
    OUTPUT ${EXECUTABLE_OUTPUT_PATH}/${example}.class
    COMMAND ${JAVA_COMPILE} ARGS ${CMAKE_CURRENT_SOURCE_DIR}/${example}.java -d ${EXECUTABLE_OUTPUT_PATH} -classpath ${LIBRARY_OUTPUT_PATH}/gdcm.jar
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${example}.java
    COMMENT "javac ${example}.java"
    )
  list(APPEND classfilesdep ${EXECUTABLE_OUTPUT_PATH}/${example}.class)
ENDFOREACH(example)

# 3. ok now add the target
ADD_CUSTOM_TARGET(GDCMJavaExample ALL
  DEPENDS ${classfilesdep}
  COMMENT "building gdcm java example"
)
# make sure gdcm.jar is built
ADD_DEPENDENCIES(GDCMJavaExample GDCMJavaJar)

IF(BUILD_TESTING)
  IF(GDCM_DATA_ROOT)
    SET_SOURCE_FILES_PROPERTIES(${EXECUTABLE_OUTPUT_PATH}/HelloSimple.class PROPERTIES CLASSPATH "${EXECUTABLE_OUTPUT_PATH}/gdcm.jar")
    ADD_JAVA_TEST(TestHelloSimpleJava ${EXECUTABLE_OUTPUT_PATH}/HelloSimple ${GDCM_DATA_ROOT}/012345.002.050.dcm)
  ENDIF(GDCM_DATA_ROOT)
ENDIF(BUILD_TESTING)
