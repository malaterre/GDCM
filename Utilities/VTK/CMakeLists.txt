PROJECT(vtkgdcm)
# We need VTK
# Technically we require VTK 5.0 and above
FIND_PACKAGE(VTK REQUIRED)
MARK_AS_ADVANCED(VTK_DIR)

# Define the src for the vtk-gdcm bridge
SET(vtkgdcm_SRCS
  vtkGDCMImageReader.cxx
  vtkGDCMImageWriter.cxx
  )

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
#IF(UNIX)
#  LINK_DIRECTORIES(/usr/X11R6/lib)
#ENDIF(UNIX)

# List the kits from VTK that are needed by this project.
SET(vtkgdcm_LIBS
  vtkCommon
  vtkIO
  vtkImaging
  vtkRendering
)

# Use wrapping hints for this project.
#SET(VTK_WRAP_HINTS "${PROJECT_SOURCE_DIR}/hints")

SET(VTKGDCM_NAME vtkgdcm CACHE STRING "vtk-gdcm lib name")
MARK_AS_ADVANCED(VTKGDCM_NAME)

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
    "${VTKGDCM_NAME}Instantiator"
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
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkImageRGBToYBR.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkGDCMPolyDataReader.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkLookupTable16.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkImageMapToColors16.cxx
    #${CMAKE_CURRENT_SOURCE_DIR}/vtkImagePlanarComponentsToComponents.cxx
  )
  #IF(CMAKE_HAVE_PTHREAD_H)
    SET(vtkgdcm_SRCS ${vtkgdcm_SRCS}
    vtkGDCMThreadedImageReader2.cxx
    )
  #ENDIF(CMAKE_HAVE_PTHREAD_H)

  SET(VTK_USE_INSTANTIATOR_NEW 1)
  VTK_MAKE_INSTANTIATOR3(
    "${VTKGDCM_NAME}Instantiator"
    vtkgdcmInstantiator_SRCS
    "${vtkgdcm_SRCS}"
    "" #"VTK_${VTKGDCM_NAME}_EXPORT"
    ${PROJECT_BINARY_DIR}
    "" #"${VTKGDCM_NAME}Configure.h"
  )
ENDIF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )

#Hum... not sure why this is needed.
#IF(NOT VTK_BUILD_SHARED_LIBS AND GDCM_BUILD_SHARED_LIBS)
#  ADD_LIBRARY(vtkgdcm STATIC ${vtkgdcm_SRCS} ${vtkgdcmInstantiator_SRCS})
#ELSE(NOT VTK_BUILD_SHARED_LIBS AND GDCM_BUILD_SHARED_LIBS)
  ADD_LIBRARY(${VTKGDCM_NAME} ${vtkgdcm_SRCS} ${vtkgdcmInstantiator_SRCS})
#ENDIF(NOT VTK_BUILD_SHARED_LIBS AND GDCM_BUILD_SHARED_LIBS)

SET_TARGET_PROPERTIES(${VTKGDCM_NAME} PROPERTIES ${GDCM_LIBRARY_PROPERTIES})
TARGET_LINK_LIBRARIES(${VTKGDCM_NAME} gdcmMSFF ${vtkgdcm_LIBS})
# this need to be set on the vtkIO lib directly
#  SET_PROPERTY(TARGET ${VTKGDCM_NAME} PROPERTY LINK_INTERFACE_LIBRARIES "")
IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS ${VTKGDCM_NAME}
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime ${NAMELINK_SKIP}
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
  )
  #INSTALL(TARGETS vtkgdcm
  #  LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development ${NAMELINK_ONLY}
  #)
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

