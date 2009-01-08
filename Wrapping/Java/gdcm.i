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
// http://www.swig.org/Doc1.3/Python.html
// http://www.swig.org/Doc1.3/SWIGPlus.html#SWIGPlus
// http://www.geocities.com/foetsch/python/extending_python.htm

%module(docstring="A DICOM library") gdcm
#pragma SWIG nowarn=504,510
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

// operator= is not needed in python AFAIK
%ignore operator=;                      // Ignore = everywhere.
%ignore operator++;                     // Ignore

//%feature("autodoc", "1")
//%include "gdcmTypes.h" // define GDCM_EXPORT so need to be the first one...
#define GDCM_EXPORT
%include "gdcmSwapCode.h"
%include "gdcmPixelFormat.h"
%include "gdcmMediaStorage.h"
%rename(__getitem__) gdcm::Tag::operator[];
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
//namespace std {
//  //struct lttag
//  //  {
//  //  bool operator()(const gdcm::DataElement &s1,
//  //    const gdcm::DataElement &s2) const
//  //    {
//  //    return s1.GetTag() < s2.GetTag();
//  //    }
//  //  };
//
//  //%template(DataElementSet) gdcm::DataSet::DataElementSet;
//  %template(DataElementSet) set<DataElement, lttag>;
//}
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
//%rename(DataElementSetPython) std::set<DataElement, lttag>;
//%rename(DataElementSetPython2) DataSet::DataElementSet;
//%template (DataElementSet) std::set<gdcm::DataElement>;
//%rename (SetString2) gdcm::DataElementSet;
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
//%extend gdcm::Pixmap
//{
//  bool GetBuffer(byte[] buffer) {
//    self->GetBuffer(buffer);
//  }
//};
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
%ignore gdcm::Testing::ComputeFileMD5(const char*, char *);
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
