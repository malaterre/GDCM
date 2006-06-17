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
  //Dimensions = std::vector<unsigned int>(dims, NumberOfDimensions);
}

double *Image::GetSpacing() const
{
}

void Image::SetSpacing(double *spacing)
{
}

double *Image::GetOrigin() const
{
}

void Image::SetOrigin(double *ori)
{
}

//unsigned int GetNumberOfScalarComponents() const;

// Acces the raw data
bool Image::GetBuffer(char *buffer) const
{
  buffer = 0;
  return false;
}

} // end namespace gdcm

