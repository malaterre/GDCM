# Define the tests for gdcm-python
# gdcm-python
SET(GDCM_PYTHON_TEST_SRCS
  TestScanner
  TestImageReader
  TestUIDGenerator
  TestModifyFields
  TestAnonymizer
  #TestStringFilter
  TestDCMTKMD5
  )
IF(BUILD_APPLICATIONS)
  SET(GDCM_PYTHON_TEST_SRCS
    ${GDCM_PYTHON_TEST_SRCS}
    TestKakaduDecompressionMD5
  )
ENDIF(BUILD_APPLICATIONS)

# Loop over files and create executables
FOREACH(name ${GDCM_PYTHON_TEST_SRCS})
  ADD_PYTHON_TEST(${name}Python ${name}.py)
ENDFOREACH(name)

