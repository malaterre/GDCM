# Define the C++ tests for itk-gdcm
# 
SET(ITK_GDCM_TEST_SRCS
  TestitkGDCMImageIO
)
INCLUDE_DIRECTORIES(
  ${itk_gdcm_SOURCE_DIR}
)

CREATE_TEST_SOURCELIST(itkGDCMTests gdcmitkGDCMTests.cxx ${ITK_GDCM_TEST_SRCS})
ADD_EXECUTABLE(gdcmitkGDCMTests ${itkGDCMTests})
#TARGET_LINK_LIBRARIES(gdcmitkGDCMTests ${ITKGDCM_NAME} ITKIO)
TARGET_LINK_LIBRARIES(gdcmitkGDCMTests ${ITKGDCM_NAME} itkgdcm2)

# Need full path to executable:
SET(GDCM_ITK_GDCM_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmitkGDCMTests")

# Loop over files and create executables
FOREACH(name ${ITK_GDCM_TEST_SRCS})
  ADD_TEST(${name} ${GDCM_ITK_GDCM_TESTS} ${name})
ENDFOREACH(name)
