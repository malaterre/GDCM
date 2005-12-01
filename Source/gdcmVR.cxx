#include "gdcmVR.h"
#include <string.h>
#include <assert.h>


namespace gdcm
{

static const char *VRStrings[] = {
  "INVALID",   // 0
  "AE",        // 1 
  "AS",        // 2
  "AT",        // 3
  "CS",        // 4
  "DA",        // 5
  "DS",        // 6
  "DT",        // 7
  "FL",        // 8
  "FD",        // 9
  "IS",        // 10
  "LO",        // 11
  "LT",        // 12
  "OB",        // 13
  "OF",        // 14
  "OW",        // 15
  "PN",        // 16
  "SH",        // 17
  "SL",        // 18
  "SQ",        // 19
  "SS",        // 20
  "ST",        // 21
  "TM",        // 22
  "UI",        // 23
  "UL",        // 24
  "UN",        // 25
  "US",        // 26
  "UT",        // 27
  "OB or OW",  // 28
  "US or SS",  // 29
  "US or SS or OW", //30
  0
};

int VR::GetIndex(VRType vr)
{
  assert( vr <= VR_END );
  int l;
  switch(vr)
    {
  case INVALID:
    l = 0;
    break;
  case OB_OW:
    l =  28;
    break;
  case US_SS:
    l =  29;
    break;
  case US_SS_OW:
    l =  30;
    break;
  case VR_END:
    l = 31;
    break;
  default:
      {
      int a = (int)vr;
      for (l = 0; a > 1; ++l)
        a >>= 1;
      l++;
      }
    }
  return l;
}

const char* VR::GetVRString(VRType vr)
{
  int idx = GetIndex(vr);
  return VRStrings[idx];
}

VR::VRType VR::GetVRType(const char *vr)
{
  VRType r = VR::VR_END;
  for (int i = 0; VRStrings[i] != NULL; i++)
    //if (strncmp(VRStrings[i],vr, strlen(VRStrings[i])) == 0)
    if (strcmp(VRStrings[i],vr) == 0)
      {
      switch(i)
        {
      case 0:
        r = INVALID;
        break;
      case 28:
        r = OB_OW;
        break;
      case 29:
        r = US_SS;
        break;
      case 30:
        r = US_SS_OW;
        break;
      case 31:
        r = VR_END; assert(0);
        break;
      default:
        r = (VR::VRType)(1 << (i-1));
        }
      break; // found one value, we can exit the for loop
      }

  return r;
}

bool VR::IsValid(const char *vr1, const VRType& vr2)
{
  assert( strlen(vr1) == 2 );
  VR::VRType vr = GetVRType(vr1);
  return vr & vr2;
}

bool VR::IsSwap(const char *vr)
{
  assert( vr[2] == '\0' );
  char vr_swap[3];
  vr_swap[0] = vr[1];
  vr_swap[1] = vr[0];
  vr_swap[2] = '\0';
  assert( GetVRType(vr_swap) != SS );
  return GetVRType(vr_swap) != VR_END;
}

} // end of namespace gdcm
