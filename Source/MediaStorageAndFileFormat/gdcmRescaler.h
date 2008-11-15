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
#ifndef __gdcmRescaler_h
#define __gdcmRescaler_h

#include "gdcmTypes.h"
#include "gdcmPixelFormat.h"

namespace gdcm
{

/**
 * \brief Rescale class
 *
 * \note handle floating point transformation back and forth to integer properly (no loss)
 */
class GDCM_EXPORT Rescaler
{
public:
  Rescaler():Intercept(0),Slope(1),PF(PixelFormat::UNKNOWN) {}
  ~Rescaler() {}

  /// Direct transform
  bool Rescale(char *out, const char *in, size_t n);

  /// Inverse transform
  bool InverseRescale(char *out, const char *in, size_t n);

  /// Set Intercept: used for both direct&inverse transformation
  void SetIntercept(double i) { Intercept = i; }

  /// Set Slope: user for both direct&inverse transformation
  void SetSlope(double s) { Slope = s; }

  /// Set Pixel Format of input data
  void SetPixelFormat(PixelFormat const & pf) { PF = pf; }

  /// Compute the Pixel Format of the output data
  /// Used for direct transformation 
  PixelFormat::ScalarType ComputeInterceptSlopePixelType();

  /// Set target interval for output data. A best match will be computed (if possible)
  /// Used for inverse transformation 
  void SetMinMaxForPixelType(double min, double max)
    {
    ScalarRangeMin = min;
    ScalarRangeMax = max;
    }

  /// Compute the Pixel Format of the output data
  /// Used for inverse transformation 
  PixelFormat ComputePixelTypeFromMinMax();

protected:
  template <typename TIn>
    void RescaleFunctionIntoBestFit(char *out, const TIn *in, size_t n);
  template <typename TIn>
    void InverseRescaleFunctionIntoBestFit(char *out, const TIn *in, size_t n);

private:
  double Intercept; // 0028,1052
  double Slope;     // 0028,1053
  PixelFormat PF;
  double ScalarRangeMin;
  double ScalarRangeMax;
};

} // end namespace gdcm

#endif //__gdcmRescaler_h
