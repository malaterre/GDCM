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
#include "gdcmSmartPointer.h"

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
  void SetLUT(LookupTable const &lut)
    {
    LUT = SmartPointer<LookupTable>( const_cast<LookupTable*>(&lut) );
    }
  const LookupTable &GetLUT() const
    {
    return *LUT;
    }
  void SetRequestPaddedCompositePixelCode(bool b) {
    RequestPaddedCompositePixelCode = b;
  }


protected:
  void SetRequestPlanarConfiguration(bool b) {
    RequestPlanarConfiguration = b;
  }
private:
  unsigned int PlanarConfiguration;
  bool RequestPlanarConfiguration;
  bool RequestPaddedCompositePixelCode;
  PhotometricInterpretation PI;
  bool NeedByteSwap;

  typedef SmartPointer<LookupTable> LUTPtr;
  LUTPtr LUT;

  bool DoByteSwap(IStream &is, OStream &os);
  bool DoYBR(IStream &is, OStream &os);
  bool DoPlanarConfiguration(IStream &is, OStream &os);
  bool DoSimpleCopy(IStream &is, OStream &os);
  bool DoPaddedCompositePixelCode(IStream &is, OStream &os);
};

} // end namespace gdcm

#endif //__gdcmImagecodec_h
