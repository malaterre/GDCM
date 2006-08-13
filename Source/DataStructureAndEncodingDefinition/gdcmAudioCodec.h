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
#ifndef __gdcmAudioCodec_h
#define __gdcmAudioCodec_h

#include "gdcmCodec.h"

namespace gdcm
{
  
class AudioCodec : public Codec
{
public:
  AudioCodec();
  ~AudioCodec();
  bool CanDecode(TS const &) { return false; }
  bool Decode(IStream &is, OStream &os);

private:
};

} // end namespace gdcm

#endif //__gdcmAudioCodec_h
