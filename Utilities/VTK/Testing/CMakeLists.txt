# Define the tests for vtk-gdcm
# vtkGDCM
SET(VTK_GDCM_TEST_SRCS
  TestvtkGDCMReader
  TestvtkGDCMThreadedReader
  #TestvtkGDCMImageActor
  TestvtkGDCMWriter
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_SOURCE_DIR}/Utilities/VTK"
  "${GDCM_BINARY_DIR}/Testing/Source/Data" # for gdcmDataImages.h
  )

CREATE_TEST_SOURCELIST(vtkGDCMTests gdcmvtkGDCMTests.cxx ${VTK_GDCM_TEST_SRCS})
ADD_EXECUTABLE(gdcmvtkGDCMTests ${vtkGDCMTests})
TARGET_LINK_LIBRARIES(gdcmvtkGDCMTests vtkgdcm)

#Don't understand why I need that ??
SET(GDCM_VTK_GDCM_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmvtkGDCMTests")

# Loop over files and create executables
FOREACH(name ${VTK_GDCM_TEST_SRCS})
  ADD_TEST(${name} ${GDCM_VTK_GDCM_TESTS} ${name})
ENDFOREACH(name)


