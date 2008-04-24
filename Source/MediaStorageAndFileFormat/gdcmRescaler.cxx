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
#include "gdcmRescaler.h"
#include <stdlib.h> // abort

namespace gdcm
{

// parameter 'size' is in bytes
template <typename TOut, typename TIn>
void RescaleFunction(TOut *out, const TIn *in, double intercept, double slope, size_t size)
{
  assert( slope == 1. );
  size /= sizeof(TIn);
  for(size_t i = 0; i != size; ++i)
  {
    out[i] = (TOut)(in[i] + intercept);
  }
}

bool Rescaler::Rescale(char *out, const char *in, size_t n)
{
  PixelFormat output;
  // check if we are dealing with floating point type
  if( Slope != (int)Slope || Intercept != (int)Intercept)
  {
  // need to rescale as float (32bits) as slope/intercept are 32bits
  abort();
  }
  // else integral type
  RescaleFunction<short,unsigned short>((short*)out,(const unsigned short*)in,Intercept,Slope,n);

  return true;
}

} // end namespace gdcm

