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
// http://www.geocities.com/foetsch/python/extending_python.htm

%module gdcm
#pragma SWIG nowarn=504,510
%{
#include "gdcmTypes.h"
#include "gdcmSwapCode.h"
#include "gdcmTag.h"
#include "gdcmVL.h"
#include "gdcmVR.h"
#include "gdcmDataElement.h"
#include "gdcmDataSet.h"
#include "gdcmPreamble.h"
#include "gdcmFile.h"
#include "gdcmReader.h"
#include "gdcmImageReader.h"
#include "gdcmStringFilter.h"

using namespace gdcm;
%}

// swig need to know what are uint16_t, uint8_t...
%include "inttypes.i"

// gdcm does not use std::string in its interface, but we do need it for the 
// %extend (see below)
%include "std_string.i"
%include "std_set.i"

%include "gdcmWin32.h" // define GDCM_EXPORT so need to be the first one...
%include "gdcmSwapCode.h"
%include "gdcmPixelFormat.h"
//%include "gdcmMediaStorage.h"
%include "gdcmTag.h"
//%include "gdcmTransferSyntax.h"
%include "gdcmPhotometricInterpretation.h"
%include "gdcmLookupTable.h"
%include "gdcmOverlay.h"
%include "gdcmVL.h"
//%include "gdcmVR.h"
%include "gdcmValue.h"
%include "gdcmByteValue.h"
%include "gdcmDataElement.h"
%include "gdcmDataSet.h"
namespace std {
  //struct lttag
  //  {
  //  bool operator()(const gdcm::DataElement &s1,
  //    const gdcm::DataElement &s2) const
  //    {
  //    return s1.GetTag() < s2.GetTag();
  //    }
  //  };

  //%template(DataElementSet) gdcm::DataSet::DataElementSet;
  %template(DataElementSet) set<DataElement, lttag>;
}
%extend gdcm::DataSet
{
  const DataElementSet & GetSet() const
    {
    return self->GetDES();
    }
  std::string Print() const
    {
    std::stringstream s;
    self->Print(s);
    return s.str();
    }
};
%include "gdcmPreamble.h"
%include "gdcmFileMetaInformation.h"
%include "gdcmFile.h"
%include "gdcmImage.h"
%extend gdcm::Image
{
  std::string Print() const
    {
    std::stringstream s;
    self->Print(s);
    return s.str();
    }
};
%include "gdcmReader.h"
%include "gdcmImageReader.h"
%include "gdcmStringFilter.h"

//#error TODO: gdcm::ByteValueToStringFilter

