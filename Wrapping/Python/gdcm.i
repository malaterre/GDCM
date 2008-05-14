/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
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

%module(directors="1",docstring="A DICOM library") gdcm
#pragma SWIG nowarn=504,510
%{
#include "gdcmTypes.h"
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
#include "gdcmFragment.h"
#include "gdcmCSAHeader.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmTransferSyntax.h"
#include "gdcmBasicOffsetTable.h"
//#include "gdcmLO.h"
#include "gdcmCSAElement.h"
#include "gdcmFileSet.h"

#include "gdcmReader.h"
#include "gdcmImageReader.h"
#include "gdcmWriter.h"
#include "gdcmImageWriter.h"
#include "gdcmStringFilter.h"
#include "gdcmGlobal.h"
#include "gdcmDicts.h"
#include "gdcmDict.h"
#include "gdcmDictEntry.h"
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
#include "gdcmTableEntry.h"
#include "gdcmDefinedTerms.h"
#include "gdcmSeries.h"
#include "gdcmModuleEntry.h"
#include "gdcmRescaler.h"
#include "gdcmSegmentedPaletteColorLookupTable.h"
#include "gdcmUnpacker12Bits.h"

using namespace gdcm;
%}

// swig need to know what are uint16_t, uint8_t...
%include "stdint.i"
//%include "typemaps.i"

// gdcm does not use std::string in its interface, but we do need it for the 
// %extend (see below)
%include "std_string.i"
%include "std_set.i"
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
//%rename(__getattr__) gdcm::Tag::operator[];
%include "gdcmTag.h"
%extend gdcm::Tag
{
  const char *__str__() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%include "gdcmPrivateTag.h"
%include "gdcmVL.h"
//%typemap(out) int
//{
//    $result = SWIG_NewPointerObj($1,SWIGTYPE_p_gdcm__VL,0);
//}
%include "gdcmVR.h"
%extend gdcm::VR
{
  const char *__str__() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%include "gdcmVM.h"
//%template (FilenameType) std::string;
%template (FilenamesType) std::vector<std::string>;
%include "gdcmDirectory.h"
%extend gdcm::Directory
{
  const char *__str__() {
    static std::string buffer;
    std::stringstream s;
    self->Print(s);
    buffer = s.str();
    return buffer.c_str();
  }
};
%include "gdcmTesting.h"
%include "gdcmObject.h"
%include "gdcmValue.h"
%extend gdcm::Value
{
  const char *__str__() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%include "gdcmByteValue.h"
%extend gdcm::ByteValue
{
  const char *__str__() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%include "gdcmDataElement.h"
%extend gdcm::DataElement
{
  const char *__str__() {
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
  const char *__str__() {
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
  const char *__str__() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
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
  const char *__str__() {
    static std::string buffer;
    std::stringstream s;
    self->Print(s);
    buffer = s.str();
    return buffer.c_str();
    }
};
//%include "gdcmString.h"
//%include "gdcmTransferSyntax.h"
%include "gdcmPhotometricInterpretation.h"
%include "gdcmObject.h"
%include "gdcmLookupTable.h"
%include "gdcmOverlay.h"
//%include "gdcmVR.h"
//%rename(DataElementSetPython) std::set<DataElement, lttag>;
//%rename(DataElementSetPython2) DataSet::DataElementSet;
%template (DataElementSet) std::set<gdcm::DataElement>;
//%rename (SetString2) gdcm::DataElementSet;
%include "gdcmPreamble.h"
%include "gdcmFileMetaInformation.h"
%extend gdcm::FileMetaInformation
{
  const char *__str__() {
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
  const char *__str__() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
//%newobject gdcm::Image::GetBuffer;
%include "cstring.i"
%include "gdcmImage.h"
%ignore gdcm::Image::GetBuffer(char*) const;
%extend gdcm::Image
{
  %cstring_output_allocate_size(char **buffer, unsigned int *size, free(*$1) );
  void GetBuffer(char **buffer, unsigned int *size) {
    *size = self->GetBufferLength();
    *buffer = (char*)malloc(*size);
    self->GetBuffer(*buffer);
  }

  const char *__str__() {
    static std::string buffer;
    std::stringstream s;
    self->Print(s);
    buffer = s.str();
    return buffer.c_str();
  }
//%typemap(python,out) const double * GetOrigin2 {
//	//float* source=(float*)$source;
//	float source[3]={0,0,0};
//	$target = PyTuple_New(3);
//	for(int i=0;i<3;i++){
//		PyTuple_SetItem($target,i,Py_BuildValue("f",(source[i])));
//	}	
//}

};
%include "gdcmFragment.h"
%include "gdcmCSAHeader.h"
%include "gdcmSequenceOfFragments.h"
%include "gdcmTransferSyntax.h"
%include "gdcmBasicOffsetTable.h"
//%include "gdcmLO.h"
%include "gdcmCSAElement.h"
%include "gdcmFileSet.h"

%include "gdcmGlobal.h"

%include "gdcmDictEntry.h"
%extend gdcm::DictEntry
{
  const char *__str__() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%include "gdcmDict.h"
%include "gdcmDicts.h"
%include "gdcmReader.h"
%include "gdcmImageReader.h"
%include "gdcmWriter.h"
%include "gdcmImageWriter.h"
%template (PairString) std::pair<std::string,std::string>;
//%template (MyM) std::map<gdcm::Tag,gdcm::ConstCharWrapper>;
%include "gdcmStringFilter.h"
%include "gdcmUIDGenerator.h"
//%include "gdcmConstCharWrapper.h"
//%{
//  typedef char * PString;   // copied to wrapper code
//%}
//%template (FilenameToValue) std::map<const char*,const char*>;
//%template (FilenameToValue) std::map<PString,PString>;
//%template (FilenameToValue) std::map<std::string,std::string>;
//%template (MappingType)     std::map<gdcm::Tag,FilenameToValue>;
//%template (StringArray)     std::vector<const char*>;
%template (ValuesType)      std::set<std::string>;
//%template (TagToValue)      std::map<gdcm::Tag,const char*>;
//%template (TagToValue)      std::map<gdcm::Tag,gdcm::ConstCharWrapper>;
%include "gdcmScanner.h"
%extend gdcm::Scanner
{
  const char *__str__() {
    static std::string buffer;
    std::stringstream s;
    self->Print(s);
    buffer = s.str();
    return buffer.c_str();
  }
};
//%template (stdFilenameToValue) std::map<const char*,const char*>;
//namespace gdcm
//{
//  class FilenameToValue : public std::map<const char*, const char*>
//  {
//    void foo();
//  };
//}
#define GDCM_STATIC_ASSERT(x)
%include "gdcmAttribute.h"
%include "gdcmAnonymizer.h"
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
%include "gdcmModule.h"
%include "gdcmModules.h"
%include "gdcmTableEntry.h"
%include "gdcmDefinedTerms.h"
%include "gdcmSeries.h"
%include "gdcmModuleEntry.h"
%include "gdcmRescaler.h"
%include "gdcmSegmentedPaletteColorLookupTable.h"
%include "gdcmUnpacker12Bits.h"


