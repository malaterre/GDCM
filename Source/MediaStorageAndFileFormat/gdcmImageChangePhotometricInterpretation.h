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
#ifndef __gdcmImageChangePhotometricInterpretation_h
#define __gdcmImageChangePhotometricInterpretation_h

#include "gdcmImageToImageFilter.h"
#include "gdcmPhotometricInterpretation.h"

namespace gdcm
{

class DataElement;
/**
 * \brief ImageChangePhotometricInterpretation class
 * Class to change the Photometric Interpetation of an input DICOM
 */
class GDCM_EXPORT ImageChangePhotometricInterpretation : public ImageToImageFilter
{
public:
  ImageChangePhotometricInterpretation():PI() {}
  ~ImageChangePhotometricInterpretation() {}

  /// Set/Get requested PhotometricInterpretation
  void SetPhotometricInterpretation(PhotometricInterpretation const &pi) { PI = pi; }
  const PhotometricInterpretation &GetPhotometricInterpretation() const { return PI; }

  /// Change
  bool Change();

  /// colorspace converstion (based on CCIR Recommendation 601-2)
  template <typename T>
  static void RGB2YBR(T ybr[3], const T rgb[3]);
  template <typename T>
  static void YBR2RGB(T rgb[3], const T ybr[3]);

protected:

private:
  PhotometricInterpretation PI;
};


template <typename T>
void ImageChangePhotometricInterpretation::RGB2YBR(T ybr[3], const T rgb[3])
{
  const double R = rgb[0];
  const double G = rgb[1];
  const double B = rgb[2];
  const double Y  =  .2990 * R + .5870 * G + .1140 * B;
  const double CB = -.16874 * R - .33126 * G + .5000 * B + 128;
  const double CR =  .5000 * R - .41869 * G - .08131 * B + 128;
  ybr[0] = Y ;
  ybr[1] = CB;
  ybr[2] = CR;
}

template <typename T>
void ImageChangePhotometricInterpretation::YBR2RGB(T rgb[3], const T ybr[3])
{

  const double Y  = ybr[0];
  const double Cb = ybr[1];
  const double Cr = ybr[2];
  //const double R =  1.0000e+00 * Y - 3.6820e-05 * CB + 1.4020e+00 * CR;
  //const double G =  1.0000e+00 * Y - 3.4411e-01 * CB - 7.1410e-01 * CR;
  //const double B =  1.0000e+00 * Y + 1.7720e+00 * CB - 1.3458e-04 * CR;
  const double R = Y                    + 1.402   * (Cr-128);
  const double G = Y - 0.34414 * (Cb-128) - 0.71414 * (Cr-128);
  const double B = Y + 1.772   * (Cb-128);
  rgb[0] = R;
  rgb[1] = G;
  rgb[2] = B;

}

} // end namespace gdcm

#endif //__gdcmImageChangePhotometricInterpretation_h

