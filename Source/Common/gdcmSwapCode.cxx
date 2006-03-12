#include "gdcmSwapCode.h"
#include <assert.h>

namespace gdcm
{

static const char *SwapCodeStrings[] = {
     "Unknown",
     "LittleEndian",
     "BigEndian",
     "BadLittleEndian",
     "BadBigEndian"
};

int SC::GetIndex(SwapCodeType sc)
{
  int idx = 0;
  switch(sc)
    {
  case Unknown:
    idx = 0;
    break;
  case LittleEndian:
    idx = 1;
    break;
  case BigEndian:
    idx = 2;
    break;
  case BadLittleEndian:
    idx = 3;
    break;
  case BadBigEndian:
    idx = 4;
    break;
  default:
    assert(0 && "Should not happen" );
    }
  return idx;
}

const char* SC::GetSwapCodeString(SwapCodeType sc)
{
  int idx = GetIndex(sc);
  return SwapCodeStrings[idx];
}

} // namespace gdcm
