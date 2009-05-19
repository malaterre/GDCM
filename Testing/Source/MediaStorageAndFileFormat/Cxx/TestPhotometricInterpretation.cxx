/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmPhotometricInterpretation.h"

#include <string.h> // strlen

int TestPhotometricInterpretation(int, char *[])
{
  gdcm::PhotometricInterpretation pi;
  int end = gdcm::PhotometricInterpretation::PI_END;
  for( int i = 0; i < end; ++i)
    {
    const char *pistr = gdcm::PhotometricInterpretation::GetPIString( (gdcm::PhotometricInterpretation::PIType)i );
    if( strlen( pistr ) % 2 )
      {
      std::cerr << pistr << std::endl;
      return 1;
      }
    }

  pi = gdcm::PhotometricInterpretation::RGB;

  return 0;
}
