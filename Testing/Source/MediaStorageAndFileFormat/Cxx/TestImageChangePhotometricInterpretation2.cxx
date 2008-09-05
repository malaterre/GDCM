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
#include "gdcmImageChangePhotometricInterpretation.h"

int TestImageChangePhotometricInterpretation2(int argc, char *argv[])
{
  int res = 0;
  for(int r = 0; r < 256; ++r)
    for(int g = 0; g < 256; ++g)
      for(int b = 0; b < 256; ++b)
        {
        unsigned char rgb[3];
        unsigned char ybr[3] = {};
        unsigned char rgb2[3] = {};
        rgb[0] = r;
        rgb[1] = g;
        rgb[2] = b;
        // convert rgb 2 ybr:
        gdcm::ImageChangePhotometricInterpretation::RGB2YBR(ybr,rgb);
        // convert back:
        gdcm::ImageChangePhotometricInterpretation::YBR2RGB(rgb2,ybr);
        if( memcmp(rgb,rgb2,3) != 0 )
          {
          std::cerr << "Problem with R,G,B=" << r << "," << g << "," << b << std::endl;
          res = 1;
abort();
          }
        }

  return res;
}
