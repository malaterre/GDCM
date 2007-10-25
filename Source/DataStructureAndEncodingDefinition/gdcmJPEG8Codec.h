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
#ifndef __gdcmJPEG8Codec_h
#define __gdcmJPEG8Codec_h

#include "gdcmJPEGCodec.h"

namespace gdcm
{

class JPEGInternals;
class JPEG8Codec : public JPEGCodec
{
public:
  JPEG8Codec();
  ~JPEG8Codec();

  bool Decode(IStream &is, OStream &os);

private:
  JPEGInternals *Internals;
};

} // end namespace gdcm

#endif //__gdcmJPEG8Codec_h
