# Define the tests for gdcm-python
# gdcm-python
SET(GDCM_PYTHON_TEST_SRCS
  TestTesting
  TestDirectory
  )


# Loop over files and create executables
FOREACH(name ${GDCM_PYTHON_TEST_SRCS})
  ADD_PYTHON_TEST(${name}Python ${name}.py ${GDCM_DATA_ROOT}/test.acr)
ENDFOREACH(name)
