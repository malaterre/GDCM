# Define the tests for vtk-gdcm
# vtkGDCM
set(VTK_GDCM_TEST_SRCS
  TestvtkGDCMImageReader.cxx
  TestvtkGDCMImageReader4.cxx
  TestvtkGDCMImageReaderIsLossy.cxx
  TestvtkGDCMImageWriterIsLossy.cxx
  #TestvtkImageChangeInformation.cxx
  #TestvtkGDCMImageActor.cxx
  #TestvtkGDCMImageViewer.cxx
)
if( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 4.5 )
  set(VTK_GDCM_TEST_SRCS
    ${VTK_GDCM_TEST_SRCS}
    TestvtkGDCMImageWriter1.cxx
    TestvtkGDCMImageWriter2.cxx
    TestvtkGDCMThreadedImageReader2.cxx
    TestvtkGDCMMetaImageWriter.cxx
  )
endif()

if( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 6.0 )
  set(VTK_GDCM_TEST_SRCS
    ${VTK_GDCM_TEST_SRCS}
    TestvtkGDCMImageReader2_1.cxx
    TestvtkGDCMImageReader2_2.cxx
    TestvtkGDCMImageReader2_3.cxx
    TestvtkGDCMMetaImageWriter2.cxx
  )
endif()

# Need gdcmData
if(GDCM_DATA_ROOT)
  set(VTK_GDCM_TEST_SRCS
    ${VTK_GDCM_TEST_SRCS}
    TestvtkGDCMImageReader1.cxx
    )
endif()
# Need gdcmDataExtra
if(GDCM_DATA_EXTRA_ROOT)
  set(VTK_GDCM_TEST_SRCS
    ${VTK_GDCM_TEST_SRCS}
    TestvtkGDCMImageReader3.cxx
    TestvtkGDCMPolyDataReader.cxx
  )
endif()

if(VTK_USE_RENDERING)
  if(GDCM_HAVE_PTHREAD_H AND CMAKE_USE_PTHREADS)
    set(VTK_GDCM_TEST_SRCS
      ${VTK_GDCM_TEST_SRCS}
      TestvtkGDCMThreadedImageReader.cxx
    )
  endif()
endif()

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
target_link_libraries(gdcmvtkGDCMTests vtksys)
if(VTK_USE_RENDERING)
  if( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    target_link_libraries(gdcmvtkGDCMTests vtkRendering)
  elseif( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 6.0 )
    target_link_libraries(gdcmvtkGDCMTests vtkVolumeRendering)
  endif()
endif()
# VTK 6.0 does not set VTK_USE_RENDERING anymore ?
if( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 6.0 )
  target_link_libraries(gdcmvtkGDCMTests ${vtkgdcm_LIBS})
  target_link_libraries(gdcmvtkGDCMTests vtkIOLegacy vtkCommonCore)
endif()

# Need full path to executable:
set(GDCM_VTK_GDCM_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmvtkGDCMTests")

# Loop over files and create executables
foreach(name ${VTK_GDCM_TEST_SRCS})
  get_filename_component(testname ${name} NAME_WE)
  add_test(NAME ${testname} COMMAND ${GDCM_VTK_GDCM_TESTS} ${testname})
endforeach()
