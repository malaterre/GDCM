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
#ifndef __gdcmRescaler_h
#define __gdcmRescaler_h

#include "gdcmTypes.h"
#include "gdcmPixelFormat.h"

namespace gdcm
{

/**
 * \brief Rescale class
 * This class is meant to apply the linear tranform of Stored Pixel Value to Real World Value.
 * This is mostly found in CT or PET dataset, where the value are stored using one type, but
 * need to be converted to another scale using a linear tranform.
 * There are basically two cases:
 * In CT: the linear transform is generally integer based. Eg the Stored Pixel Type is unsigned
 * short 12bits, but to get Hounsfield unit, one need to apply the linear transform:
 *   RWV = 1. * SV - 1024
 * So the best scalar to store the Real World Value will be 16 bit signed type.
 * In PET: the linear transform is generally floating point based.
 * Since the dynamic range can be quite high, the Rescale Slope / Rescale Intercept can be
 * changing thoughout the Series. So it is important to read all linear tranform and deduce
 * the best Pixel Type only at the end (when all image to be read, have been parsed).
 *
 * \warning internally any time a floating point value is found either in the Rescale Slope
 * or the Rescale Intercept it is assumed that the best matching output pixel type if FLOAT64
 * in previous implementation it was FLOAT32. Because VR:DS is closer to a 64bits floating point type
 * FLOAT64 is thus a best matching pixel type for the floating point transformation.
 *
 * Example: Let say input is FLOAT64, and we want UINT16 as ouput, we would do:
 *
 *  Rescaler ir;
 *  ir.SetIntercept( 0 );
 *  ir.SetSlope( 5.6789 );
 *  ir.SetPixelFormat( FLOAT64 );
 *  ir.SetMinMaxForPixelType( ((PixelFormat)UINT16).GetMin(), ((PixelFormat)UINT16).GetMax() );
 *  ir.InverseRescale(output,input,numberofbytes );
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
