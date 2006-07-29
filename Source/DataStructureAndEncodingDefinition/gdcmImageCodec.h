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
#ifndef __gdcmImagecodec_h
#define __gdcmImagecodec_h

#include "gdcmCodec.h"

namespace gdcm
{
  
class ImageCodec : public Codec
{
public:
  ImageCodec();
  ~ImageCodec();
  bool CanDecode(TS const &) { return false; }
  bool Decode(IStream &is, OStream &os);

  unsigned int GetPlanarConfiguration() const
    {
    return PlanarConfiguration;
    }
  void SetPlanarConfiguration(unsigned int pc)
    {
    PlanarConfiguration = pc;
    }

private:
  unsigned int PlanarConfiguration;
};

} // end namespace gdcm

#endif //__gdcmImagecodec_h
