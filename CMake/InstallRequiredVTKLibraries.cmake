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
endforeach()

if(CMAKE_INSTALL_VTK_RUNTIME_LIBS)
  if(NOT CMAKE_INSTALL_VTK_RUNTIME_LIBS_SKIP)
    if(NOT CMAKE_INSTALL_VTK_RUNTIME_DESTINATION)
      if(WIN32)
        set(CMAKE_INSTALL_VTK_RUNTIME_DESTINATION bin)
      else()
        set(CMAKE_INSTALL_VTK_RUNTIME_DESTINATION lib)
      endif()
    endif()
    install(PROGRAMS ${CMAKE_INSTALL_VTK_RUNTIME_LIBS}
      DESTINATION ${CMAKE_INSTALL_VTK_RUNTIME_DESTINATION}
      COMPONENT VTKLibraries
    )
  endif()
endif()
