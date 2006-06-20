#include "gdcmPixelType.h"

namespace gdcm
{
static const char *PixelTypeStrings[] = {
  "INT8",
  "UINT8",
  "INT12",
  "UINT12",
  "INT16",
  "UINT16",
  NULL,
};

PixelType::TPixelType PixelType::GetTPixelType() const
{
  TPixelType type = PixelType::UNKNOWN;
  switch( BitsAllocated )
    {
  case 8:
    type = PixelType::UINT8;
    break;
  case 12:
    type = PixelType::UINT12;
    break;
  case 16:
    type = PixelType::UINT16;
    break;
  default:
    abort();
    }
  if( PixelRepresentation )
    {
    assert( type <= INT16 );
    // That's why you need to order properly type in TPixelType
    type = TPixelType(int(type)+1);
    }
  return type;
}

const char *PixelType::GetPixelTypeAsString(PixelType const &pt) const
{
  TPixelType type = pt.GetTPixelType();
  return PixelTypeStrings[type];
}

uint8_t PixelType::GetPixelSize() const
{
  uint8_t pixelsize = BitsAllocated / 8;
  pixelsize *= SamplesPerPixel;

  return pixelsize;
}

void PixelType::Print(std::ostream &os) const
{
  os << "SamplesPerPixel    :" << SamplesPerPixel << "\n"; 
  os << "BitsAllocated      :" << BitsAllocated << "\n";
  os << "BitsStored         :" << BitsStored << "\n";
  os << "HighBit            :" << HighBit << "\n";
  os << "PixelRepresentation:" << PixelRepresentation << "\n";
}

} // end namespace gdcm
