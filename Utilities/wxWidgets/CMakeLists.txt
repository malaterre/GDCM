PROJECT(WXGDCM)

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
    FIND_PACKAGE(GTK REQUIRED)
    INCLUDE_DIRECTORIES(${GTK_INCLUDE_DIR} )
    SET(WXWINDOWS_USE_GL 1)
  ENDIF(APPLE)
ENDIF(WIN32)

# wxWidgets is required to build the project
FIND_PACKAGE(wxWidgets REQUIRED)
INCLUDE(UsewxWidgets)


ADD_EXECUTABLE(exe main.cpp MyFrame.cpp wxVTKRenderWindowInteractor.cxx)
TARGET_LINK_LIBRARIES(exe vtkRendering)
