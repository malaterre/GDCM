# Define the tests for vtk-gdcm
# vtkGDCM
SET(VTK_GDCM_TEST_SRCS
  TestvtkGDCMImageReader
  TestvtkGDCMImageReader2
  TestvtkGDCMImageReader4
  TestvtkGDCMImageReaderIsLossy
  #TestvtkGDCMImageActor
  #TestvtkGDCMImageViewer
)
IF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 4.5 )
  SET(VTK_GDCM_TEST_SRCS
    ${VTK_GDCM_TEST_SRCS}
    TestvtkGDCMImageWriter1
    TestvtkGDCMImageWriter2
    TestvtkGDCMThreadedImageReader2
  )
ENDIF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 4.5 )

# Need gdcmDataExtra
IF(GDCM_DATA_EXTRA_ROOT)
  SET(VTK_GDCM_TEST_SRCS
    ${VTK_GDCM_TEST_SRCS}
    TestvtkGDCMImageReader3
    TestvtkGDCMPolyDataReader
  )
ENDIF(GDCM_DATA_EXTRA_ROOT)
IF(CMAKE_HAVE_PTHREAD_H)
  SET(VTK_GDCM_TEST_SRCS
    ${VTK_GDCM_TEST_SRCS}
    TestvtkGDCMThreadedImageReader
  )
ENDIF(CMAKE_HAVE_PTHREAD_H)

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_SOURCE_DIR}/Utilities/VTK"
  "${GDCM_BINARY_DIR}/Testing/Source/Data" # for gdcmDataImages.h
  )

CREATE_TEST_SOURCELIST(vtkGDCMTests gdcmvtkGDCMTests.cxx ${VTK_GDCM_TEST_SRCS})
ADD_EXECUTABLE(gdcmvtkGDCMTests ${vtkGDCMTests})
IF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
  TARGET_LINK_LIBRARIES(gdcmvtkGDCMTests ${VTKGDCM_NAME} vtkRendering)
ELSE( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
  TARGET_LINK_LIBRARIES(gdcmvtkGDCMTests ${VTKGDCM_NAME} vtkVolumeRendering)
ENDIF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )

# Need full path to executable:
SET(GDCM_VTK_GDCM_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmvtkGDCMTests")

# Loop over files and create executables
FOREACH(name ${VTK_GDCM_TEST_SRCS})
  ADD_TEST(${name} ${GDCM_VTK_GDCM_TESTS} ${name})
ENDFOREACH(name)

