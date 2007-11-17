/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmRAWcodec_h
#define __gdcmRAWcodec_h

#include "gdcmImageCodec.h"

namespace gdcm
{
  
class RAWInternals;
class RAWCodec : public ImageCodec
{
public:
  RAWCodec();
  ~RAWCodec();
  bool CanDecode(TransferSyntax const &ts);
  bool Decode(std::istream &is, std::ostream &os);

private:
  RAWInternals *Internals;
};

} // end namespace gdcm

#endif //__gdcmRAWcodec_h
