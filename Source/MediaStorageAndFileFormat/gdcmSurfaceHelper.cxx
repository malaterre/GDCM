#include "gdcmSurfaceHelper.h"

#include <cmath>

namespace gdcm
{

std::vector< float > SurfaceHelper::RGBToXYZ(const std::vector<float> & RGB)
{
  std::vector< float > XYZ(3);
  float tmp[3];

  tmp[0] = RGB[0];
  tmp[1] = RGB[1];
  tmp[2] = RGB[2];

  const float A = 1 / 12.92;
  const float B = 1 / 1.055;

  if ( tmp[0] > 0.04045 ) tmp[0] = pow( ( ( tmp[0] + 0.055 ) * B ), 2.4);
  else                    tmp[0] *= A;
  if ( tmp[1] > 0.04045 ) tmp[1] = pow( ( ( tmp[1] + 0.055 ) * B ), 2.4);
  else                    tmp[1] *= A;
  if ( tmp[2] > 0.04045 ) tmp[2] = pow( ( ( tmp[2] + 0.055 ) * B ), 2.4);
  else                    tmp[2] *= A;

  tmp[0] *= 100;
  tmp[1] *= 100;
  tmp[2] *= 100;

  //Observer. = 2°, Illuminant = D65
  XYZ[0] = tmp[0] * 0.4124 + tmp[1] * 0.3576 + tmp[2] * 0.1805;
  XYZ[1] = tmp[0] * 0.2126 + tmp[1] * 0.7152 + tmp[2] * 0.0722;
  XYZ[2] = tmp[0] * 0.0193 + tmp[1] * 0.1192 + tmp[2] * 0.9505;

  return XYZ;
}

std::vector< float > SurfaceHelper::XYZToRGB(const std::vector<float> & XYZ)
{
  std::vector< float > RGB(3);
  float tmp[3];

  tmp[0] = XYZ[0];
  tmp[1] = XYZ[1];
  tmp[2] = XYZ[2];

  // Divide by 100
  tmp[0] *= 0.01;        //X from 0 to  95.047      (Observer = 2°, Illuminant = D65)
  tmp[1] *= 0.01;        //Y from 0 to 100.000
  tmp[2] *= 0.01;        //Z from 0 to 108.883

  RGB[0] = tmp[0] *  3.2406 + tmp[1] * -1.5372 + tmp[2] * -0.4986;
  RGB[1] = tmp[0] * -0.9689 + tmp[1] *  1.8758 + tmp[2] *  0.0415;
  RGB[2] = tmp[0] *  0.0557 + tmp[1] * -0.2040 + tmp[2] *  1.0570;

  const float A = 1 / 2.4;

  if ( RGB[0] > 0.0031308 )   RGB[0] = 1.055 * pow( RGB[0], A) - 0.055;
  else                        RGB[0] *= 12.92;
  if ( RGB[1] > 0.0031308 )   RGB[1] = 1.055 * pow( RGB[1], A) - 0.055;
  else                        RGB[1] *= 12.92;
  if ( RGB[2] > 0.0031308 )   RGB[2] = 1.055 * pow( RGB[2], A) - 0.055;
  else                        RGB[2] *= 12.92;

  return RGB;
}

std::vector< float > SurfaceHelper::XYZToCIELab(const std::vector<float> & XYZ)
{
  std::vector< float > CIELab(3);
  float tmp[3];

  tmp[0] = XYZ[0] / 95.047;   //ref_X =  95.047   Observer= 2°, Illuminant= D65
  tmp[1] = XYZ[1] * 0.01;     //ref_Y = 100.000
  tmp[2] = XYZ[2] / 108.883;  //ref_Z = 108.883

  const float A = 1. / 3.;
  const float B = 16. / 116.;

  if ( tmp[0] > 0.008856 )  tmp[0] = pow(tmp[0], A);
  else                      tmp[0] = 7.787 * tmp[0] + B;
  if ( tmp[1] > 0.008856 )  tmp[1] = pow(tmp[1], A);
  else                      tmp[1] = 7.787 * tmp[1] + B;
  if ( tmp[2] > 0.008856 )  tmp[2] = pow(tmp[2], A);
  else                      tmp[2] = 7.787 * tmp[2] + B;

  CIELab[0] = ( 116 * tmp[1] ) - 16;
  CIELab[1] = 500 * ( tmp[0] - tmp[1] );
  CIELab[2] = 200 * ( tmp[1] - tmp[2] );

  return CIELab;
}

std::vector< float > SurfaceHelper::CIELabToXYZ(const std::vector<float> & CIELab)
{
  std::vector< float > XYZ(3);
  float tmp[3];

  tmp[1] = ( CIELab[0] + 16 ) / 116.;
  tmp[0] = CIELab[1] * 0.002 + tmp[1];
  tmp[2] = tmp[1] - CIELab[2] * 0.005;

  // Compute t
  const float A = tmp[0]*tmp[0]*tmp[0];
  const float B = tmp[1]*tmp[1]*tmp[1];
  const float C = tmp[2]*tmp[2]*tmp[2];

  const float D = 16 / 116.;

  // Compute f(t)
  if ( B > 0.008856 ) tmp[1] = B;
  else                tmp[1] = ( tmp[1] - D ) / 7.787;
  if ( A > 0.008856 ) tmp[0] = A;
  else                tmp[0] = ( tmp[0] - D ) / 7.787;
  if ( C > 0.008856 ) tmp[2] = C;
  else                tmp[2] = ( tmp[2] - D ) / 7.787;

  XYZ[0] = tmp[0] * 95.047;   //ref_X =  95.047     Observer= 2°, Illuminant= D65
  XYZ[1] = tmp[1] * 100;      //ref_Y = 100.000
  XYZ[2] = tmp[2] * 108.883;  //ref_Z = 108.883

  return XYZ;
}

}
