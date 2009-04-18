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
// See docs:
// http://www.swig.org/Doc1.3/CSharp.html
// http://www.swig.org/Doc1.3/SWIGPlus.html
// The main difference with this wrapping is that gdcm.System is now renamed
// to gdcm.PosixEmulation. I could not figure out a way to preserve gdcm.System
// as swig by default flatten all namespace and gdcm.System would conflict
// with .NET 'System' namespace... fix welcome to get back gdcm.System
// until then gdcm.PosixEmulation will remain the recommended way to access
// gdcm.System API from C#

// Some good reference:
// https://code.crt.realtors.org/projects/librets/browser/librets/trunk/project/swig/librets.i?rev=729

/*
> I want to wrap C++ code in C#. Is there a way to instruct swig to insert
> a
> series of "using" statements for each C# source file that gets generated?


%pragma(csharp) moduleimports=%{
using System;
using System.Runtime.InteropServices;
using System.Diagnostics;
using My.Own.Namespace;
%}

%pragma(csharp) imclassimports=%{
using System;
using System.Runtime.InteropServices;
using My.Own.Namespace;
%}
*/

%module(docstring="A DICOM library") gdcm
#pragma SWIG nowarn=504,510

// There is something funky with swig 1.3.33, one cannot simply test defined(SWIGCSHARP)
// I need to redefine it myself... seems to be solved in later revision
#if defined(SWIGCSHARP)
%{
#define SWIGCSHARP
%}
#endif

%{
#include "gdcmTypes.h"
#include "gdcmSmartPointer.h"
#include "gdcmSwapCode.h"
#include "gdcmDirectory.h"
#include "gdcmTesting.h"
#include "gdcmObject.h"
#include "gdcmPixelFormat.h"
#include "gdcmMediaStorage.h"
#include "gdcmTag.h"
#include "gdcmPrivateTag.h"
#include "gdcmVL.h"
#include "gdcmVR.h"
#include "gdcmVM.h"
#include "gdcmObject.h"
#include "gdcmValue.h"
#include "gdcmByteValue.h"
#include "gdcmDataElement.h"
#include "gdcmItem.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmDataSet.h"
//#include "gdcmString.h"
#include "gdcmPreamble.h"
#include "gdcmFile.h"
#include "gdcmPixmap.h"
#include "gdcmImage.h"
#include "gdcmIconImage.h"
#include "gdcmFragment.h"
#include "gdcmCSAHeader.h"
#include "gdcmPDBHeader.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmTransferSyntax.h"
#include "gdcmBasicOffsetTable.h"
//#include "gdcmLO.h"
#include "gdcmCSAElement.h"
#include "gdcmPDBElement.h"
#include "gdcmFileSet.h"

#include "gdcmReader.h"
#include "gdcmImageReader.h"
#include "gdcmWriter.h"
#include "gdcmImageWriter.h"
#include "gdcmStringFilter.h"
#include "gdcmGlobal.h"
#include "gdcmDicts.h"
#include "gdcmDict.h"
#include "gdcmCSAHeaderDict.h"
#include "gdcmDictEntry.h"
#include "gdcmCSAHeaderDictEntry.h"
#include "gdcmUIDGenerator.h"
//#include "gdcmConstCharWrapper.h"
#include "gdcmScanner.h"
#include "gdcmAttribute.h"
#include "gdcmAnonymizer.h"
#include "gdcmSystem.h"
#include "gdcmTrace.h"
#include "gdcmUIDs.h"
#include "gdcmSorter.h"
#include "gdcmIPPSorter.h"
#include "gdcmSpectroscopy.h"
#include "gdcmPrinter.h"
#include "gdcmDumper.h"
#include "gdcmOrientation.h"
#include "gdcmFiducials.h"
#include "gdcmWaveform.h"
#include "gdcmPersonName.h"
#include "gdcmIconImage.h"
#include "gdcmCurve.h"
#include "gdcmDICOMDIR.h"
#include "gdcmValidate.h"
#include "gdcmApplicationEntity.h"
#include "gdcmDictPrinter.h"
#include "gdcmFilenameGenerator.h"
#include "gdcmVersion.h"
#include "gdcmFilename.h"
#include "gdcmEnumeratedValues.h"
#include "gdcmPatient.h"
#include "gdcmStudy.h"
#include "gdcmModule.h"
#include "gdcmModules.h"
#include "gdcmDefs.h"
#include "gdcmIOD.h"
#include "gdcmIODs.h"
#include "gdcmTableEntry.h"
#include "gdcmDefinedTerms.h"
#include "gdcmSeries.h"
#include "gdcmModuleEntry.h"
#include "gdcmNestedModuleEntries.h"
#include "gdcmIODEntry.h"
#include "gdcmRescaler.h"
#include "gdcmSegmentedPaletteColorLookupTable.h"
#include "gdcmUnpacker12Bits.h"
#include "gdcmDirectionCosines.h"
#include "gdcmTagPath.h"
#include "gdcmImageToImageFilter.h"
#include "gdcmSOPClassUIDToIOD.h"
#include "gdcmImageChangeTransferSyntax.h"
#include "gdcmImageApplyLookupTable.h"
#include "gdcmSplitMosaicFilter.h"
//#include "gdcmImageChangePhotometricInterpretation.h"
#include "gdcmImageChangePlanarConfiguration.h"
#include "gdcmImageFragmentSplitter.h"
#include "gdcmDataSetHelper.h"
#include "gdcmFileExplicitFilter.h"
#include "gdcmImageHelper.h"
#include "gdcmHAVEGE.h"
#include "gdcmAES.h"
#include "gdcmMD5.h"
#include "gdcmDummyValueGenerator.h"
//#include "gdcmX509.h"
#include "gdcmRSA.h"
#include "gdcmSHA1.h"
#include "gdcmBase64.h"
#include "gdcmSpacing.h"

using namespace gdcm;
%}

