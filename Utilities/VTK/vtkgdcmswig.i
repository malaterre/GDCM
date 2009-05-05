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

//%pragma(csharp) moduleimports=%{
//using Kitware.VTK;
//%}

#if defined(SWIGCSHARP)
%{
#define SWIGCSHARP
%}
#endif

%{
//#define VTK_MAJOR_VERSION 5
//#define VTK_MINOR_VERSION 4
//#define VTK_BUILD_VERSION 0
//#define VTK_VERSION "5.4.0"
%}


%{
// Let's reproduce the stack of include, when one would include vtkSetGet:
#include "vtkConfigure.h"
#include "vtkType.h"
#include "vtkSystemIncludes.h"
#include "vtkSetGet.h"
#include <sstream>

// Common stuff
#include "vtkObjectBase.h"
#include "vtkObject.h"

#include "vtkMatrix4x4.h"
#include "vtkMedicalImageProperties.h"

// Wrap vtkImageData
#include "vtkDataObject.h"
#include "vtkDataSet.h"
#include "vtkImageData.h"

// same for vtkGDCMImageReader / vtkGDCMImageWriter so that we get all 
// parent's member class functions properly wrapped. (Update, SetFileName ...)
#include "vtkAlgorithm.h"
#include "vtkImageAlgorithm.h"
#include "vtkImageWriter.h"
#include "vtkImageReader2.h"
#include "vtkMedicalImageReader2.h"
#include "vtkGDCMImageReader.h"
#include "vtkGDCMImageWriter.h"

#include "vtkImageExport.h"
#include "vtkImageImport.h"
%}

//%typemap(csimports) vtkGDCMImageWriter %{
//%typemap(csimports) SWIGTYPE %{
//// I need to duplicate those also:
//using System;
//using System.Runtime.InteropServices;
//// my special import:
//using Kitware.VTK;
//using Kitware.mummy.Runtime;
//%}

//%pragma(csharp) imclassimports=%{
//using System;
//using System.Runtime.InteropServices;
//using My.Own.Namespace;
//%}

#define VTK_EXPORT
#define VTK_COMMON_EXPORT
#define VTK_FILTERING_EXPORT
#define VTK_IO_EXPORT
#define VTK_IMAGING_EXPORT


// FIXME. Including #include vtkSetGet would not work on siwg 1.3.33 ...
#define vtkGetMacro(name,type) virtual type Get##name ();
#define vtkSetMacro(name,type) virtual void Set##name (type _arg);
#define vtkBooleanMacro(name,type) \
  virtual void name##On (); \
  virtual void name##Off ();
#define vtkGetVector3Macro(name,type) virtual type *Get##name ();
#define vtkGetVector6Macro(name,type) virtual type *Get##name ();
#define vtkGetObjectMacro(name,type)  virtual type *Get##name ();
#define vtkSetClampMacro(name,type,min,max) virtual void Set##name (type _arg);
#define vtkSetStringMacro(name) virtual void Set##name (const char* _arg);
#define vtkGetStringMacro(name) virtual char* Get##name ();

//%include "vtkConfigure.h"

//%ignore vtkGDCMImageReader::GetOverlay;
//%ignore vtkGDCMImageReader::GetIconImage;
//
//%ignore vtkAlgorithm::GetOutputDataObject;
//%ignore vtkAlgorithm::GetInputDataObject;
//
//%ignore vtkImageAlgorithm::GetOutput;
//%ignore vtkImageAlgorithm::GetInput;
//%ignore vtkImageAlgorithm::GetImageDataInput;

%ignore operator<<(ostream& os, vtkObjectBase& o);

%ignore vtkMatrix4x4::operator[];
%ignore vtkMatrix4x4::Determinant(vtkMatrix4x4 &);
%ignore vtkMatrix4x4::Adjoint(vtkMatrix4x4 *in, vtkMatrix4x4 *out);
%ignore vtkMatrix4x4::Invert(vtkMatrix4x4 *in, vtkMatrix4x4 *out);
%ignore vtkMatrix4x4::Transpose(vtkMatrix4x4 *in, vtkMatrix4x4 *out);

%ignore vtkImageWriter::GetInput; // I am getting a warning on swig 1.3.33 because of vtkImageAlgorithm.GetInput

// Let's wrap the following constants:
// this is only a subset of vtkSystemIncludes.h :
#define VTK_LUMINANCE       1
#define VTK_LUMINANCE_ALPHA 2
#define VTK_RGB             3
#define VTK_RGBA            4

//#include "vtkConfigure.h"
//#define VTK_USE_64BIT_IDS
//
//#ifdef VTK_USE_64BIT_IDS
//typedef long long vtkIdType;
//#else
//typedef int vtkIdType;
//#endif
//typedef vtkIdType2 vtkIdType;
//%apply vtkIdType { vtkIdType }
//#define vtkIdType vtkIdType;
//%include "vtkType.h"

//%typemap(cstype) vtkDataObject * "vtkDataObject"
//%typemap(cstype) vtkImageData * "vtkImageData"
//%typemap(csin) vtkDataObject * "$csinput.GetCppThis()"
//%typemap(csin) vtkImageData * "$csinput.GetCppThis()"
//%typemap(csout) (vtkImageData *) {
//  IntPtr rawCppThisSwig = $imcall;
//  vtkImageData data = null;
//  return data;
//}
//
//%typemap(csout) (vtkDataObject *) {
//    vtkImageData data = null;
////    uint mteStatus = 0;
////    uint maxValue = uint.MaxValue;
////    uint rawRefCount = 0;
////    IntPtr rawCppThis =
////vtkImageAlgorithm_GetOutput_06(base.GetCppThis(), ref mteStatus, ref
////maxValue, ref rawRefCount);
////    IntPtr rawCppThisSwig = $imcall;
////    if (IntPtr.Zero != rawCppThisSwig)
////    {
////        bool flag;
////        data = (vtkImageData) Methods.CreateWrappedObject(mteStatus,
////maxValue, rawRefCount, rawCppThisSwig, true, out flag);
////        if (flag)
////        {
////            data.Register(null);
////        }
////    }
//    return data;
//}
//
#define vtkGetVectorMacro(name,type,count) virtual type *Get##name ();
#define vtkNotUsed(x) x

%include "vtkObjectBase.h"
%csmethodmodifiers vtkObjectBase::ToString() "public override"
%extend vtkObjectBase
{
  const char *ToString()
    {
    static std::string buffer;
    std::ostringstream os;
    self->Print( os );
    buffer = os.str();
    return buffer.c_str();
    }
};

%include "vtkObject.h"

%include "vtkMatrix4x4.h"
%include "vtkMedicalImageProperties.h"

%include "vtkDataObject.h"
%include "vtkDataSet.h"
%include "vtkImageData.h"
%extend vtkImageData
{
%typemap(cscode) vtkImageData
%{
  public HandleRef GetCppThis()
    {
    return getCPtr(this);
    }

  public vtkImageData(HandleRef hr) : base(vtkgdcmswigPINVOKE.vtkImageDataUpcast(hr.Handle), false) {
    swigCPtr = new HandleRef(this, hr.Handle);
  }
%}
};

%include "vtkAlgorithm.h"
%include "vtkImageAlgorithm.h"
%include "vtkImageWriter.h"
%include "vtkImageReader2.h"
%include "vtkMedicalImageReader2.h"
%include "vtkGDCMImageReader.h"
%include "vtkGDCMImageWriter.h"

%include "vtkImageExport.h"
%include "vtkImageImport.h"

