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
    || Input->GetPhotometricInterpretation() == PhotometricInterpretation::RGB );
  Output = Input;
  if( Input->GetPlanarConfiguration() == PlanarConfiguration )
    {
    return true;
    }

  const Image &image = *Input;

  unsigned long len = image.GetBufferLength();
  char *p = new char[len];
  image.GetBuffer( p );

  assert( len % 3 == 0 );
  size_t size = len / 3;

  const char *a = p + 0;
  const char *b = p + size;
  const char *c = p + size + size;

  char *copy = new char[len];
  char *pcopy = copy;
  for(size_t i = 0; i < size; ++i )
    {
    *pcopy++ = *a++;
    *pcopy++ = *b++;
    *pcopy++ = *c++;
    }

  DataElement &de = Output->GetDataElement();
  de.SetByteValue( copy, len );

  Output->SetPlanarConfiguration( PlanarConfiguration );

  delete[] p;
  delete[] copy;

  return true;
}


} // end namespace gdcm

