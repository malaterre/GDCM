# Define the tests for vtkgdcm-java
SET(VTKGDCM_JAVA_TEST_SRCS
  TestvtkGDCMImageReader
  )

FIND_PACKAGE(Java 1.5 REQUIRED)
FIND_PACKAGE(JNI REQUIRED)
INCLUDE_DIRECTORIES(
  ${JNI_INCLUDE_PATH}
  )

if(UNIX)
  set(classpath ${LIBRARY_OUTPUT_PATH}/vtkgdcm.jar:${LIBRARY_OUTPUT_PATH}/gdcm.jar:${VTK_JAVA_JAR}:${GDCM_VTK_JAVA_JAR})
else(UNIX)
  set(classpath ${LIBRARY_OUTPUT_PATH}/vtkgdcm.jar\;${LIBRARY_OUTPUT_PATH}/gdcm.jar\;${VTK_JAVA_JAR}\;${GDCM_VTK_JAVA_JAR})
endif(UNIX)

if(IS_DIRECTORY ${VTK_DIR})
  if(IS_DIRECTORY ${VTK_DIR}/bin)
    # this is a build-tree VTK
    set(runtimepath "${VTK_DIR}/bin")
    #get_filename_component(dummyjava ${JAVA_AWT_LIBRARY} PATH)
    #set(JAVA_MAWT_LIBRARY ${dummyjava}/headless)
    #set(runtimepath "${runtimepath}:${dummyjava}/headless")
    set(runtimepath "${runtimepath}:${JAVA_LIBRARY_PATH}")
  endif()
endif()

set(classfilesdep)

FOREACH(example ${VTKGDCM_JAVA_TEST_SRCS})
  ADD_CUSTOM_COMMAND(
    OUTPUT ${EXECUTABLE_OUTPUT_PATH}/${example}.class
    COMMAND ${JAVA_COMPILE} ARGS -classpath "${classpath}"
    ${CMAKE_CURRENT_SOURCE_DIR}/${example}.java -d ${EXECUTABLE_OUTPUT_PATH}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${example}.java
    COMMENT "javac ${example}.java"
    )
  list(APPEND classfilesdep ${EXECUTABLE_OUTPUT_PATH}/${example}.class)
  SET_SOURCE_FILES_PROPERTIES(${EXECUTABLE_OUTPUT_PATH}/${example}.class PROPERTIES RUNTIMEPATH "${runtimepath}")
  SET_SOURCE_FILES_PROPERTIES(${EXECUTABLE_OUTPUT_PATH}/${example}.class PROPERTIES CLASSPATH "${classpath}")
  ADD_JAVA_TEST(${example}Java ${EXECUTABLE_OUTPUT_PATH}/${example})

ENDFOREACH(example)

# 3. ok now add the target
ADD_CUSTOM_TARGET(VTKGDCMJavaTests ALL
  DEPENDS ${classfilesdep}
  COMMENT "building gdcm java vtk tests"
)
ADD_DEPENDENCIES(VTKGDCMJavaTests VTKGDCMJavaJar)
