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
  assert( NumberOfDimensions );
}

// TODO does it make sense to PlanarConfiguration in Image
// and SamplesPerPixel in PixelType when those two are linked...
unsigned int Image::GetPlanarConfiguration() const
{
  if( PlanarConfiguration && PT.GetSamplesPerPixel() != 3 )
    {
    // LEADTOOLS_FLOWERS-8-PAL-RLE.dcm
    // User specify PlanarConfiguration whereas SamplesPerPixel != 3
    gdcmWarningMacro( 
      "Can't set PlanarConfiguration if SamplesPerPixel is not 3" );
    // Let's assume it's this way...
    return 0;
    }
  return PlanarConfiguration;
}

void Image::SetPlanarConfiguration(unsigned int pc)
{
  PlanarConfiguration = pc;
}

const PhotometricInterpretation &Image::GetPhotometricInterpretation() const
{
  return PI;
}

void Image::SetPhotometricInterpretation(
  PhotometricInterpretation const &pi)
{
  PI = pi;
}

const unsigned int *Image::GetDimensions() const
{
  assert( NumberOfDimensions );
  return &Dimensions[0];
}

unsigned int Image::GetDimensions(unsigned int idx) const
{
  return Dimensions[idx];
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
  if( PT == PixelType::UINT12 )
    {
    assert( PT.GetSamplesPerPixel() == 1 );
    unsigned int save = mul;
    save *= 12;
    save /= 8;
    assert( save * 8 / 12 == mul );
    mul = save;
    }
  else
    {
    mul *= PT.GetPixelSize();
    }
  len = mul;
  // if Palette Color:
  //if( PI == PhotometricInterpretation::PALETTE_COLOR )
  //  {
  //  len *= 3;
  //  }
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

