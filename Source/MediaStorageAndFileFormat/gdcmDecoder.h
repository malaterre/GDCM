/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
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

class TransferSyntax;
class DataElement;
/** 
 * \brief Decoder
 */
class GDCM_EXPORT Decoder
{
public:
  virtual ~Decoder() {}

  /// Return whether this decoder support this transfer syntax (can decode it)
  virtual bool CanDecode(TransferSyntax const &) const = 0;

  /// Decode 
  virtual bool Decode(DataElement const &is, DataElement &os) { (void)is;(void)os;return false; }
protected:
  virtual bool Decode(std::istream &is, std::ostream &os) { (void)is; (void)os;return false; }
};

} // end namespace gdcm

#endif //__gdcmDecoder_h
