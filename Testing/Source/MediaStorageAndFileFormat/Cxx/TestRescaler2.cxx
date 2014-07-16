/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmRescaler.h"

#include <vector>
#include <limits>

int TestRescaler2(int, char *[])
{
  // gdcmData/MR-MONO2-12-shoulder.dcm
  // (0028,1052) DS [0.000061] # 8,1 Rescale Intercept
  // (0028,1053) DS [3.774114] # 8,1 Rescale Slope
  const double intercept = 0.000061;
  const double slope     = 3.774114;

  // (0028,0100) US 16                                                 # 2,1 Bits Allocated
  // (0028,0101) US 12                                                 # 2,1 Bits Stored
  // (0028,0102) US 11                                                 # 2,1 High Bit
  // (0028,0103) US 0                                                  # 2,1 Pixel Representation
  const gdcm::PixelFormat pixeltype(1,16,12,11,0);

  gdcm::Rescaler r;
  r.SetIntercept( intercept );
  r.SetSlope( slope );
  r.SetPixelFormat( pixeltype );

  gdcm::PixelFormat::ScalarType outputpt;
  outputpt = r.ComputeInterceptSlopePixelType();
  if( outputpt != gdcm::PixelFormat::FLOAT64 ) return 1;

  gdcm::PixelFormat::ScalarType targetpixeltype = gdcm::PixelFormat::FLOAT64;
  r.SetTargetPixelType( targetpixeltype );
  r.SetUseTargetPixelType(true);

  std::vector<unsigned short> values;
  const unsigned short nvalues = 1 << 12; // 2^12 = 4096
  values.reserve( nvalues );
  for( unsigned short i = 0; i < nvalues; ++i )
    values.push_back( std::numeric_limits<unsigned short>::min() + i );

  std::vector<double> output;
  output.resize( nvalues );
  if( !r.Rescale((char*)&output[0],(char*)&values[0],nvalues * sizeof( values[0] ) ) )
    {
    return 1;
    }

  gdcm::Rescaler ir;
  ir.SetIntercept( intercept );
  ir.SetSlope( slope );
  ir.SetPixelFormat( gdcm::PixelFormat::FLOAT64 );
  ir.SetMinMaxForPixelType( 0, 4096 );
  gdcm::PixelFormat pf2 = ir.ComputePixelTypeFromMinMax();

  if( pf2 != pixeltype ) return 1;

  std::vector<unsigned short> check;
  check.resize( nvalues );

  if( !ir.InverseRescale((char*)&check[0],(char*)&output[0], nvalues * sizeof( output[0] ) ) )
    {
    return 1;
    }

  if( check != values )
    {
    return 1;
    }

  return 0;
}
