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
#ifndef __gdcmImageCodec_h
#define __gdcmImageCodec_h

#include "gdcmCodec.h"
#include "gdcmPhotometricInterpretation.h"
#include "gdcmLookupTable.h"
#include "gdcmSmartPointer.h"
#include "gdcmPixelType.h"

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

  const PixelType &GetPixelType() const
    {
    return PT;
    }
  virtual void SetPixelType(PixelType const &pt)
    {
    PT = pt;
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

protected:
  bool RequestPlanarConfiguration;
  bool RequestPaddedCompositePixelCode;
private:
  unsigned int PlanarConfiguration;
  PhotometricInterpretation PI;
  PixelType PT;
  bool NeedByteSwap;

  typedef SmartPointer<LookupTable> LUTPtr;
  LUTPtr LUT;

  bool DoPixelType(IStream &is, OStream &os);
  bool DoByteSwap(IStream &is, OStream &os);
  bool DoYBR(IStream &is, OStream &os);
  bool DoPlanarConfiguration(IStream &is, OStream &os);
  bool DoSimpleCopy(IStream &is, OStream &os);
  bool DoPaddedCompositePixelCode(IStream &is, OStream &os);
  bool DoInvertMonochrome(IStream &is, OStream &os);
};

} // end namespace gdcm

#endif //__gdcmImageCodec_h
