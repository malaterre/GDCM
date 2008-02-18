PROJECT(vtkgdcm)
# We need VTK
# Technically we require VTK 5.0 and above
FIND_PACKAGE(VTK REQUIRED)

# Define the src for the vtk-gdcm bridge
SET(vtkgdcm_SRCS
  vtkGDCMImageReader.cxx
  vtkGDCMThreadedImageReader.cxx
  vtkGDCMImageWriter.cxx
  )

INCLUDE(${VTK_USE_FILE})
INCLUDE_DIRECTORIES(
  ${GDCM_BINARY_DIR}/Source/Common
  ${GDCM_SOURCE_DIR}/Source/Common
  ${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition
  ${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat
  ${GDCM_SOURCE_DIR}/Source/DataDictionary
  )

# List the kits from VTK that are needed by this project.
SET(vtkgdcm_LIBS
  vtkCommon
  vtkIO
)

# Use wrapping hints for this project.
#SET(VTK_WRAP_HINTS "${PROJECT_SOURCE_DIR}/hints")

# Create the instantiator for these classes.
# FIXME: Are instantiator really needed when only doing python wrapping ?
IF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
  # Setup vtkInstantiator registration for this library's classes.
    INCLUDE_DIRECTORIES(
      ${GDCM_BINARY_DIR}
    )
  VTK_MAKE_INSTANTIATOR2(
    "${PROJECT_NAME}Instantiator"
    vtkgdcmInstantiator_SRCS
    "${vtkgdcm_SRCS}"
                       EXPORT_MACRO "" #GDCM_EXPORT
                       HEADER_LOCATION ${GDCM_BINARY_DIR})
ELSE( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
  SET(VTK_USE_INSTANTIATOR_NEW 1)
  VTK_MAKE_INSTANTIATOR3(
    "${PROJECT_NAME}Instantiator"
    vtkgdcmInstantiator_SRCS
    "${vtkgdcm_SRCS}"
    "" #"VTK_${PROJECT_NAME}_EXPORT"
    ${PROJECT_BINARY_DIR}
    "" #"${PROJECT_NAME}Configure.h"
  )
ENDIF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )

ADD_LIBRARY(vtkgdcm ${vtkgdcm_SRCS} ${vtkgdcmInstantiator_SRCS})
TARGET_LINK_LIBRARIES(vtkgdcm gdcmMSFF ${vtkgdcm_LIBS})
INSTALL(TARGETS vtkgdcm
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
	)

IF(BUILD_WRAPPING)
  IF(VTK_WRAP_PYTHON)
    INCLUDE(${VTK_CMAKE_DIR}/vtkWrapPython.cmake)
IF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    VTK_WRAP_PYTHON2(${PROJECT_NAME}Python vtkgdcmPYTHON_SRCS ${vtkgdcm_SRCS})
ELSE( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    INCLUDE_DIRECTORIES(
      ${CMAKE_CURRENT_SOURCE_DIR}
    )
    VTK_WRAP_PYTHON3(${PROJECT_NAME}Python vtkgdcmPYTHON_SRCS "${vtkgdcm_SRCS}")
ENDIF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    ADD_LIBRARY(${PROJECT_NAME}PythonD ${vtkgdcmPYTHON_SRCS})
    ADD_LIBRARY(${PROJECT_NAME}Python MODULE ${PROJECT_NAME}PythonInit.cxx)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME}PythonD ${PROJECT_NAME})
    FOREACH(c ${vtkgdcm_LIBS})
      TARGET_LINK_LIBRARIES(${PROJECT_NAME}PythonD ${c}PythonD)
    ENDFOREACH(c)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME}Python ${PROJECT_NAME}PythonD)
    ADD_CUSTOM_COMMAND(
      TARGET    ${PROJECT_NAME}Python
      POST_BUILD
      COMMAND   cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm.py ${LIBRARY_OUTPUT_PATH}
      #DEPENDS "${swig_generated_file_fullname}"
      COMMENT   "Copy vtkgdcm.py into ${LIBRARY_OUTPUT_PATH}"
    )
    INSTALL(TARGETS ${PROJECT_NAME}PythonD ${PROJECT_NAME}Python
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
	)
  ENDIF(VTK_WRAP_PYTHON)
ENDIF(BUILD_WRAPPING)

IF(BUILD_TESTING)
  SUBDIRS(Testing)
ENDIF(BUILD_TESTING)

IF(BUILD_APPLICATIONS)
  SUBDIRS(Applications)
ENDIF(BUILD_APPLICATIONS)

