#include "gdcmImage.h"
#include "gdcmTrace.h"

#include <iostream>

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

unsigned int Image::GetPlanarConfiguration() const
{
  return PlanarConfiguration;
}

void Image::SetPlanarConfiguration(unsigned int pc)
{
  assert( !PlanarConfiguration );
  if( pc && PT.GetSamplesPerPixel() != 3 )
    {
    // This is the chicken and the egg, which one do we set first.
    // Since SamplesPerPixel comes first (0028,0002), it is expected
    // that at the time of setting PlanarConfiguration SamplesPerPixel
    // would have the proper value
    gdcmWarningMacro( 
      "Can't set PlanarConfiguration if SamplesPerPixel is not 3" )
    }
  else
    {
    PlanarConfiguration = pc;
    }
}

const unsigned int *Image::GetDimensions() const
{
  assert( NumberOfDimensions );
  return &Dimensions[0];
}

void Image::SetDimensions(unsigned int *dims)
{
  assert( NumberOfDimensions );
  assert( Dimensions.empty() );
  Dimensions = std::vector<unsigned int>(dims, 
    dims+NumberOfDimensions);
}

void Image::SetDimensions(unsigned int idx, unsigned int dim)
{
  assert( NumberOfDimensions );
  assert( idx < NumberOfDimensions );
  Dimensions.resize( NumberOfDimensions );
  Dimensions[idx] = dim;
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
  // First multiply the dimensions:
  std::vector<unsigned int>::const_iterator it = Dimensions.begin();
  for(; it != Dimensions.end(); ++it)
    {
    mul *= *it;
    }
  // Multiply by the pixel size:
  mul *= PT.GetPixelSize();
  len = mul;
  assert( len != 0 );
  return len;
}

// Acces the raw data
bool Image::GetBuffer(char *buffer) const
{
  buffer = 0;
  return false;
}

void Image::Print(std::ostream &os) const
{
  assert( NumberOfDimensions );
  os << "NumberOfDimensions" << NumberOfDimensions << "\n";
  assert( Dimensions.size() );
  os << "Dimensions: (";
  std::vector<unsigned int>::const_iterator it = Dimensions.begin();
  os << *it;
  for(++it; it != Dimensions.end(); ++it)
    {
    os << "," << *it;
    }
  os << ")\n";
  //std::vector<unsigned int> Dimensions;
  //std::vector<double> Spacing;
  //std::vector<double> Origin;

  PT.Print(os);
}

} // end namespace gdcm

