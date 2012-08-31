# - Install VTK required libs for GDCM
#
#  Copyright (c) 2006-2011 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

set(vtklist
  vtkCommon
  vtkFiltering
  vtkGraphics
  vtkHybrid
  vtkIO
  vtkImaging
  vtkRendering
  vtkWidgets
# utilities
  vtkDICOMParser
  vtkNetCDF
  vtkNetCDF_cxx
  vtkexoIIc
  vtkexpat
  vtkfreetype
  vtkftgl
  vtkjpeg
  vtkmetaio
  vtkpng
  vtksys
  vtktiff
  vtkverdict
  vtkzlib
)

foreach(el ${vtklist})
  list(APPEND CMAKE_INSTALL_VTK_RUNTIME_LIBS ${VTK_DIR}/bin/${el}.dll)
endforeach(el)

IF(CMAKE_INSTALL_VTK_RUNTIME_LIBS)
  IF(NOT CMAKE_INSTALL_VTK_RUNTIME_LIBS_SKIP)
    IF(NOT CMAKE_INSTALL_VTK_RUNTIME_DESTINATION)
      IF(WIN32)
        SET(CMAKE_INSTALL_VTK_RUNTIME_DESTINATION bin)
      ELSE(WIN32)
        SET(CMAKE_INSTALL_VTK_RUNTIME_DESTINATION lib)
      ENDIF(WIN32)
    ENDIF(NOT CMAKE_INSTALL_VTK_RUNTIME_DESTINATION)
    INSTALL(PROGRAMS ${CMAKE_INSTALL_VTK_RUNTIME_LIBS}
      DESTINATION ${CMAKE_INSTALL_VTK_RUNTIME_DESTINATION}
      COMPONENT VTKLibraries
    )
  ENDIF(NOT CMAKE_INSTALL_VTK_RUNTIME_LIBS_SKIP)
ENDIF(CMAKE_INSTALL_VTK_RUNTIME_LIBS)
