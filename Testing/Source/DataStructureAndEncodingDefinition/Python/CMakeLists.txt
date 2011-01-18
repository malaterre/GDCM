# Define the tests for gdcm-python
# gdcm-python
SET(GDCM_PYTHON_TEST_SRCS
  TestReader
  TestTag
  )

# Loop over files and create executables
FOREACH(name ${GDCM_PYTHON_TEST_SRCS})
  ADD_PYTHON_TEST(${name}Python ${name}.py)
ENDFOREACH(name)
