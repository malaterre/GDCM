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
#include "gdcmImageCSAFilter.h"

namespace gdcm
{

/*
 *  gdcmSampleData/images_of_interest/MR-sonata-3D-as-Tile.dcm  
 */
bool reorganize_mosaic(const unsigned short *input, const unsigned int *inputdims, unsigned int square,
  const unsigned int *outputdims, unsigned short *output )
{
  for(unsigned x = 0; x < outputdims[0]; ++x)
    {
    for(unsigned y = 0; y < outputdims[1]; ++y)
      {
      for(unsigned z = 0; z < outputdims[2]; ++z)
        {
        output[ x + y*outputdims[0] + z*outputdims[0]*outputdims[1] ] = 
          input[ (x + z * outputdims[0]) + (y + (z/square)*outputdims[0])*inputdims[0] ];
        }
      }
    }
  return true;
}


bool ImageCSAFilter::Filter()
{
  Output = Input;

  return success;
}


} // end namespace gdcm

