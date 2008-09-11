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
#include "gdcmImageChangePlanarConfiguration.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmFragment.h"

namespace gdcm
{

bool ImageChangePlanarConfiguration::Change()
{
  if( Input->GetPixelFormat().GetSamplesPerPixel() != 3 )
    {
    return false;
    }
  assert( Input->GetPhotometricInterpretation() == PhotometricInterpretation::YBR_FULL
    || Input->GetPhotometricInterpretation() == PhotometricInterpretation::YBR_FULL_422
    || Input->GetPhotometricInterpretation() == PhotometricInterpretation::RGB );
  Output = Input;
  if( Input->GetPlanarConfiguration() == PlanarConfiguration )
    {
    return true;
    }

  const Image &image = *Input;

  const unsigned int *dims = image.GetDimensions();
  unsigned long len = image.GetBufferLength();
  char *p = new char[len];
  image.GetBuffer( p );

  assert( len % 3 == 0 );
  size_t framesize = dims[0] * dims[1] * 3;
  assert( framesize * dims[2] == len );

  char *copy = new char[len];
  size_t size = framesize / 3;
  if( PlanarConfiguration == 0 )
    {
    for(unsigned int z = 0; z < dims[2]; ++z)
      {
      const char *frame = p + z * framesize;
      const char *r = frame + 0;
      const char *g = frame + size;
      const char *b = frame + size + size;

      char *framecopy = copy + z * framesize;
      ImageChangePlanarConfiguration::RGBPlanesToRGBPixels(framecopy, r, g, b, size);
      }
    }
  else // User requested to do PlanarConfiguration == 1
    {
    assert( PlanarConfiguration == 1 );
    for(unsigned int z = 0; z < dims[2]; ++z)
      {
      const char *frame = p + z * framesize;
      char *framecopy = copy + z * framesize;
      char *r = framecopy + 0;
      char *g = framecopy + size;
      char *b = framecopy + size + size;

      ImageChangePlanarConfiguration::RGBPixelsToRGBPlanes(r, g, b, frame, size);
      }
    }
  delete[] p;

  DataElement &de = Output->GetDataElement();
  de.SetByteValue( copy, len );
  delete[] copy;

  Output->SetPlanarConfiguration( PlanarConfiguration );

  return true;
}


} // end namespace gdcm

