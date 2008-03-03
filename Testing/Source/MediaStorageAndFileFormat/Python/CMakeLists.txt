# Define the tests for gdcm-python
# gdcm-python
SET(GDCM_PYTHON_TEST_SRCS
  TestReader
  TestScanner
  TestImageReader
  TestUIDGenerator
  TestModifyFields
  TestAnonymizer
  )

#FIND_PACKAGE(PythonInterp REQUIRED)
INCLUDE(${GDCM_SOURCE_DIR}/CMake/UsePythonTest.cmake)

# Loop over files and create executables
FOREACH(name ${GDCM_PYTHON_TEST_SRCS})
  SET_SOURCE_FILES_PROPERTIES(${name}.py PROPERTIES PYTHONPATH ${LIBRARY_OUTPUT_PATH})
  ADD_PYTHON_TEST(${name}Python ${name}.py)
ENDFOREACH(name)


