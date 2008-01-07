# Define the tests for gdcm-python
# vtk-python
SET(GDCM_PYTHON_TEST_SRCS
  TestReader
  TestImageReader
  )

# Loop over files and create executables
FOREACH(name ${GDCM_PYTHON_TEST_SRCS})
  ADD_TEST(${name}Python ${CMAKE_CURRENT_SOURCE_DIR}/${name}.py)
ENDFOREACH(name)


