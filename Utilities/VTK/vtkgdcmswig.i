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

//%typemap(csimports) vtkGDCMImageWriter %{
%typemap(csimports) SWIGTYPE %{
// I need to duplicate those also:
using System;
using System.Runtime.InteropServices;
// my special import:
using Kitware.VTK;
using Kitware.mummy.Runtime;
%}

//%pragma(csharp) imclassimports=%{
//using System;
//using System.Runtime.InteropServices;
//using My.Own.Namespace;
//%}

#define VTK_EXPORT

// FIXME
#define vtkGetMacro(a,b)
#define vtkSetMacro(a,b)
#define vtkBooleanMacro(a,b)


%typemap(cstype) vtkDataObject * "vtkDataObject"
%typemap(csin) vtkDataObject * "$csinput.GetCppThis()"
%typemap(csout) (vtkDataObject *) {
  vtkImageData points = null;
  uint mteStatus = 0;
  //uint maxValue = uint.MaxValue;
  uint maxValue = 1;
  uint rawRefCount = 0;
  //IntPtr rawCppThis = vtkCell_GetPoints_23(base.GetCppThis(), ref
  //  mteStatus, ref maxValue, ref rawRefCount);
  IntPtr rawCppThis = $imcall;
  if (IntPtr.Zero != rawCppThis)
    {
    bool flag;
    points = (vtkImageData) Methods.CreateWrappedObject(mteStatus,
      maxValue, rawRefCount, rawCppThis, true, out flag);
    if (flag)
      {
      points.Register(null);
      }
    }
  return points;
}

%include "vtkGDCMImageReader.h"
%include "vtkGDCMImageWriter.h"

