#ifndef __gdcmVR_h
#define __gdcmVR_h

/* \brief VR class
 * This is adapated from DICOM standart
 * The biggest difference is the INVALID VR
 * and the composite one that differ from standart (more like an addidtion)
 * This allow us to represent all the possible case express in the DICOMV3 dict
 */
#include "gdcmType.h"
#include <iostream>

namespace gdcm
{

class GDCM_EXPORT VR 
{
public:
typedef enum {
  INVALID = 0, // For Item/(Seq) Item Delimitation Item
  AE = 1,
  AS = 2,
  AT = 4,
  CS = 8,
  DA = 16,
  DS = 32,
  DT = 64,
  FL = 128,
  FD = 256,
  IS = 512,
  LO = 1024,
  LT = 2048,
  OB = 4096,
  OF = 8192,
  OW = 16384,
  PN = 32768,
  SH = 65536,
  SL = 131072,
  SQ = 262144,
  SS = 524288,
  ST = 1048576,
  TM = 2097152,
  UI = 4194304,
  UL = 8388608,
  UN = 16777216,
  US = 33554432,
  UT = 67108864,
  OB_OW = OB | OW,
  US_SS = US | SS,
  US_SS_OW = US | SS | OW,
  VR_END = UT+1  // Invalid VR, need to be max(VMType)+1
} VRType;


static const char* GetVRString(VRType vr);
static VRType GetVRType(const char *vr);
// Check if vr1 is valid against vr2,
// Typically vr1 is read from the file and vr2 is taken from the dict
static bool IsValid(const char *vr1, const VRType& vr2);
//static bool IsValid(const VRType& vr1, const VRType& vr2);
// Find out if the string read is byte swapped
static bool IsSwap(const char *vr);

// Size read on disk
static uint32_t GetLength(VRType vr) { 
  if( vr == VR::OB
   || vr == VR::OW
   || vr == VR::OF
   || vr == VR::SQ
   || vr == VR::UN )
    {
    return 4;
    }
  else
    return 2;
}

private:
// Internal function that map a VRType to an index in the VRStrings table
static int GetIndex(VRType vr);
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const VR::VRType&_val)
{
  _os << VR::GetVRString(_val);
  return _os;
}

} // end namespace gdcm

#endif //__gdcmVR_h
