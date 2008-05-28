/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
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
  Dimensions.resize( NumberOfDimensions ); // fill with 0
  Spacing.resize( NumberOfDimensions, 1 ); // fill with 1
}

// TODO does it make sense to PlanarConfiguration in Image
// and SamplesPerPixel in PixelFormat when those two are linked...
unsigned int Image::GetPlanarConfiguration() const
{
  if( PlanarConfiguration && PF.GetSamplesPerPixel() != 3 )
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

unsigned int Image::GetDimension(unsigned int idx) const
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

void Image::SetDimension(unsigned int idx, unsigned int dim)
{
  assert( NumberOfDimensions );
  assert( idx < NumberOfDimensions );
  Dimensions.resize( NumberOfDimensions );
  // Can dim be 0 ??
  Dimensions[idx] = dim;
}

const double *Image::GetSpacing() const
{
  assert( NumberOfDimensions );
  return &Spacing[0];
}

double Image::GetSpacing(unsigned int idx) const
{
  assert( NumberOfDimensions );
  if( idx < Spacing.size() )
    {
    return Spacing[idx];
    }
  //assert( 0 && "Should not happen" );
  return 1; // FIXME ???
}

void Image::SetSpacing(const double *spacing)
{
  assert( NumberOfDimensions );
  Spacing = std::vector<double>(spacing, 
    spacing+NumberOfDimensions);
}

void Image::SetSpacing(unsigned int idx, double spacing)
{
  Spacing.resize( idx + 1 );
  Spacing[idx] = spacing;
}

const double *Image::GetOrigin() const
{
  assert( NumberOfDimensions );
  if( !Origin.empty() )
    return &Origin[0];
  return 0;
}

double Image::GetOrigin(unsigned int idx) const
{
  assert( NumberOfDimensions );
  if( idx < Origin.size() )
    {
    return Origin[idx];
    }
  return 0; // FIXME ???
}

void Image::SetOrigin(const float *ori)
{
  assert( NumberOfDimensions );
  Origin.resize( NumberOfDimensions );
  for(unsigned int i = 0; i < NumberOfDimensions; ++i)
    {
    Origin[i] = ori[i];
    }
}

void Image::SetOrigin(const double *ori)
{
  assert( NumberOfDimensions );
  Origin = std::vector<double>(ori, 
    ori+NumberOfDimensions);
}

void Image::SetOrigin(unsigned int idx, double ori)
{
  Origin.resize( idx + 1 );
  Origin[idx] = ori;
}

const double *Image::GetDirectionCosines() const
{
  assert( NumberOfDimensions );
  if( !DirectionCosines.empty() )
    return &DirectionCosines[0];
  return 0;
}
double Image::GetDirectionCosines(unsigned int idx) const
{
  assert( NumberOfDimensions );
  if( idx < DirectionCosines.size() )
    {
    return DirectionCosines[idx];
    }
  return 0; // FIXME !!
}
void Image::SetDirectionCosines(const float *dircos)
{
  assert( NumberOfDimensions );
  DirectionCosines.resize( 6 );
  for(int i = 0; i < 6; ++i)
    {
    DirectionCosines[i] = dircos[i];
    }
}
void Image::SetDirectionCosines(const double *dircos)
{
  assert( NumberOfDimensions );
  DirectionCosines = std::vector<double>(dircos, 
    dircos+6);
}
void Image::SetDirectionCosines(unsigned int idx, double dircos)
{
  DirectionCosines.resize( idx + 1 );
  DirectionCosines[idx] = dircos;
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
  // Special handling of packed format:
  if( PF == PixelFormat::UINT12 )
    {
    assert( PF.GetSamplesPerPixel() == 1 );
    unsigned int save = mul;
    save *= 12;
    save /= 8;
    assert( save * 8 / 12 == mul );
    mul = save;
    }
  else
    {
    mul *= PF.GetPixelSize();
    }
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

bool Image::AreOverlaysInPixelData() const
{
  int total = 0;
  std::vector<Overlay>::const_iterator it = Overlays.begin();
  for(; it != Overlays.end(); ++it)
    {
    total += (int)it->IsInPixelData();
    }
  assert( total == (int)GetNumberOfOverlays() || !total );
  return total != 0;
}

void Image::Print(std::ostream &os) const
{
  //assert( NumberOfDimensions );
  os << "NumberOfDimensions: " << NumberOfDimensions << "\n";
  if( NumberOfDimensions )
    {
    assert( Dimensions.size() );
    os << "Dimensions: (";
    std::vector<unsigned int>::const_iterator it = Dimensions.begin();
    os << *it;
    for(++it; it != Dimensions.end(); ++it)
      {
      os << "," << *it;
      }
    os << ")\n";
{
  os << "Origin: (";
  if( !Origin.empty() )
    {
    std::vector<double>::const_iterator it = Origin.begin();
    os << *it;
    for(++it; it != Origin.end(); ++it)
      {
      os << "," << *it;
      }
    }
  os << ")\n";
}
{
    os << "Spacing: (";
    std::vector<double>::const_iterator it = Spacing.begin();
    os << *it;
    for(++it; it != Spacing.end(); ++it)
      {
      os << "," << *it;
      }
    os << ")\n";
}
{
  os << "DirectionCosines: (";
  if( !DirectionCosines.empty() )
    {
    std::vector<double>::const_iterator it = DirectionCosines.begin();
    os << *it;
    for(++it; it != DirectionCosines.end(); ++it)
      {
      os << "," << *it;
      }
    }
  os << ")\n";
}
{
  os << "Rescale Intercept/Slope: (" << Intercept << "," << Slope << ")\n";
}
    //std::vector<double> Spacing;
    //std::vector<double> Origin;

    PF.Print(os);
    }
}

} // end namespace gdcm