// swig need to know what are uint16_t, uint8_t...
%include "stdint.i"

// gdcm does not use std::string in its interface, but we do need it for the 
// %extend (see below)
%include "std_string.i"
//%include "std_set.i"
%include "std_vector.i"
%include "std_pair.i"
%include "std_map.i"
%include "exception.i"

// operator= is not needed in python AFAIK
%ignore operator=;                      // Ignore = everywhere.
%ignore operator++;                     // Ignore

//%feature("autodoc", "1")
//%include "gdcmTypes.h" // define GDCM_EXPORT so need to be the first one...
#define GDCM_EXPORT

// The following must be define early on as gdcmVL.h get included real early
%rename(GetValueLength) gdcm::VL::operator uint32_t;
//%csmethodmodifiers gdcm::VL::GetValueLength "private"
//%csmethodmodifiers GetValueLength "private"
//%rename(GetValue) VL::operator uint32_t ();
//  public static implicit operator int( MyType a )
//        {
//            return a.value;
//        }
%include "gdcmSwapCode.h"
%include "gdcmPixelFormat.h"
%extend gdcm::PixelFormat
{
  const char *toString() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%include "gdcmMediaStorage.h"
//%rename(this ) gdcm::Tag::operator[];
%include "gdcmTag.h"
%extend gdcm::Tag
{
  const char *toString() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%include "gdcmPrivateTag.h"
%extend gdcm::PrivateTag
{
  const char *toString() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%include "gdcmVL.h"
%extend gdcm::VL
{
  const char *toString() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
%typemap(cscode) VL
%{
  public static implicit operator uint( VL vl )
    {
    return vl.GetValueLength();
    }
%}
}
%csmethodmodifiers gdcm::VL::GetValueLength "private"

%include "gdcmVR.h"
%extend gdcm::VR
{
  const char *toString() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%include "gdcmVM.h"
%template (FilenamesType) std::vector<std::string>;
%include "gdcmDirectory.h"
%extend gdcm::Directory
{
  const char *toString() {
    static std::string buffer;
    std::stringstream s;
    self->Print(s);
    buffer = s.str();
    return buffer.c_str();
  }
};
%include "gdcmObject.h"
%include "gdcmValue.h"
%extend gdcm::Value
{
  const char *toString() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
// Array marshaling for arrays of primitives
%define %cs_marshal_array(TYPE, CSTYPE)
       %typemap(ctype)  TYPE[] "void*"
       %typemap(imtype, inattributes="[MarshalAs(UnmanagedType.LPArray)]") TYPE[] "CSTYPE[]"
       %typemap(cstype) TYPE[] "CSTYPE[]"
       %typemap(in)     TYPE[] %{ $1 = (TYPE*)$input; %}
       %typemap(csin)   TYPE[] "$csinput"
%enddef

// The following macro invocations allow you to pass arrays of primitive
// types. Arrays of other things such as System.Drawing.Point are also
// possible.
%cs_marshal_array(bool, bool)
%cs_marshal_array(char, byte)
%cs_marshal_array(short, short)
%cs_marshal_array(unsigned short, ushort)
%cs_marshal_array(int, int)
%cs_marshal_array(unsigned int, uint)
%cs_marshal_array(long, int)
%cs_marshal_array(unsigned long, uint)
%cs_marshal_array(long long, long)
%cs_marshal_array(unsigned long long, ulong)
%cs_marshal_array(float, float)
%cs_marshal_array(double, double)


// %clear commands should be unnecessary, but do it just-in-case
%clear char* buffer;
%clear unsigned char* buffer;

%apply char[] { char* buffer }
%ignore gdcm::ByteValue::WriteBuffer(std::ostream &os) const;
//%ignore gdcm::ByteValue::GetPointer() const;
//%ignore gdcm::ByteValue::GetBuffer(char *buffer, unsigned long length) const;
%include "gdcmByteValue.h"
%extend gdcm::ByteValue
{
  const char *toString() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%clear char* buffer;


%apply char[] { const char* array }

%include "gdcmSmartPointer.h"
%template(SmartPtrSQ) gdcm::SmartPointer<gdcm::SequenceOfItems>;
%template(SmartPtrFrag) gdcm::SmartPointer<gdcm::SequenceOfFragments>;
%include "gdcmDataElement.h"

%clear const char* array;
%extend gdcm::DataElement
{
  const char *toString() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
 void SetArray(unsigned char array[], unsigned int nitems) {
   $self->SetByteValue((char*)array, nitems * sizeof(unsigned char) );
 }
 void SetArray(char array[], unsigned int nitems) {
   $self->SetByteValue((char*)array, nitems * sizeof(char) );
 }
 void SetArray(unsigned short array[], unsigned int nitems) {
   $self->SetByteValue((char*)array, nitems * sizeof(unsigned short) );
 }
 void SetArray(short array[], unsigned int nitems) {
   $self->SetByteValue((char*)array, nitems * sizeof(short) );
 }
 void SetArray(float array[], unsigned int nitems) {
   $self->SetByteValue((char*)array, nitems * sizeof(float) );
 }
 void SetArray(double array[], unsigned int nitems) {
   $self->SetByteValue((char*)array, nitems * sizeof(double) );
 }
};

%include "gdcmItem.h"
%extend gdcm::Item
{
  const char *toString() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%include "gdcmSequenceOfItems.h"
%extend gdcm::SequenceOfItems
{
  const char *toString() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%rename (CSharpDataSet) SWIGDataSet; 
%include "gdcmDataSet.h"
%extend gdcm::DataSet
{
  const char *toString() {
    static std::string buffer;
    std::stringstream s;
    self->Print(s);
    buffer = s.str();
    return buffer.c_str();
    }
};

%include "gdcmPhotometricInterpretation.h"
%include "gdcmObject.h"
%include "gdcmLookupTable.h"
%include "gdcmOverlay.h"
//%include "gdcmVL.h"
//%template (DataElementSet) std::set<gdcm::DataElement>;
%include "gdcmPreamble.h"
%include "gdcmTransferSyntax.h"
%extend gdcm::TransferSyntax
{
  const char *toString() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%include "gdcmFileMetaInformation.h"
%extend gdcm::FileMetaInformation
{
  const char *toString() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%include "gdcmFile.h"
%extend gdcm::File
{
  const char *toString() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};

//%include "gdcm_arrays_csharp.i"

%apply char[] { char* buffer }
%apply unsigned int[] { unsigned int dims[3] }

//%apply byte OUTPUT[] { char* buffer } ;
//%ignore gdcm::Pixmap::GetBuffer(char*) const;
//%apply byte FIXED[] { char *buffer }
//%csmethodmodifiers gdcm::Pixmap::GetBuffer "public unsafe";
//%define %cs_marshal_array(TYPE, CSTYPE)
//       %typemap(ctype)  TYPE[] "void*"
//       %typemap(imtype, inattributes="[MarshalAs(UnmanagedType.LPArray)]") TYPE[] "CSTYPE[]"
//       %typemap(cstype) TYPE[] "CSTYPE[]"
//       %typemap(in)     TYPE[] %{ $1 = (TYPE*)$input; %}
//       %typemap(csin)   TYPE[] "$csinput"
//%enddef
//%cs_marshal_array(char, byte)
%include "gdcmPixmap.h"
%extend gdcm::Pixmap
{
  bool GetArray(unsigned char buffer[]) const {
    assert( $self->GetPixelFormat() == PixelFormat::UINT8 );
    return $self->GetBuffer((char*)buffer);
  }
  bool GetArray(char buffer[]) const {
    assert( $self->GetPixelFormat() == PixelFormat::INT8 );
    return $self->GetBuffer((char*)buffer);
  }
  bool GetArray(unsigned short buffer[]) const {
    assert( $self->GetPixelFormat() == PixelFormat::UINT16 );
    return $self->GetBuffer((char*)buffer);
  }
  bool GetArray(short buffer[]) const {
    assert( $self->GetPixelFormat() == PixelFormat::INT16 );
    return $self->GetBuffer((char*)buffer);
  }
  bool GetArray(float buffer[]) const {
    assert( $self->GetPixelFormat() == PixelFormat::FLOAT32 );
    return $self->GetBuffer((char*)buffer);
  }
  bool GetArray(double buffer[]) const {
    assert( $self->GetPixelFormat() == PixelFormat::FLOAT64 );
    return $self->GetBuffer((char*)buffer);
  }
};
%clear char* buffer;
%clear unsigned int* dims;


%include "gdcmImage.h"
%extend gdcm::Image
{
  const char *toString() {
    static std::string buffer;
    std::stringstream s;
    self->Print(s);
    buffer = s.str();
    return buffer.c_str();
  }
};
%include "gdcmIconImage.h"
%include "gdcmFragment.h"
%include "gdcmPDBElement.h"
%extend gdcm::PDBElement
{
  const char *toString() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%include "gdcmPDBHeader.h"
%extend gdcm::PDBHeader
{
  const char *toString() {
    static std::string buffer;
    std::stringstream s;
    self->Print(s);
    buffer = s.str();
    return buffer.c_str();
  }
};
%include "gdcmCSAElement.h"
%extend gdcm::CSAElement
{
  const char *toString() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%include "gdcmCSAHeader.h"
%extend gdcm::CSAHeader
{
  const char *toString() {
    static std::string buffer;
    std::stringstream s;
    self->Print(s);
    buffer = s.str();
    return buffer.c_str();
  }
};
%include "gdcmSequenceOfFragments.h"
%include "gdcmBasicOffsetTable.h"
//%include "gdcmLO.h"
%include "gdcmFileSet.h"

%include "gdcmGlobal.h"

%include "gdcmDictEntry.h"
%extend gdcm::DictEntry
{
  const char *toString() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%include "gdcmCSAHeaderDictEntry.h"
%extend gdcm::CSAHeaderDictEntry
{
  const char *toString() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};

%include "gdcmDict.h"
%include "gdcmCSAHeaderDict.h"
%include "gdcmDicts.h"
%include "gdcmReader.h"
%include "gdcmImageReader.h"
%include "gdcmWriter.h"
%include "gdcmImageWriter.h"
%template (PairString) std::pair<std::string,std::string>;
//%template (MyM) std::map<gdcm::Tag,gdcm::ConstCharWrapper>;
%include "gdcmStringFilter.h"
%include "gdcmUIDGenerator.h"
//%template (ValuesType)      std::set<std::string>;
%rename (CSharpTagToValue) SWIGTagToValue; 
%include "gdcmScanner.h"
%extend gdcm::Scanner
{
  const char *toString() {
    static std::string buffer;
    std::stringstream s;
    self->Print(s);
    buffer = s.str();
    return buffer.c_str();
  }
};
#define GDCM_STATIC_ASSERT(x)
%include "gdcmAttribute.h"
%include "gdcmAnonymizer.h"

// System is a namespace in C#, need to rename to something different
%rename (PosixEmulation) System; 
%include "gdcmSystem.h"

%include "gdcmTrace.h"
%include "gdcmUIDs.h"
//%feature("director") gdcm::IPPSorter;      

////////////////////////////////////////////////////////////////////////////
// cs_callback is used to marshall callbacks. It allows a C# function to
// be passed to C++ as a function pointer through P/Invoke, which has the
// ability to make unmanaged-to-managed thunks. It does NOT allow you to
// pass C++ function pointers to C#.
//
// I would have liked to support FastDelegate<...> as the C++ argument
// type; this would have involved the cs_callback2 macro... but it turns
// out not to work under default project settings because .NET functions
// use the __stdcall calling convention, but FastDelegate uses the default
// convention which tends to be something else (__fastcall?). So nevermind.
//
// Anyway, to use this macro you need to declare the function pointer type
// TYPE in the appropriate header file (including the calling convention),
// declare a delegate named after CSTYPE in your C# project, and use this
// macro in your .i file. Here is an example:
//
// in C++ header file (%include this header in your .i file):
// typedef void (__stdcall *Callback)(PCWSTR);
// void Foo(Callback c);
//
// in C# code:
// public delegate void CppCallback([MarshalAs(UnmanagedType.LPWStr)] string message);
//
// in your .i file:
// %cs_callback(Callback, CppCallback)
//
// Remember to invoke %cs_callback before any code involving Callback.
%define %cs_callback(TYPE, CSTYPE)
       %typemap(ctype) TYPE, TYPE& "void*"
       %typemap(in) TYPE  %{ $1 = (TYPE)$input; %}
       %typemap(in) TYPE& %{ $1 = (TYPE*)&$input; %}
       %typemap(imtype, out="IntPtr") TYPE, TYPE& "CSTYPE"
       %typemap(cstype, out="IntPtr") TYPE, TYPE& "CSTYPE"
       %typemap(csin) TYPE, TYPE& "$csinput"
%enddef
%define %cs_callback2(TYPE, CTYPE, CSTYPE)
       %typemap(ctype) TYPE "CTYPE"
       %typemap(in) TYPE %{ $1 = (TYPE)$input; %}
       %typemap(imtype, out="IntPtr") TYPE "CSTYPE"
       %typemap(cstype, out="IntPtr") TYPE "CSTYPE"
       %typemap(csin) TYPE "$csinput"
%enddef

%cs_callback(Sorter::SortFunction, Sorter::CppSortFunction)

%include "gdcmSorter.h"
%include "gdcmIPPSorter.h"
%include "gdcmSpectroscopy.h"
%include "gdcmPrinter.h"
%include "gdcmDumper.h"
%include "gdcmOrientation.h"
%include "gdcmDirectionCosines.h"
%include "gdcmFiducials.h"
%include "gdcmWaveform.h"
%include "gdcmPersonName.h"
%include "gdcmIconImage.h"
%include "gdcmCurve.h"
%include "gdcmDICOMDIR.h"
%include "gdcmValidate.h"
%include "gdcmApplicationEntity.h"
%include "gdcmDictPrinter.h"
%include "gdcmFilenameGenerator.h"
%include "gdcmVersion.h"
%include "gdcmFilename.h"
%include "gdcmEnumeratedValues.h"
%include "gdcmPatient.h"
%include "gdcmStudy.h"
%include "gdcmModuleEntry.h"
%extend gdcm::ModuleEntry
{
  const char *toString() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%include "gdcmNestedModuleEntries.h"
%include "gdcmModule.h"
%include "gdcmModules.h"
%include "gdcmDefs.h"
%include "gdcmIOD.h"
%include "gdcmIODs.h"
%include "gdcmTableEntry.h"
%include "gdcmDefinedTerms.h"
%include "gdcmSeries.h"
%include "gdcmIODEntry.h"
%include "gdcmRescaler.h"
%include "gdcmSegmentedPaletteColorLookupTable.h"
%include "gdcmUnpacker12Bits.h"

%include "gdcmConfigure.h"
#ifdef GDCM_BUILD_TESTING
%include "gdcmTesting.h"
%ignore gdcm::Testing::ComputeMD5(const char *, const unsigned long , char []);
%ignore gdcm::Testing::ComputeFileMD5(const char*, char []);
%extend gdcm::Testing
{
  static const char *ComputeFileMD5(const char *filename) {
    static char buffer[33];
    gdcm::Testing::ComputeFileMD5(filename, buffer);
    return buffer;
  }
};
#endif
%include "gdcmTagPath.h"
%include "gdcmImageToImageFilter.h"
%include "gdcmSOPClassUIDToIOD.h"
%include "gdcmImageChangeTransferSyntax.h"
%include "gdcmImageApplyLookupTable.h"
%include "gdcmSplitMosaicFilter.h"
//%include "gdcmImageChangePhotometricInterpretation.h"
%include "gdcmImageChangePlanarConfiguration.h"
%include "gdcmImageFragmentSplitter.h"
%include "gdcmDataSetHelper.h"
%include "gdcmFileExplicitFilter.h"
%template (DoubleType) std::vector<double>;
%include "gdcmImageHelper.h"
%include "gdcmHAVEGE.h"
%include "gdcmAES.h"
%include "gdcmMD5.h"
%include "gdcmDummyValueGenerator.h"
//%include "gdcmX509.h"
%include "gdcmRSA.h"
%include "gdcmSHA1.h"
%include "gdcmBase64.h"
%include "gdcmSpacing.h"

