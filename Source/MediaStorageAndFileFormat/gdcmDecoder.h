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

#ifndef __gdcmDecoder_h
#define __gdcmDecoder_h

#include "gdcmTypes.h"
#include "gdcmDataElement.h" // FIXME

namespace gdcm
{

/** \class Coder
 */
class TransferSyntax;
class DataElement;
class GDCM_EXPORT Decoder
{
public:
  virtual ~Decoder() {}
  virtual bool CanDecode(TransferSyntax const &) { return false; }
  virtual bool Decode(DataElement const &is, DataElement &os) { (void)is;(void)os;return false; }
protected:
  virtual bool Decode(std::istream &is, std::ostream &os) { (void)is; (void)os;return false; }
};

} // end namespace gdcm

#endif //__gdcmDecoder_h
