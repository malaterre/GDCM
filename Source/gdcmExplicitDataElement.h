
#ifndef __gdcmExplicitDataElement_h
#define __gdcmExplicitDataElement_h

#include "gdcmDataElement.h"
#include "gdcmDICOMIStream.h"
#include "gdcmDICOMOStream.h"
#include "gdcmVR.h"

namespace gdcm
{
// Data Element (Explicit)
/**
 * \brief Class to represent a Data Element
 * Implicit / Explicit
 * \note bla
 */
class GDCM_EXPORT ExplicitDataElement : public DataElement
{
public:
  ExplicitDataElement() { ValueLengthField = 0; VRField = VR::INVALID; SequenceLength = 0; }

  friend std::ostream& operator<<(std::ostream& _os, const ExplicitDataElement &_val);
  friend DICOMIStream& operator>>(DICOMIStream& _os, ExplicitDataElement &_val);
  friend DICOMOStream& operator<<(DICOMOStream& _os, const ExplicitDataElement &_val);

  uint32_t GetValueLength() { return ValueLengthField; }
  void SetValueLength(uint32_t vl) { ValueLengthField = vl; }

  VR::VRType GetVR() { return VRField; }
  void SetVR(VR::VRType vr) { VRField = vr; }

  uint32_t GetLength() { return ComputeLength(); }

  uint32_t GetLength() const { return ComputeLength(); }

protected:
  uint32_t ComputeLength() const
    {
    assert( ValueLengthField != 0xFFFFFFFF ); //FIXME
    // Nice trick each time VR::GetLength() is 2 then Value Length is coded in 2
    //                                         4 then Value Length is coded in 4
    if( ValueLengthField != 0xFFFFFFFF )
      return DataElement::GetLength() + 2*VR::GetLength(VRField) + ValueLengthField;
    else
      return DataElement::GetLength() + 2*VR::GetLength(VRField) + SequenceLength;
    }

private:
  // Value Representation
  VR::VRType VRField;

  // This is set if ValueLengthField == 0xFFFFFFFF
  uint32_t SequenceLength;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const ExplicitDataElement &_val)
{
  _os << _val.TagField << " VR=" << _val.VRField;
  if(_val.ValueLengthField == 0xFFFFFFFF )
    _os << ",VL=" << std::dec << _val.ValueLengthField;
  else
    _os << ",VL=" << std::dec << _val.SequenceLength;
  return _os;
}

} // end namespace gdcm

#endif //__gdcmExplicitDataElement_h
