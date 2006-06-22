#include "gdcmPhotometricInterpretation.h"

namespace gdcm
{

static const char *PIStrings[] = {
  "UNKNOW",
  "MONOCHROME1 ",
  "MONOCHROME2 ",
  "PALETTE_COLOR",
  "RGB",
  "HSV",
  "ARGB",
  "CMYK",
  "YBR_FULL",
  "YBR_FULL_422",
  "YBR_PARTIAL_422",
  "YBR_PARTIAL_420",
  "YBR_ICT",
  "YBR_RCT",
  0
};

const char *PhotometricInterpretation::GetPIString(PIType pi)
{
  assert( pi < PhotometricInterpretation::PI_END );
  return PIStrings[pi];
}

PhotometricInterpretation::PIType PhotometricInterpretation::GetPIType(const char *pi)
{
  int i = 0;
  while(PIStrings[i] != 0)
    {
    if( strcmp(pi, PIStrings[i]) == 0 )
      {
      return PIType(i);
      }
    ++i;
    }

  return PI_END;
}

bool PhotometricInterpretation::IsRetired(PIType pi)
{
  return pi == HSV || pi == ARGB || pi == CMYK;
}

} // end namespace gdcm
