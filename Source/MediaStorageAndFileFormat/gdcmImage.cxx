/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmImage.h"
#include "gdcmTrace.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmByteValue.h"
#include "gdcmDataSet.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmFragment.h"

#include <iostream>

namespace gdcm
{

const double *Image::GetSpacing() const
{
  assert( NumberOfDimensions );
  return &SpacingArray[0][0];
}

double Image::GetSpacing(unsigned int idx) const
{
  assert( NumberOfDimensions );
  assert( idx < 3 );
  return SpacingArray[0][idx];
}

void Image::SetSpacing(const double spacing[3])
{
  assert( NumberOfDimensions );
  assert( NumberOfDimensions <= 3 );
  for(unsigned int i = 0; i < NumberOfDimensions; ++i )
    SpacingArray[0][i] = spacing[i];
}

void Image::SetSpacing(unsigned int idx, double spacing)
{
  assert( NumberOfDimensions );
  assert( idx < 3 );
  //Spacing.resize( 3 /*idx + 1*/ );
  SpacingArray[0][idx] = spacing;
}

const double *Image::GetOrigin() const
{
  assert( NumberOfDimensions );
  return &OriginArray[0][0];
}

double Image::GetOrigin(unsigned int idx) const
{
  assert( NumberOfDimensions );
  assert( idx < 3 );
//  if( idx < OriginArray[0].size() )
    {
    return OriginArray[0][idx];
    }
//  return 0; // FIXME ???
}

void Image::SetOrigin(const float *ori)
{
  assert( NumberOfDimensions );
  assert( NumberOfDimensions <= 3 );
  //OriginArray[0].resize( NumberOfDimensions );
  for(unsigned int i = 0; i < NumberOfDimensions; ++i)
    {
    OriginArray[0][i] = ori[i];
    }
}

void Image::SetOrigin(const double ori[3])
{
  assert( NumberOfDimensions );
//  Origin = std::vector<double>(ori,
//    ori+NumberOfDimensions);
  assert( NumberOfDimensions <= 3 );
//  OriginArray[0].resize( NumberOfDimensions );
  for(unsigned int i = 0; i < NumberOfDimensions; ++i)
    {
    OriginArray[0][i] = ori[i];
    }
}

void Image::SetOrigin(unsigned int idx, double ori)
{
  assert( NumberOfDimensions );
  assert( idx < 3 );
//  Origin.resize( idx + 1 );
  OriginArray[0][idx] = ori;
}

const double *Image::GetDirectionCosines() const
{
  assert( NumberOfDimensions );
//  if( !DirectionCosines.empty() )
  return &DirectionCosinesArray[0][0];
//  return 0;
}
double Image::GetDirectionCosines(unsigned int idx) const
{
  assert( NumberOfDimensions );
  assert( idx < 6 );
//  if( idx < DirectionCosines.size() )
    {
    return DirectionCosinesArray[0][idx];
    }
//  return 0; // FIXME !!
}

void Image::SetDirectionCosines(const float dircos[3])
{
  assert( NumberOfDimensions );
//  DirectionCosines.resize( 6 );
  for(int i = 0; i < 6; ++i)
    {
    DirectionCosinesArray[0][i] = dircos[i];
    }
}

void Image::SetDirectionCosines(const double dircos[3])
{
  assert( NumberOfDimensions );
//  DirectionCosines = std::vector<double>(dircos,
//    dircos+6);
  for(int i = 0; i < 6; ++i)
    {
    DirectionCosinesArray[0][i] = dircos[i];
    }
}

void Image::SetDirectionCosines(unsigned int idx, double dircos)
{
  assert( NumberOfDimensions );
  assert( idx < 6 );
  //DirectionCosinesArray[0].resize( idx + 1 );
  DirectionCosinesArray[0][idx] = dircos;
}

#if !defined(GDCM_LEGACY_REMOVE)
SwapCode Image::GetSwapCode() const
{
  return SwapCode();
}

void Image::SetSwapCode(SwapCode sc)
{
}

void Image::SetIntercept(double intercept) { InterceptSlopeArray[0][0] = intercept; }
double Image::GetIntercept() const { return InterceptSlopeArray[0][0]; }

void Image::SetSlope(double slope) { InterceptSlopeArray[0][1] = slope; }
double Image::GetSlope() const { return InterceptSlopeArray[0][1]; }
#endif

void Image::SetIntercept(unsigned int idx, double intercept)
{
  assert( NumberOfDimensions );
  assert( idx < InterceptSlopeArray.size() );
  assert( NumberOfDimensions == InterceptSlopeArray.size() );
  InterceptSlopeArray[idx][0] = intercept;
}

double Image::GetIntercept(unsigned int idx) const
{
  return InterceptSlopeArray[idx][0];
}

void Image::SetSlope(unsigned int idx, double slope)
{
  assert( NumberOfDimensions );
  assert( idx < NumberOfDimensions );
  InterceptSlopeArray[idx][1] = slope;
}

double Image::GetSlope(unsigned int idx) const
{
  return InterceptSlopeArray[idx][1];
}

void Image::Print(std::ostream &os) const
{
  Pixmap::Print(os);
#if 0
  if( NumberOfDimensions )
    {
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

    }
#endif
}

} // end namespace gdcm
