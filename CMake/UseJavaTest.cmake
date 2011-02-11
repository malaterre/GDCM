# Add a java test from a java file
#
# Usage:
# SET_SOURCE_FILES_PROPERTIES(test.py PROPERTIES PYTHONPATH
#   "${LIBRARY_OUTPUT_PATH}:${VTK_DIR}")
# ADD_PYTHON_TEST(PYTHON-TEST test.py)
#
#  Copyright (c) 2006-2011 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

# Need python interpreter:
#FIND_PACKAGE(PythonInterp REQUIRED)
#MARK_AS_ADVANCED(PYTHON_EXECUTABLE)
# UseCSharp.cmake

MACRO(ADD_JAVA_TEST TESTNAME FILENAME)
  GET_SOURCE_FILE_PROPERTY(loc ${FILENAME}.class LOCATION)
  GET_SOURCE_FILE_PROPERTY(pyenv ${FILENAME}.class RUNTIMEPATH)
  GET_SOURCE_FILE_PROPERTY(theclasspath ${FILENAME}.class CLASSPATH)
  get_filename_component(loc2 ${loc} NAME_WE)


  IF(CMAKE_CONFIGURATION_TYPES)
    # I cannot use CMAKE_CFG_INTDIR since it expand to "$(OutDir)"
    IF(pyenv)
      SET(pyenv "${pyenv};${LIBRARY_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}")
    ELSE(pyenv)
      SET(pyenv ${LIBRARY_OUTPUT_PATH}/${CMAKE_BUILD_TYPE})
      #SET(pyenv ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR})
      #SET(pyenv ${LIBRARY_OUTPUT_PATH}/${CMAKE_CONFIG_TYPE})
      #SET(pyenv ${LIBRARY_OUTPUT_PATH}/\${CMAKE_CONFIG_TYPE})
    ENDIF(pyenv)
  ELSE(CMAKE_CONFIGURATION_TYPES)
    IF(pyenv)
      SET(pyenv ${pyenv}:${LIBRARY_OUTPUT_PATH})
    ELSE(pyenv)
      SET(pyenv ${LIBRARY_OUTPUT_PATH})
    ENDIF(pyenv)
   ENDIF(CMAKE_CONFIGURATION_TYPES)
  STRING(REGEX REPLACE ";" " " wo_semicolumn "${ARGN}")

  set(classpath)
  if(theclasspath)
    set(classpath "${theclasspath}:.")
  else(theclasspath)
    set(classpath ".")
  endif(theclasspath)
  set(theld_library_path $ENV{LD_LIBRARY_PATH})
  set(ld_library_path)
  if(theld_library_path)
    set(ld_library_path ${theld_library_path})
  endif(theld_library_path)
  if(pyenv)
    set(ld_library_path ${ld_library_path}:${pyenv})
  endif(pyenv)

  FILE(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${TESTNAME}.cmake
"
  SET(ENV{LD_LIBRARY_PATH} ${ld_library_path})
  #SET(ENV{CLASSPATH} ${pyenv}/gdcm.jar:.)
  MESSAGE(\"pyenv: ${pyenv}\")
  MESSAGE(\"loc: ${loc}\")
  MESSAGE(\"loc2: ${loc2}\")
  #message( \"wo_semicolumn: ${wo_semicolumn}\" )
  EXECUTE_PROCESS(
    COMMAND ${JAVA_RUNTIME} -classpath ${classpath} ${loc2} ${wo_semicolumn}
    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
    RESULT_VARIABLE import_res
    OUTPUT_VARIABLE import_output
    ERROR_VARIABLE  import_output
  )

  # Pass the output back to ctest
  IF(import_output)
    MESSAGE("\${import_output}")
  ENDIF(import_output)
  IF(import_res)
    MESSAGE(SEND_ERROR "\${import_res}")
  ENDIF(import_res)
"
)
  ADD_TEST(${TESTNAME} ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/${TESTNAME}.cmake)
ENDMACRO(ADD_JAVA_TEST)

# Byte compile recursively a directory (DIRNAME)
#MACRO(ADD_PYTHON_COMPILEALL_TEST DIRNAME)
#  # First get the path:
#  GET_FILENAME_COMPONENT(temp_path "${PYTHON_LIBRARIES}" PATH)
#  # Find the python script:
#  GET_FILENAME_COMPONENT(PYTHON_COMPILE_ALL_PY "${temp_path}/../compileall.py" ABSOLUTE)
#  # add test, use DIRNAME to create uniq name for the test:
#  ADD_TEST(COMPILE_ALL-${DIRNAME} ${PYTHON_EXECUTABLE} "${PYTHON_COMPILE_ALL_PY}" -q ${DIRNAME})
#ENDMACRO(ADD_PYTHON_COMPILEALL_TEST)
#
