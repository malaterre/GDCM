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
#include "gdcmDirectionCosines.h"

int TestDirectionCosines(int, char *[])
{
  gdcm::DirectionCosines dc;
  const double *dircos = dc;
  if( !dc.IsValid() )
    {
    return 1;
    }
  const double cross[3] = {0,0,1};
  double z[3];
  dc.Cross(z);
  if( z[0] != cross[0] 
   || z[1] != cross[1] 
   || z[2] != cross[2] )
    {
    return 1;
    }

  return 0;
}

