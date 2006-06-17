#include "gdcmImage.h"

namespace gdcm
{

/*
 * Internal implementation everything assume that NumberOfDimensions was set
 */
unsigned int Image::GetNumberOfDimensions() const
{
  assert( NumberOfDimensions );
  return NumberOfDimensions;
}

void Image::SetNumberOfDimensions(unsigned int dim)
{
  NumberOfDimensions = dim;
}

const unsigned int *Image::GetDimensions() const
{
  assert( NumberOfDimensions );
  return &Dimensions[0];
}

void Image::SetDimensions(unsigned int *dims)
{
  assert( NumberOfDimensions );
  Dimensions = std::vector<unsigned int>(dims, 
    dims+NumberOfDimensions);
}

const double *Image::GetSpacing() const
{
  return &Spacing[0];
}

void Image::SetSpacing(double *spacing)
{
  assert( NumberOfDimensions );
  Spacing = std::vector<double>(spacing, 
    spacing+NumberOfDimensions);
}

const double *Image::GetOrigin() const
{
  return &Origin[0];
}

void Image::SetOrigin(double *ori)
{
  assert( NumberOfDimensions );
  Origin = std::vector<double>(ori, 
    ori+NumberOfDimensions);
}

unsigned long Image::GetBufferLength() const
{
  assert( NumberOfDimensions );
  assert( NumberOfDimensions == Dimensions.size() );
  unsigned long len = 0;
  unsigned int mul = 1;
  std::vector<unsigned int>::const_iterator it = Dimensions.begin();
  for(; it != Dimensions.end(); ++it)
    {
    mul *= *it;
    }
  len = mul;
  assert( len != 0 );
  return len;
}

unsigned int Image::GetSamplesPerPixel() const
{
  return SamplesPerPixel;
}

void Image::SetSamplesPerPixel(unsigned int spp)
{
  SamplesPerPixel = spp;
}

// BitsAllocated
unsigned int Image::GetBitsAllocated() const
{
  return BitsAllocated;
}

void Image::SetBitsAllocated(unsigned int ba)
{
  BitsAllocated = ba;
}

// BitsStored
unsigned int Image::GetBitsStored() const
{
  return BitsStored;
}

void Image::SetBitsStored(unsigned int bs)
{
  BitsStored = bs;
}

// HighBit
unsigned int Image::GetHighBit() const
{
  return HighBit;
}

void Image::SetHighBit(unsigned int hb)
{
  HighBit = hb;
}

// Acces the raw data
bool Image::GetBuffer(char *buffer) const
{
  buffer = 0;
  return false;
}

} // end namespace gdcm

