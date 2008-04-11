PROJECT(vtkgdcm)
# We need VTK
# Technically we require VTK 5.0 and above
FIND_PACKAGE(VTK REQUIRED)

# Define the src for the vtk-gdcm bridge
SET(vtkgdcm_SRCS
  vtkGDCMImageReader.cxx
  vtkGDCMImageWriter.cxx
  )

# Need pthread for the following class:
CHECK_INCLUDE_FILE("pthread.h"      CMAKE_HAVE_PTHREAD_H)

IF(CMAKE_HAVE_PTHREAD_H)
  SET(vtkgdcm_SRCS ${vtkgdcm_SRCS}
  vtkGDCMThreadedImageReader.cxx
  )
ENDIF(CMAKE_HAVE_PTHREAD_H)

INCLUDE(${VTK_USE_FILE})
INCLUDE_DIRECTORIES(
  ${GDCM_BINARY_DIR}/Source/Common
  ${GDCM_SOURCE_DIR}/Source/Common
  ${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition
  ${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat
  ${GDCM_SOURCE_DIR}/Source/DataDictionary
  )

# FIXME: temp fix
IF(UNIX)
  LINK_DIRECTORIES(/usr/X11R6/lib)
ENDIF(UNIX)

# List the kits from VTK that are needed by this project.
SET(vtkgdcm_LIBS
  vtkCommon
  vtkIO
  vtkImaging
  vtkRendering
)

# Use wrapping hints for this project.
#SET(VTK_WRAP_HINTS "${PROJECT_SOURCE_DIR}/hints")

# Create the instantiator for these classes.
# FIXME: Are instantiator really needed when only doing python wrapping ?
IF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
  SET(vtkgdcm_SRCS ${vtkgdcm_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/VTK4/vtkMedicalImageProperties.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/VTK4/vtkStringArray.cxx
  )
  # Setup vtkInstantiator registration for this library's classes.
  INCLUDE_DIRECTORIES(
    ${GDCM_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/VTK4
  )
  VTK_MAKE_INSTANTIATOR2(
    "${PROJECT_NAME}Instantiator"
    vtkgdcmInstantiator_SRCS
    "${vtkgdcm_SRCS}"
    EXPORT_MACRO "" #GDCM_EXPORT
    HEADER_LOCATION ${GDCM_BINARY_DIR}
  )
ELSE( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
  SET(vtkgdcm_SRCS ${vtkgdcm_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkImageColorViewer.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkImageMapToWindowLevelColors2.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkImageYBRToRGB.cxx
  )

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
IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS vtkgdcm
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
  )
ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)

IF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
  SET(header_files_glob "*.h" "*.txx")
  IF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    SET(header_files_glob ${header_files_glob}
      "VTK4/*.h"
    )
  ENDIF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
  FILE(GLOB header_files ${header_files_glob})
  INSTALL(FILES ${header_files}
    DESTINATION ${GDCM_INSTALL_INCLUDE_DIR} COMPONENT Development
  )
ENDIF(NOT GDCM_INSTALL_NO_DEVELOPMENT)

IF(BUILD_WRAPPING)
  IF(VTK_WRAP_PYTHON)
      SET(DEXTENSION "")
    IF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
        VTK_WRAP_PYTHON2(${PROJECT_NAME}Python vtkgdcmPYTHON_SRCS ${vtkgdcm_SRCS})
    ELSE( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    INCLUDE(${VTK_CMAKE_DIR}/vtkWrapPython.cmake)
        INCLUDE_DIRECTORIES(
          ${CMAKE_CURRENT_SOURCE_DIR}
        )
        VTK_WRAP_PYTHON3(${PROJECT_NAME}Python vtkgdcmPYTHON_SRCS "${vtkgdcm_SRCS}")
      SET(DEXTENSION "D")
    ENDIF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    ADD_LIBRARY(${PROJECT_NAME}PythonD ${vtkgdcmPYTHON_SRCS})
    ADD_LIBRARY(${PROJECT_NAME}Python MODULE ${PROJECT_NAME}PythonInit.cxx)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME}PythonD ${PROJECT_NAME})
    FOREACH(c ${vtkgdcm_LIBS})
      TARGET_LINK_LIBRARIES(${PROJECT_NAME}PythonD ${c}Python${DEXTENSION})
    ENDFOREACH(c)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME}Python ${PROJECT_NAME}PythonD)
# Python extension modules on Windows must have the extension ".pyd"
# instead of ".dll" as of Python 2.5.  Older python versions do support
# this suffix.
IF(WIN32 AND NOT CYGWIN)
  SET_TARGET_PROPERTIES(${PROJECT_NAME}Python PROPERTIES SUFFIX ".pyd")
ENDIF(WIN32 AND NOT CYGWIN)

    ADD_CUSTOM_COMMAND(
      TARGET    ${PROJECT_NAME}Python
      POST_BUILD
      COMMAND   cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm.py ${LIBRARY_OUTPUT_PATH}
      DEPENDS   "${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm.py"
      COMMENT   "Copy vtkgdcm.py into ${LIBRARY_OUTPUT_PATH}"
    )
IF(NOT GDCM_INSTALL_NO_LIBRARIES)
    INSTALL(TARGETS ${PROJECT_NAME}PythonD ${PROJECT_NAME}Python
      RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
      LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime
      ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
    )
# the python file is not a dev file, but part of the gdcm module...
  INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm.py 
    DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime
  )
ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)

  ENDIF(VTK_WRAP_PYTHON)
ENDIF(BUILD_WRAPPING)

IF(BUILD_TESTING)
  SUBDIRS(Testing)
ENDIF(BUILD_TESTING)

IF(BUILD_APPLICATIONS)
  SUBDIRS(Applications)
ENDIF(BUILD_APPLICATIONS)

