
#ifndef __gdcmExplicitDataElement_h
#define __gdcmExplicitDataElement_h

/**
 * \brief Class to represent a Data Element
 * Implicit / Explicit
 * \note bla
 */

#include "gdcmDataElement.h"
#include "gdcmIStream.h"
#include "gdcmOStream.h"
#include "gdcmVR.h"

namespace gdcm
{
// Data Element (Explicit)
class ExplicitDataElement : public DataElement
{
public:
  ExplicitDataElement() { ValueLengthField = 0; VRField = VR::INVALID; }

  friend std::ostream& operator<<(std::ostream& _os, const ExplicitDataElement &_val);
  friend gdcm::IStream& operator>>(gdcm::IStream& _os, ExplicitDataElement &_val);
  friend gdcm::OStream& operator<<(gdcm::OStream& _os, ExplicitDataElement &_val);

  uint32_t GetValueLength() { return ValueLengthField; }
  void SetValueLength(uint32_t vl) { ValueLengthField = vl; }

  uint32_t GetLength() { 
    assert( ValueLengthField != 0xFFFFFFFF );
    return ValueLengthField; }

  VR::VRType GetVR() { return VRField; }
  void SetVR(VR::VRType vr) { VRField = vr; }

private:
  // Value Representation
  VR::VRType VRField;
  // This is the value read from the file, might be different from the lenght of Value Field
  uint32_t ValueLengthField; // Can be 0xFFFFFFF
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const ExplicitDataElement &_val)
{
  _os << "VR=" << _val.VRField/* << ",VL=" << std::dec << _val.ValueLengthField*/;
  const DataElement &de = _val;
  _os << " " << de;
  return _os;
}

} // end namespace gdcm

#endif //__gdcmExplicitDataElement_h
