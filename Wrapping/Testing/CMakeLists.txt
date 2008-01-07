# Define the tests for gdcm-python
# gdcm-python
SET(GDCM_PYTHON_TEST_SRCS
  TestReader
  TestImageReader
  )

#FIND_PACKAGE(PythonInterp REQUIRED)
INCLUDE(${GDCM_SOURCE_DIR}/CMake/UsePythonTest.cmake)

# Loop over files and create executables
FOREACH(name ${GDCM_PYTHON_TEST_SRCS})
  #ADD_TEST(${name}Python "PYTHONPATH=./Wrapping:./bin" ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${name}.py)
  #ADD_TEST(${name}Python ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${name}.py)
  SET_SOURCE_FILES_PROPERTIES(${name}.py PROPERTIES PYTHONPATH
    "${LIBRARY_OUTPUT_PATH}:${GDCM_BINARY_DIR}/Wrapping")
  ADD_PYTHON_TEST(${name}Python ${name}.py ${GDCM_DATA_ROOT}/test.acr)
ENDFOREACH(name)


