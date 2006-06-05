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

// Optimized version for transforming a read VR from DICOM file
// into a VRType (does not support OB_OW for instance)
VR::VRType VR::GetVRTypeFromFile(const char *vr)
{
  VRType r = VR::VR_END;
  for (int i = 1; VRStrings[i] != NULL; i++)
    {
    const char *ref = VRStrings[i];
    // Use lazy evaluation instead of strncmp
    if (ref[0] == vr[0] && ref[1] == vr[1] )
      {
      r = (VR::VRType)(1 << (i-1));
      break;
      }
    }
  // postcondition
  assert( r != VR::INVALID
       && r != VR::OB_OW
       && r != VR::US_SS
       && r != VR::US_SS_OW
       && r != VR::VR_END );
  return r;
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
        assert( vr[2] == 0 );
        r = (VR::VRType)(1 << (i-1));
        }
      break; // found one value, we can exit the for loop
      }

  return r;
}

bool VR::IsValid(const char *vr)
{
  for (int i = 1; VRStrings[i] != NULL; i++)
    {
    const char *ref = VRStrings[i];
    // Use lazy evaluation instead of strncmp
    if (ref[0] == vr[0] && ref[1] == vr[1] )
      {
      assert( i < 28 ); // FIXME
      return true;
      }
    }
  return false;
}

bool VR::IsValid(const char *vr1, const VRType& vr2)
{
  assert( strlen(vr1) == 2 );
  VR::VRType vr = GetVRType(vr1);
  return (bool)(vr & vr2);
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

#define VRTemplateCase(type, rep) \
  case VR::type: \
    return (VR::VREncoding)TypeToEncoding<VR::type>::Mode  \
       == VR::rep;
#define VRTemplate(rep) \
VRTemplateCase(AE,rep) \
VRTemplateCase(AS,rep) \
VRTemplateCase(AT,rep) \
VRTemplateCase(CS,rep) \
VRTemplateCase(DA,rep) \
VRTemplateCase(DS,rep) \
VRTemplateCase(DT,rep) \
VRTemplateCase(FL,rep) \
VRTemplateCase(FD,rep) \
VRTemplateCase(IS,rep) \
VRTemplateCase(LO,rep) \
VRTemplateCase(LT,rep) \
VRTemplateCase(OB,rep) \
VRTemplateCase(OF,rep) \
VRTemplateCase(OW,rep) \
VRTemplateCase(PN,rep) \
VRTemplateCase(SH,rep) \
VRTemplateCase(SL,rep) \
VRTemplateCase(SQ,rep) \
VRTemplateCase(SS,rep) \
VRTemplateCase(ST,rep) \
VRTemplateCase(TM,rep) \
VRTemplateCase(UI,rep) \
VRTemplateCase(UL,rep) \
VRTemplateCase(UN,rep) \
VRTemplateCase(US,rep) \
VRTemplateCase(UT,rep)

bool VR::IsASCII(VRType const & vr)
{
  switch(vr)
    {
    VRTemplate(ASCII)
  default:
      abort();
      return false;
    }
}

bool VR::IsASCII2(VRType const & vr )
{
  return
    vr == AE ||
    vr == AS ||
    vr == CS ||
    vr == DA ||
    vr == DS ||
    vr == DT ||
    vr == IS ||
    vr == LO ||
    vr == LT ||
    vr == PN ||
    vr == SH ||
    vr == ST ||
    vr == TM ||
    vr == UI;
}

bool VR::IsBinary(VRType const & vr)
{
  switch(vr)
    {
    VRTemplate(BINARY)
  default:
      abort();
      return false;
    }
}

bool VR::IsBinary2(VRType const & vr)
{
  //assert( vr != OF );
  return 
    vr == OB ||
    vr == OW ||
    vr == OB_OW ||
    vr == UN ||
    vr == SQ ;
}

bool VR::CanDisplay(VRType const & vr)
{
  return 
    vr == AE ||
    vr == AS ||
    vr == AT ||
    vr == CS ||
    vr == DA ||
    vr == DS ||
    vr == FL ||
    vr == FD ||
    vr == IS ||
    vr == LO ||
    vr == LT ||
    vr == PN ||
    vr == SH ||
    vr == SL ||
    vr == SS ||
    vr == ST ||
    vr == TM ||
    vr == UI ||
    vr == UL ||
    vr == US ||
    vr == UT;
}


} // end of namespace gdcm
