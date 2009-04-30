/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
%module(docstring="A VTK/GDCM binding") vtkgdcm
#pragma SWIG nowarn=504,510
#if defined(SWIGCSHARP)
%{
#define SWIGCSHARP
%}
#endif

%{
#include "vtkGDCMImageReader.h"
#include "vtkGDCMImageWriter.h"
%}

#define VTK_EXPORT

// FIXME
#define vtkGetMacro(a,b)
#define vtkSetMacro(a,b)
#define vtkBooleanMacro(a,b)
//
%include "vtkGDCMImageReader.h"
%include "vtkGDCMImageWriter.h"

