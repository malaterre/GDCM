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
#ifndef __gdcmRescaler_h
#define __gdcmRescaler_h

#include "gdcmTypes.h"

namespace gdcm
{


class GDCM_EXPORT Rescaler
{
public:
  Rescaler() {}
  ~Rescaler() {}
  bool Rescale(char *out, const char *in, size_t n);
  void SetIntercept(double i) { Intercept = i; }
  void SetSlope(double s) { Slope = s; }

private:
  double Intercept; // 0028,1052
  double Slope;     // 0028,1053
};

} // end namespace gdcm

#endif //__gdcmUnpacker12Bits_h
