# Define the tests for vtkgdcm-java
SET(VTKGDCM_JAVA_TEST_SRCS
  TestvtkGDCMImageReader
  )

set(classpath ${LIBRARY_OUTPUT_PATH}/vtkgdcm.jar${JavaProp_PATH_SEPARATOR}${LIBRARY_OUTPUT_PATH}/gdcm.jar${JavaProp_PATH_SEPARATOR}${VTK_JAVA_JAR}${JavaProp_PATH_SEPARATOR}${GDCM_VTK_JAVA_JAR})

if(IS_DIRECTORY ${VTK_DIR})
  if(IS_DIRECTORY ${VTK_DIR}/bin)
    # this is a build-tree VTK
    set(runtimepath "${VTK_DIR}/bin")
    if(UNIX)
      get_filename_component(dummyjava ${JAVA_MAWT_LIBRARY} PATH)
      set(runtimepath "${runtimepath}:${JAVA_LIBRARY_PATH}:${dummyjava}")
    endif()
  endif()
endif()

set(classfilesdep)

FOREACH(example ${VTKGDCM_JAVA_TEST_SRCS})
  ADD_CUSTOM_COMMAND(
    OUTPUT ${EXECUTABLE_OUTPUT_PATH}/${example}.class
    COMMAND ${Java_JAVAC_EXECUTABLE} ARGS -classpath "${classpath}"
    ${CMAKE_CURRENT_SOURCE_DIR}/${example}.java -d ${EXECUTABLE_OUTPUT_PATH}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${example}.java
    COMMENT "javac ${example}.java"
    )
  list(APPEND classfilesdep ${EXECUTABLE_OUTPUT_PATH}/${example}.class)
  SET_SOURCE_FILES_PROPERTIES(${EXECUTABLE_OUTPUT_PATH}/${example}.class PROPERTIES RUNTIMEPATH "${runtimepath}")
  SET_SOURCE_FILES_PROPERTIES(${EXECUTABLE_OUTPUT_PATH}/${example}.class PROPERTIES CLASSPATH "${classpath}")
  IF(GDCM_WRAP_JAVA)
    ADD_JAVA_TEST(${example}Java ${EXECUTABLE_OUTPUT_PATH}/${example})
  ENDIF(GDCM_WRAP_JAVA)

ENDFOREACH(example)

# 3. ok now add the target
ADD_CUSTOM_TARGET(VTKGDCMJavaTests ALL
  DEPENDS ${classfilesdep}
  COMMENT "building gdcm java vtk tests"
)
ADD_DEPENDENCIES(VTKGDCMJavaTests VTKGDCMJavaJar
  GDCMJavaJar)
