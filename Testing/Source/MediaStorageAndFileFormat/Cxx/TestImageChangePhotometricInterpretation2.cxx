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

#include <math.h>

template <typename T>
double diff(T rgb1[3], T rgb2[2])
{
  double sum = 0;
  for(int i = 0; i < 3; ++i)
    sum += fabs(rgb1[i] - rgb2[i]);
  //return sum < 1e-3 ? 0 : sum;
  return sum;
}

int TestImageChangePhotometricInterpretation2(int argc, char *argv[])
{
  double sdiff = 0;
  double max = 0;
  int nerrors = 0;
  int res = 0;
double error[3];
double error2[3];
double yerror[3];
  for(int r = 0; r < 256; ++r)
    for(int g = 0; g < 256; ++g)
      for(int b = 0; b < 256; ++b)
        {
        double rgb[3];
        double ybr[3] = {};
        double rgb2[3] = {};
        rgb[0] = r;
        rgb[1] = g;
        rgb[2] = b;
        // convert rgb 2 ybr:
        gdcm::ImageChangePhotometricInterpretation::RGB2YBR(ybr,rgb);
        // convert back:
        gdcm::ImageChangePhotometricInterpretation::YBR2RGB(rgb2,ybr);
        if( memcmp(rgb,rgb2,3) != 0 )
          {
          //std::cerr << "Problem with R,G,B=" << r << "," << g << "," << b << 
          //  " instead of " << (int)rgb2[0] << "," << (int)rgb2[1] << "," << (int)rgb2[2] << std::endl;
          //std::cerr << "diff:" << diff(rgb,rgb2) << std::endl;
          double d = diff(rgb,rgb2);
          sdiff += d;
          if( d > max ) 
            {
           error2[0] = rgb2[0];
           error2[1] = rgb2[1];
           error2[2] = rgb2[2];
           error[0] = rgb[0];
           error[1] = rgb[1];
           error[2] = rgb[2];
           yerror[0] = ybr[0];
           yerror[1] = ybr[1];
           yerror[2] = ybr[2];
            }
          max = std::max(d,max);
          res = 1;
          ++nerrors;
          }
        }

  std::cerr << "nerrors=" << nerrors << std::endl;
  std::cerr << "sdiff=" << sdiff<< std::endl;
  std::cerr << "max=" << max << std::endl;
  std::cerr << "max error=" << error[0] << "," << error[1] << "," << error[2] << std::endl;
  std::cerr << "max error2=" << error2[0] << "," << error2[1] << "," << error2[2] << std::endl;
  std::cerr << "max yerror=" << yerror[0] << "," << yerror[1] << "," << yerror[2] << std::endl;

  return res;
}
