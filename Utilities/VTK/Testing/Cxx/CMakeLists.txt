# Define the tests for vtk-gdcm
# vtkGDCM
set(VTK_GDCM_TEST_SRCS
  TestvtkGDCMImageReader
  TestvtkGDCMImageReader4
  TestvtkGDCMImageReaderIsLossy
  TestvtkGDCMImageWriterIsLossy
  #TestvtkImageChangeInformation
  #TestvtkGDCMImageActor
  #TestvtkGDCMImageViewer
)
if( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 4.5 )
  set(VTK_GDCM_TEST_SRCS
    ${VTK_GDCM_TEST_SRCS}
    TestvtkGDCMImageWriter1
    TestvtkGDCMImageWriter2
    TestvtkGDCMThreadedImageReader2
    TestvtkGDCMMetaImageWriter
  )
endif( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 4.5 )

# Need gdcmData
if(GDCM_DATA_ROOT)
  set(VTK_GDCM_TEST_SRCS
    ${VTK_GDCM_TEST_SRCS}
    TestvtkGDCMImageReader2
    )
endif(GDCM_DATA_ROOT)
# Need gdcmDataExtra
if(GDCM_DATA_EXTRA_ROOT)
  set(VTK_GDCM_TEST_SRCS
    ${VTK_GDCM_TEST_SRCS}
    TestvtkGDCMImageReader3
    TestvtkGDCMPolyDataReader
  )
endif(GDCM_DATA_EXTRA_ROOT)

if(VTK_USE_RENDERING)
  if(GDCM_HAVE_PTHREAD_H AND CMAKE_USE_PTHREADS)
    set(VTK_GDCM_TEST_SRCS
      ${VTK_GDCM_TEST_SRCS}
      TestvtkGDCMThreadedImageReader
    )
  endif(GDCM_HAVE_PTHREAD_H AND CMAKE_USE_PTHREADS)
endif(VTK_USE_RENDERING)

# Add the include paths
include_directories(
  "${GDCM_SOURCE_DIR}/Utilities/VTK"
  "${GDCM_BINARY_DIR}/Testing/Source/Data" # for gdcmDataImages.h
  )

create_test_sourcelist(vtkGDCMTests gdcmvtkGDCMTests.cxx ${VTK_GDCM_TEST_SRCS}
  EXTRA_INCLUDE gdcmTestDriver.h
  )
add_executable(gdcmvtkGDCMTests ${vtkGDCMTests})
target_link_libraries(gdcmvtkGDCMTests ${VTKGDCM_NAME} gdcmMSFF)
if(VTK_USE_RENDERING)
  if( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    target_link_libraries(gdcmvtkGDCMTests vtkRendering)
  else( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    target_link_libraries(gdcmvtkGDCMTests vtkVolumeRendering)
  endif( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
endif(VTK_USE_RENDERING)

# Need full path to executable:
set(GDCM_VTK_GDCM_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmvtkGDCMTests")

# Loop over files and create executables
foreach(name ${VTK_GDCM_TEST_SRCS})
  add_test(${name} ${GDCM_VTK_GDCM_TESTS} ${name})
endforeach(name)
