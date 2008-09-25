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
#ifndef __gdcmRAWCodec_h
#define __gdcmRAWCodec_h

#include "gdcmImageCodec.h"

namespace gdcm
{
  
class RAWInternals;
/**
 * \brief RAWCodec class
 */
class RAWCodec : public ImageCodec
{
public:
  RAWCodec();
  ~RAWCodec();
  bool CanCode(TransferSyntax const &ts) const;
  bool CanDecode(TransferSyntax const &ts) const;
  bool Decode(DataElement const &is, DataElement &os);
  bool Code(DataElement const &in, DataElement &out);
protected:
  bool Decode(std::istream &is, std::ostream &os);

private:
  RAWInternals *Internals;
};

} // end namespace gdcm

#endif //__gdcmRAWcodec_h
