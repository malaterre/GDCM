/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmRescaler.h"

#include <stdlib.h> // atof

int TestRescaler(int, char *[])
{
  gdcm::Rescaler ir;

  /*
gdcmData/MR-MONO2-12-shoulder.dcm
(gdb) p intercept
$1 = 6.0999999999999999e-05
(gdb) p slope
$2 = 3.774114
(gdb) p in[i]
$3 = 3.77417493
...
p (in[i] - intercept)/slope
$7 = 0.99999998109891775

$10 = {Intercept = 6.0999999999999999e-05, Slope = 3.774114, PF = {SamplesPerPixel = 1, BitsAllocated = 32, BitsStored = 32, HighBit = 31, PixelRepresentation = 3}, ScalarRangeMin = 6.0999998822808266e-05,
  ScalarRangeMax = 247336.561051}

*/

  // (0028,1052) DS [0.000061]                               #   8, 1 RescaleIntercept
  // (0028,1053) DS [3.774114]                               #   8, 1 RescaleSlope

  const double intercept = atof( "0.000061" );
  const double slope     = atof( "3.774114" );
  ir.SetIntercept( intercept );
  ir.SetSlope( slope );
  ir.SetPixelFormat( gdcm::PixelFormat::FLOAT32 );
  const double smin = 6.0999998822808266e-05;
  const double smax = 247336.561051;
  ir.SetMinMaxForPixelType( smin, smax );
  
  float outref[] = { 0 };
{
  char *copy = (char*)outref;
  const uint16_t in[] = { 1. };
  const char *tempimage = (char*)in;
  size_t vtklen = sizeof(in);
  ir.SetPixelFormat( gdcm::PixelFormat::UINT16 );
  ir.Rescale(copy,tempimage,vtklen);

  std::cout << outref[0] << std::endl;
}

  ir.SetPixelFormat( gdcm::PixelFormat::FLOAT32 );
  uint16_t out[] = { 0 };
  char *copy = (char*)out;
  const float in[] = { 3.77417493 };
  if( outref[0] != in[0] )
  {
    std::cerr << "Wrong input/output" << std::endl;
    return 1;
  }
  const char *tempimage = (char*)in;
  size_t vtklen = sizeof(in);
  ir.InverseRescale(copy,tempimage,vtklen);

  std::cout << out[0] << std::endl;
  if( out[0] != 1 )
    {
    return 1;
    }

  return 0;
}

