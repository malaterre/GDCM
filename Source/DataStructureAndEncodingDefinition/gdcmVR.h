#ifndef __gdcmVR_h
#define __gdcmVR_h

#include "gdcmType.h"
#include "gdcmTag.h"

#include <iostream>
#include <assert.h>

namespace gdcm
{
/* \brief VR class
 * This is adapated from DICOM standart
 * The biggest difference is the INVALID VR
 * and the composite one that differ from standart (more like an addidtion)
 * This allow us to represent all the possible case express in the DICOMV3 dict
 * \note
 * VALUE REPRESENTATION (VR)
 * Specifies the data type and format of the Value(s) contained in the
 * Value Field of a Data Element.
 * VALUE REPRESENTATION FIELD:
 * The field where the Value Representation of a Data Element is
 * stored in the encoding of a Data Element structure with explicit VR.
 */
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

  typedef enum {
    ASCII = 0,
    BINARY
  } VREncoding; // VR Encoding

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
    assert( vr != VR::INVALID );
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
  
  // Some use of template metaprograming with ugly macro
  static bool IsBinary(VRType const &vr);
  static bool IsASCII(VRType const &vr);
  // TODO: REMOVE ME
  static bool CanDisplay(VRType const &vr);
  // TODO: REMOVE ME
  static bool IsBinary2(VRType const &vr);
  // TODO: REMOVE ME
  static bool IsASCII2(VRType const &vr);
  
  static void Read(std::istream &is, VRType &vr)
    {
    char vr_str[3];
    is.read(vr_str, 2);
    vr_str[2] = '\0';
    vr = VR::GetVRType(vr_str);
    assert( vr != VR::VR_END );
    }

  static void Write(std::ostream &os, VRType const & vr)
    {
    const char *vr_str = GetVRString(vr);
    assert( strlen( vr_str ) == 2 );
    os.write(vr_str, 2);
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

// Tells whether VR Type is ASCII or Binary
template<int T> struct TypeToEncoding;
// Convert from VR Type to real underlying type
template<int T> struct TypeToType;
#define TYPETOREPRESENTATION(type,rep, rtype)              \
  template<> struct TypeToEncoding<VR::type>  \
  { enum { Mode = VR::rep }; };                     \
  template<> struct TypeToType<VR::type>        \
  { typedef rtype Type; };

// TODO: Could be generated from XML file
TYPETOREPRESENTATION(AE,ASCII ,float)
TYPETOREPRESENTATION(AS,ASCII ,float)
TYPETOREPRESENTATION(AT,BINARY,Tag)
TYPETOREPRESENTATION(CS,ASCII ,float)
TYPETOREPRESENTATION(DA,ASCII ,float)
TYPETOREPRESENTATION(DS,ASCII ,float)
TYPETOREPRESENTATION(DT,ASCII ,float)
TYPETOREPRESENTATION(FL,BINARY,float)
TYPETOREPRESENTATION(FD,BINARY,double)
TYPETOREPRESENTATION(IS,ASCII ,float)
TYPETOREPRESENTATION(LO,ASCII ,float)
TYPETOREPRESENTATION(LT,ASCII ,float)
TYPETOREPRESENTATION(OB,BINARY,float)
TYPETOREPRESENTATION(OF,BINARY,float)
TYPETOREPRESENTATION(OW,BINARY,float)
TYPETOREPRESENTATION(PN,ASCII ,char*)
TYPETOREPRESENTATION(SH,ASCII ,float)
TYPETOREPRESENTATION(SL,BINARY,int32_t)
TYPETOREPRESENTATION(SQ,BINARY,float)
TYPETOREPRESENTATION(SS,BINARY,int16_t)
TYPETOREPRESENTATION(ST,ASCII ,float)
TYPETOREPRESENTATION(TM,ASCII ,float)
TYPETOREPRESENTATION(UI,ASCII ,float)
TYPETOREPRESENTATION(UL,BINARY,uint32_t)
TYPETOREPRESENTATION(UN,BINARY,float)
TYPETOREPRESENTATION(US,BINARY,uint16_t)
TYPETOREPRESENTATION(UT,BINARY,float)


} // end namespace gdcm

#endif //__gdcmVR_h

