# Define the tests for gdcm-python
# gdcm-python
SET(GDCM_PYTHON_TEST_SRCS
  TestScanner
  TestImageReader
  TestUIDGenerator
  TestModifyFields
  TestAnonymizer
  #TestStringFilter
  TestOrientation
  TestIPPSorter
  #TestPythonFilter
  )
IF(BUILD_APPLICATIONS)
  IF(DCMTK_DCMDUMP_EXECUTABLE)
  IF(UNIX)
    SET(GDCM_PYTHON_TEST_SRCS
      ${GDCM_PYTHON_TEST_SRCS}
      TestDCMTKMD5 # need dcmdrle and dcmdjpeg
    )
  ENDIF(UNIX)
  ENDIF(DCMTK_DCMDUMP_EXECUTABLE)
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
  IF(UNIX)
    ADD_PYTHON_TEST(TestKakaduDecompressionMD5Python TestKakaduDecompressionMD5.py ${KDU_EXPAND_EXECUTABLE})
  ENDIF(UNIX)
  ENDIF(KDU_EXPAND_EXECUTABLE)
ENDIF(BUILD_APPLICATIONS)
