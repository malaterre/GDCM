# Define the tests for gdcm-python
# gdcm-python
SET(GDCM_PYTHON_TEST_SRCS
  TestScanner
  TestImageReader
  TestUIDGenerator
  TestModifyFields
  TestAnonymizer
  #TestStringFilter
  )
IF(BUILD_APPLICATIONS)
  SET(GDCM_PYTHON_TEST_SRCS
    ${GDCM_PYTHON_TEST_SRCS}
    TestDCMTKMD5 # need dcmdrle and dcmdjpeg
  )
ENDIF(BUILD_APPLICATIONS)

# Loop over files and create executables
FOREACH(name ${GDCM_PYTHON_TEST_SRCS})
  ADD_PYTHON_TEST(${name}Python ${name}.py)
ENDFOREACH(name)

# Special test that need extra arg:
# TestKakaduDecompressionMD5
FIND_PACKAGE(KAKADU)
IF(BUILD_APPLICATIONS)
  IF(KDU_EXPAND_EXECUTABLE)
    ADD_PYTHON_TEST(TestKakaduDecompressionMD5Python TestKakaduDecompressionMD5.py ${KDU_EXPAND_EXECUTABLE})
  ENDIF(KDU_EXPAND_EXECUTABLE)
ENDIF(BUILD_APPLICATIONS)

