PROJECT(WXGDCM)
# wxWidgets stuff changed a lot within the 2.4.2 to 2.4.3
# I wonder if this has something to do with adding features on a stable branch?
CMAKE_MINIMUM_REQUIRED(VERSION 2.4.2)

#-----------------------------------------------------------------------------
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

IF(WIN32)
  SET(GUI_EXECUTABLE WIN32)
ELSE(WIN32)
  IF(APPLE)
    SET(GUI_EXECUTABLE MACOSX_BUNDLE)
    IF(VTK_USE_COCOA)
      SET_SOURCE_FILES_PROPERTIES(
        wxVTKRenderWindowInteractor.cxx
        PROPERTIES COMPILE_FLAGS "-ObjC++")
    ENDIF(VTK_USE_COCOA)
  ELSE(APPLE)
    # Ok X11 for sure, but just check:
    IF(NOT VTK_USE_X)
      MESSAGE(FATAL_ERROR "You need to have VTK_USE_X")
    ENDIF(NOT VTK_USE_X)
    # See also:
    # FindGTK.cmake update
    # http://www.cmake.org/Bug/bug.php?op=show&bugid=3582
    FIND_PACKAGE(GTK REQUIRED)
    INCLUDE_DIRECTORIES(${GTK_INCLUDE_DIR} )
    SET(WXWINDOWS_USE_GL 1) # CMake 2.4.2
    # important on GNU/Linux since we need wxGLCanvas
    # adv is for wxGrid::CreateGrid
    SET(wxWidgets_USE_LIBS adv gl) # CMake 2.4.3 and up
  ENDIF(APPLE)
ENDIF(WIN32)

# wxWidgets is required to build the project
FIND_PACKAGE(wxWidgets REQUIRED)
# Blocker to do the right thing depending of CMake version
IF("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" EQUAL 2.4)
  IF(${CMAKE_CACHE_RELEASE_VERSION} STREQUAL "patch 2")
    INCLUDE(UsewxWidgets) # CMake 2.4.2
  ELSE(${CMAKE_CACHE_RELEASE_VERSION} STREQUAL "patch 2")
    INCLUDE( ${wxWidgets_USE_FILE} )
  ENDIF(${CMAKE_CACHE_RELEASE_VERSION} STREQUAL "patch 2")
ENDIF("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" EQUAL 2.4)

INCLUDE_DIRECTORIES(${GDCM_SOURCE_DIR}/Utilities/VTK)

ADD_EXECUTABLE(wxGDCM main.cpp wxGDCMFrame.cpp wxGDCMFrameBase.cpp wxVTKRenderWindowInteractor.cxx)
TARGET_LINK_LIBRARIES(wxGDCM vtkRendering ${wxWidgets_LIBRARIES} vtkgdcm)
INSTALL(TARGETS wxGDCM
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
	)
