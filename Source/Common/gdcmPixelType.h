
#ifndef __gdcmPixelType_h
#define __gdcmPixelType_h

#include "gdcmTypes.h"
#include <iostream>

namespace gdcm
{

/**
 * \brief PixelType
 * \note
 * By default the Pixel Type will be instanciated with the following
 * parameters:
 * - SamplesPerPixel : 1
 * - BitsAllocated : 8
 * - BitsStored : 8
 * - HighBit : 7
 * - PixelRepresentation : 0
 */
class GDCM_EXPORT PixelType
{
public:
  typedef enum {
    INT8,
    UINT8,
    INT12,
    UINT12,
    INT16,
    UINT16,
    UNKNOWN
  } TPixelType;

  PixelType (
    unsigned short samplesperpixel = 1,
    unsigned short bitsallocated = 8,
    unsigned short bitsstored = 8,
    unsigned short highbit = 7,
    unsigned short pixelrepresentation = 0 ) :
  SamplesPerPixel(samplesperpixel),
  BitsAllocated(bitsallocated),
  BitsStored(bitsstored),
  HighBit(highbit),
  PixelRepresentation(pixelrepresentation) {}
  ~PixelType() {}

  // Samples Per Pixel
  unsigned short GetSamplesPerPixel() const
    {
    return SamplesPerPixel;
    }
  void SetSamplesPerPixel(unsigned short spp)
    {
    SamplesPerPixel = spp;
    }

  // BitsAllocated
  unsigned short GetBitsAllocated() const
    {
    return BitsAllocated;
    }
  void SetBitsAllocated(unsigned short ba)
    {
    BitsAllocated = ba;
    }

  // BitsStored
  unsigned short GetBitsStored() const
    {
    return BitsStored;
    }
  void SetBitsStored(unsigned short bs)
    {
    BitsStored = bs;
    }

  // HighBit
  unsigned short GetHighBit() const
    {
    return HighBit;
    }
  void SetHighBit(unsigned short hb)
    {
    HighBit = hb;
    }

  // PixelRepresentation
  unsigned short GetPixelRepresentation() const
    {
    return PixelRepresentation;
    }
  void SetPixelRepresentation(unsigned short pr)
    {
    PixelRepresentation = pr;
    }

  TPixelType GetTPixelType() const;
  const char *PixelType::GetPixelTypeAsString(PixelType const &pt) const;

  uint8_t GetPixelSize() const;

  void Print(std::ostream &os) const;

private:
  // D 0028|0002 [US] [Samples per Pixel] [1]
  unsigned short SamplesPerPixel;
  // D 0028|0100 [US] [Bits Allocated] [8]
  unsigned short BitsAllocated;
  // D 0028|0101 [US] [Bits Stored] [8]
  unsigned short BitsStored;
  // D 0028|0102 [US] [High Bit] [7]
  unsigned short HighBit;
  // D 0028|0103 [US] [Pixel Representation] [0]
  unsigned short PixelRepresentation;
};

} // end namespace gdcm

#endif //__gdcmPixelType_h

