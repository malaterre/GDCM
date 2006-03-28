# Define the tests
SET(TEST_SRCS
  TestPersonName
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/ValueRepresentations"
  )

CREATE_TEST_SOURCELIST(ValueRepresentationsTests gdcmValueRepresentationsTests.cxx ${TEST_SRCS})
ADD_EXECUTABLE(gdcmValueRepresentationsTests ${ValueRepresentationsTests})
TARGET_LINK_LIBRARIES(gdcmValueRepresentationsTests gdcmValueRepresentations)

#Don't understand why I need that ??
SET(GDCM_VR_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmValueRepresentationsTests")

# Loop over files and create executables
FOREACH(name ${TEST_SRCS})
  ADD_TEST(${name} ${GDCM_VR_TESTS} ${name})
ENDFOREACH(name)


