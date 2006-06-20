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
  return type;
}

const char *PixelType::GetPixelTypeAsString(PixelType const &pt) const
{
  TPixelType type = pt.GetTPixelType();
  return PixelTypeStrings[type];
}

uint8_t PixelType::GetPixelSize() const
{
  return 0;
}

void PixelType::Print(std::ostream &os) const
{
  os << "SamplesPerPixel" << SamplesPerPixel << "\n"; 
  os << "BitsAllocated  " << BitsAllocated << "\n";
  os << "BitsStored     " << BitsStored << "\n";
  os << "HighBit        " << HighBit << "\n";
}

} // end namespace gdcm
