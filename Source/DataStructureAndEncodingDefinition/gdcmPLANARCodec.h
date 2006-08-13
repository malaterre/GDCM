/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmPLANARcodec_h
#define __gdcmPLANARcodec_h

#include "gdcmCodec.h"

namespace gdcm
{
  
class PLANARInternals;
class PLANARCodec : public ImageCodec
{
public:
  PLANARCodec();
  ~PLANARCodec();
  bool CanDecode(TS const &ts);
  bool Decode(IStream &is, OStream &os);

private:
  PLANARInternals *Internals;
};

} // end namespace gdcm

#endif //__gdcmPLANARcodec_h
