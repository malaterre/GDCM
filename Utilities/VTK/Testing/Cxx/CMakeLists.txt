# Define the tests for vtk-gdcm
# vtkGDCM
SET(VTK_GDCM_TEST_SRCS
  TestvtkGDCMImageReader
  TestvtkGDCMThreadedImageReader
  #TestvtkGDCMImageActor
  TestvtkGDCMImageWriter
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_SOURCE_DIR}/Utilities/VTK"
  "${GDCM_BINARY_DIR}/Testing/Source/Data" # for gdcmDataImages.h
  )

CREATE_TEST_SOURCELIST(vtkGDCMTests gdcmvtkGDCMTests.cxx ${VTK_GDCM_TEST_SRCS})
ADD_EXECUTABLE(gdcmvtkGDCMTests ${vtkGDCMTests})
TARGET_LINK_LIBRARIES(gdcmvtkGDCMTests vtkgdcm vtkVolumeRendering)

# Need full path to executable:
SET(GDCM_VTK_GDCM_TESTS "${EXECUTABLE_OUTPUT_PATH}/gdcmvtkGDCMTests")

# Loop over files and create executables
FOREACH(name ${VTK_GDCM_TEST_SRCS})
  ADD_TEST(${name} ${GDCM_VTK_GDCM_TESTS} ${name})
ENDFOREACH(name)

#IF(BUILD_WRAPPING)
#  INCLUDE(${GDCM_SOURCE_DIR}/CMake/UsePythonTest.cmake)
#
#  #MESSAGE(${VTK_DIR})
#  #MESSAGE(${VTK_LIBRARY_DIRS})
#  #MESSAGE(${VTK_PYTHONPATH_DIRS})
#  STRING(REGEX REPLACE ";" ":" UNIX_VTK_PYTHONPATH_DIRS "${VTK_PYTHONPATH_DIRS}")
#  SET_SOURCE_FILES_PROPERTIES(TestvtkGDCMThreadedImageReader.py PROPERTIES PYTHONPATH
#    "${UNIX_VTK_PYTHONPATH_DIRS}:${LIBRARY_OUTPUT_PATH}")
#  ADD_PYTHON_TEST(TestvtkGDCMThreadedImageReaderPython TestvtkGDCMThreadedImageReader.py ${GDCM_DATA_ROOT}/test.acr)
#
#ENDIF(BUILD_WRAPPING)
#
