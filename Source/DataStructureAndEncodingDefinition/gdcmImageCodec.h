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
#include "gdcmPhotometricInterpretation.h"
#include "gdcmLookupTable.h"

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

  const PhotometricInterpretation &GetPhotometricInterpretation() const;
  void SetPhotometricInterpretation(PhotometricInterpretation const &pi);

  bool GetNeedByteSwap() const
    {
    return NeedByteSwap;
    }
  void SetNeedByteSwap(bool b)
    {
    NeedByteSwap = b;
    }

private:
  unsigned int PlanarConfiguration;
  PhotometricInterpretation PI;
  LookupTable LUT;
  bool NeedByteSwap;
};

} // end namespace gdcm

#endif //__gdcmImagecodec_h
