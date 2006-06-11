#ifndef __gdcmVR_h
#define __gdcmVR_h

#include "gdcmTag.h"
#include "gdcmVL.h"

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

  // This function will only look at the very first two chars nothing else
  static VRType GetVRTypeFromFile(const char *vr);

  // You need to make sure end of string is \0
  static VRType GetVRType(const char *vr);

  static bool IsValid(const char *vr);
  // Check if vr1 is valid against vr2,
  // Typically vr1 is read from the file and vr2 is taken from the dict
  static bool IsValid(const char *vr1, const VRType& vr2);
  //static bool IsValid(const VRType& vr1, const VRType& vr2);
  // Find out if the string read is byte swapped
  static bool IsSwap(const char *vr);
  
  // Size read on disk
  VL GetLength() const {
    return VR::GetLength(VRField);
  }
  static uint32_t GetLength(VRType vr) { 
    assert( vr != VR::INVALID );
    if( vr == VR::OB
     || vr == VR::OW
     || vr == VR::OF
     || vr == VR::SQ
     || vr == VR::UN
     || vr == VR::UT )
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
  
  VR(VRType vr = INVALID):VRField(vr) { }
  //VR(VR const &vr):VRField(vr.VRField) { }
  IStream &Read(IStream &is)
    {
    char vr[2];
    is.Read(vr, 2);
    VRField = VR::GetVRTypeFromFile(vr);
    assert( VRField != VR::VR_END );
    assert( VRField != VR::INVALID );
    if( VRField == VR::OB
     || VRField == VR::OW
     || VRField == VR::OF
     || VRField == VR::SQ
     || VRField == VR::UN
     || VRField == VR::UT )
      {
      char dum[2];
      is.Read(dum, 2);
      }
    return is;
    }

  const OStream & Write(OStream &os) const
    {
    const char *vr = GetVRString(VRField);
    assert( strlen( vr ) == 2 );
    os.Write(vr, 2);
    // See PS 3.5, Date Element Structure With Explicit VR
    if( VRField == VR::OB
     || VRField == VR::OW
     || VRField == VR::OF
     || VRField == VR::SQ
     || VRField == VR::UN
     || VRField == VR::UT )
      {
      const char dum[2] = {0, 0};
      os.Write(dum,2);
      }
    return os;
    }
  friend std::ostream& operator<<(std::ostream& os, const VR& vr);

  operator VR::VRType() const { return VRField; }

private:
  // Internal function that map a VRType to an index in the VRStrings table
  static int GetIndex(VRType vr);
  VRType VRField;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const VR& val)
{
  _os << VR::GetVRString(val.VRField);
  return _os;
}

// Tells whether VR Type is ASCII or Binary
template<int T> struct TypeToEncoding;
// Convert from VR Type to real underlying type
template<int T> struct TypeToType;
#define TYPETOENCODING(type,rep, rtype)         \
  template<> struct TypeToEncoding<VR::type>    \
  { enum { Mode = VR::rep }; };                 \
  template<> struct TypeToType<VR::type>        \
  { typedef rtype Type; };

// TODO: Could be generated from XML file
TYPETOENCODING(AE,ASCII ,float)
TYPETOENCODING(AS,ASCII ,char)
TYPETOENCODING(AT,BINARY,Tag)
TYPETOENCODING(CS,ASCII ,float)
TYPETOENCODING(DA,ASCII ,float)
TYPETOENCODING(DS,ASCII ,float)
TYPETOENCODING(DT,ASCII ,float)
TYPETOENCODING(FL,BINARY,float)
TYPETOENCODING(FD,BINARY,double)
TYPETOENCODING(IS,ASCII ,float)
TYPETOENCODING(LO,ASCII ,float)
TYPETOENCODING(LT,ASCII ,float)
TYPETOENCODING(OB,BINARY,float)
TYPETOENCODING(OF,BINARY,float)
TYPETOENCODING(OW,BINARY,float)
TYPETOENCODING(PN,ASCII ,char*)
TYPETOENCODING(SH,ASCII ,float)
TYPETOENCODING(SL,BINARY,int32_t)
TYPETOENCODING(SQ,BINARY,float)
TYPETOENCODING(SS,BINARY,int16_t)
TYPETOENCODING(ST,ASCII ,float)
TYPETOENCODING(TM,ASCII ,float)
TYPETOENCODING(UI,ASCII ,float)
TYPETOENCODING(UL,BINARY,uint32_t)
TYPETOENCODING(UN,BINARY,float)
TYPETOENCODING(US,BINARY,uint16_t)
TYPETOENCODING(UT,BINARY,float)


} // end namespace gdcm

#endif //__gdcmVR_h