IF(GDCM_WRAP_JAVA)
  IF(VTK_WRAP_JAVA)
    ADD_EXECUTABLE(vtkgdcmrepackage repackage.cxx)
    GET_TARGET_PROPERTY( VTKGDCMREPACKAGE
      vtkgdcmrepackage
      LOCATION
    )
    SET(VTK_WRAP_JAVA3_INIT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
    # Lars Matthäus patch (package vtkgdcm;)
    SET(VTK_JAVA_HOME ${CMAKE_CURRENT_BINARY_DIR}/java/${PROJECT_NAME})
    MAKE_DIRECTORY(${VTK_JAVA_HOME})
    INCLUDE(${VTK_CMAKE_DIR}/vtkWrapJava.cmake)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

    VTK_WRAP_JAVA3(${VTKGDCM_NAME}Java vtkgdcmJAVA_SRCS "${vtkgdcm_SRCS}")
    ADD_LIBRARY(${VTKGDCM_NAME}Java SHARED ${vtkgdcmJAVA_SRCS})
    TARGET_LINK_LIBRARIES(${VTKGDCM_NAME}Java ${VTKGDCM_NAME})
    FOREACH(c ${vtkgdcm_LIBS})
      TARGET_LINK_LIBRARIES(${VTKGDCM_NAME}Java ${c}Java)
    ENDFOREACH(c)

    ADD_CUSTOM_COMMAND(
      OUTPUT ${LIBRARY_OUTPUT_PATH}/vtkgdcm.jar
      COMMAND ${VTKGDCMREPACKAGE} ARGS "${PROJECT_NAME}/*.java"
      COMMAND ${JAVA_COMPILE} ARGS -cp ${VTK_JAVA_JAR} "${PROJECT_NAME}/*.java"
      COMMAND ${JAVA_ARCHIVE} ARGS cvf ${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.jar ${PROJECT_NAME}/*.class
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/java
      DEPENDS ${VTKGDCM_NAME}Java vtkgdcmrepackage
      COMMENT   "*.java -> jar"
    )
    ADD_CUSTOM_TARGET(VTKGDCMJavaJar ALL
      DEPENDS ${LIBRARY_OUTPUT_PATH}/vtkgdcm.jar
      COMMENT "building vtkgdcm.jar"
    )

    IF(NOT GDCM_INSTALL_NO_LIBRARIES)
        INSTALL(TARGETS ${VTKGDCM_NAME}Java
          RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
          LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime ${NAMELINK_SKIP}
          ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
        )
    ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)

  ELSE(VTK_WRAP_JAVA)
    MESSAGE("GDCM_WRAP_JAVA canot be build without VTK_WRAP_JAVA")
  ENDIF(VTK_WRAP_JAVA)

ENDIF(GDCM_WRAP_JAVA)

IF(GDCM_WRAP_PYTHON)
  IF(VTK_WRAP_PYTHON)
      SET(DEXTENSION "")
    IF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
        VTK_WRAP_PYTHON2(${VTKGDCM_NAME}Python vtkgdcmPYTHON_SRCS ${vtkgdcm_SRCS})
    ELSE( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    INCLUDE(${VTK_CMAKE_DIR}/vtkWrapPython.cmake)
        INCLUDE_DIRECTORIES(
          ${CMAKE_CURRENT_SOURCE_DIR}
        )
        VTK_WRAP_PYTHON3(${VTKGDCM_NAME}Python vtkgdcmPYTHON_SRCS "${vtkgdcm_SRCS}")
      SET(DEXTENSION "D")
    ENDIF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    ADD_LIBRARY(${VTKGDCM_NAME}PythonD ${vtkgdcmPYTHON_SRCS})
    # this is a library set the version:
    SET_TARGET_PROPERTIES(${VTKGDCM_NAME}PythonD PROPERTIES ${GDCM_LIBRARY_PROPERTIES})
    ADD_LIBRARY(${VTKGDCM_NAME}Python MODULE ${VTKGDCM_NAME}PythonInit.cxx)
    # do not set the version on the Python module:
    #SET_TARGET_PROPERTIES(${VTKGDCM_NAME}Python PROPERTIES ${GDCM_LIBRARY_PROPERTIES})
    TARGET_LINK_LIBRARIES(${VTKGDCM_NAME}PythonD ${VTKGDCM_NAME})
    FOREACH(c ${vtkgdcm_LIBS})
      TARGET_LINK_LIBRARIES(${VTKGDCM_NAME}PythonD ${c}Python${DEXTENSION})
    ENDFOREACH(c)
    TARGET_LINK_LIBRARIES(${VTKGDCM_NAME}Python ${VTKGDCM_NAME}PythonD)
    # Python extension modules on Windows must have the extension ".pyd"
    # instead of ".dll" as of Python 2.5.  Older python versions do support
    # this suffix.
    IF(WIN32 AND NOT CYGWIN)
      SET_TARGET_PROPERTIES(${VTKGDCM_NAME}Python PROPERTIES SUFFIX ".pyd")
    ENDIF(WIN32 AND NOT CYGWIN)

    ADD_CUSTOM_COMMAND(
      TARGET    ${VTKGDCM_NAME}Python
      POST_BUILD
      COMMAND   ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm.py ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}
      DEPENDS   "${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm.py"
      COMMENT   "Copy vtkgdcm.py into ${LIBRARY_OUTPUT_PATH}"
    )
    IF(NOT GDCM_INSTALL_NO_LIBRARIES)
        INSTALL(TARGETS ${VTKGDCM_NAME}Python
          RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
          LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR}/${python_site_package} COMPONENT Runtime ${NAMELINK_SKIP}
          ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR}/${python_site_package} COMPONENT Development
        )
        INSTALL(TARGETS ${VTKGDCM_NAME}PythonD
          RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
          LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime ${NAMELINK_SKIP}
          ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
        )
#        INSTALL(TARGETS ${VTKGDCM_NAME}PythonD ${VTKGDCM_NAME}Python
#          LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR}/${python_site_package} COMPONENT Development ${NAMELINK_ONLY}
#  )
    # the python file is not a dev file, but part of the gdcm module...
      INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm.py 
        DESTINATION ${GDCM_INSTALL_LIB_DIR}/${python_site_package} COMPONENT Runtime
      )
    ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)

  ELSE(VTK_WRAP_PYTHON)
    MESSAGE("GDCM_WRAP_PYTHON canot be build without VTK_WRAP_PYTHON")
  ENDIF(VTK_WRAP_PYTHON)
ENDIF(GDCM_WRAP_PYTHON)

IF(BUILD_TESTING)
  SUBDIRS(Testing)
ENDIF(BUILD_TESTING)

IF(BUILD_APPLICATIONS)
  SUBDIRS(Applications)
ENDIF(BUILD_APPLICATIONS)

IF(BUILD_EXAMPLES)
  SUBDIRS(Examples)
ENDIF(BUILD_EXAMPLES)

