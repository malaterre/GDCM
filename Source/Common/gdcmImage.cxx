#include "gdcmImage.h"

namespace gdcm
{

unsigned int *Image::GetDimensions()
{
  return &Dimensions[0];
}

unsigned int Image::GetNumberOfDimensions()
{
  return Dimensions.size();
}

} // end namespace gdcm
