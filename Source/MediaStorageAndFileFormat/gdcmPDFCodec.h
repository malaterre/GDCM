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
#ifndef __gdcmPDFCodec_h
#define __gdcmPDFCodec_h

#include "gdcmCodec.h"

namespace gdcm
{
  
class GDCM_EXPORT PDFCodec : public Codec
{
public:
  PDFCodec();
  ~PDFCodec();
  bool CanDecode(TransferSyntax const &) { return false; }
  bool Decode(DataElement const &is, DataElement &os);
};

} // end namespace gdcm

#endif //__gdcmPDFCodec_h
