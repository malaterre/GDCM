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
%module(docstring="A VTK/GDCM binding") vtkgdcmswig
#pragma SWIG nowarn=504,510

%pragma(csharp) moduleimports=%{
using Kitware.VTK;
%}

#if defined(SWIGCSHARP)
%{
#define SWIGCSHARP
%}
#endif

%{
#include "vtkGDCMImageReader.h"
#include "vtkGDCMImageWriter.h"
%}

//%wrapper %{
//toto
//%}

//%inline %{
//using Kitware.VTK;
//%}

%typemap(csimports) SWIGTYPE %{
// I need to duplicate those also:
using System;
using System.Runtime.InteropServices;
// my special import:
using Kitware.VTK;
%}

#define VTK_EXPORT

// FIXME
#define vtkGetMacro(a,b)
#define vtkSetMacro(a,b)
#define vtkBooleanMacro(a,b)


%include "vtkGDCMImageReader.h"

%typemap(cstype) vtkDataObject * "vtkDataObject"
%typemap(csin) vtkDataObject * "$csinput.GetCppThis()"

%include "vtkGDCMImageWriter.h"

