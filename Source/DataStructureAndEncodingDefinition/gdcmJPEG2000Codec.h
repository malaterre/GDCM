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
#ifndef __gdcmJPEG2000codec_h
#define __gdcmJPEG2000codec_h

#include "gdcmImageCodec.h"

namespace gdcm
{
  
class JPEG2000Internals;
class JPEG2000Codec : public ImageCodec
{
public:
  JPEG2000Codec();
  ~JPEG2000Codec();
  bool CanDecode(TS const &ts);
  bool Decode(IStream &is, OStream &os);
private:
  JPEG2000Internals *Internals;
};

} // end namespace gdcm

#endif //__gdcmJPEG2000codec_h
