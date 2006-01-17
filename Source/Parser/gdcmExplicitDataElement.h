
#ifndef __gdcmExplicitDataElement_h
#define __gdcmExplicitDataElement_h

#include "gdcmDataElement.h"
//#include "gdcmDICOMIStream.h"
#include "gdcmDICOMOStream.h"
#include "gdcmVR.h"

namespace gdcm
{
// Data Element (Explicit)
/**
 * \brief Class to represent an *Explivit VR* Data Element
 * \note bla
 */
class GDCM_EXPORT ExplicitDataElement : public DataElement
{
public:
  ExplicitDataElement() { ValueLengthField = 0; VRField = VR::INVALID; }

  friend std::ostream& operator<<(std::ostream& _os, const ExplicitDataElement &_val);
//  friend DICOMIStream& operator>>(DICOMIStream& _os, ExplicitDataElement &_val);
  friend class DICOMIStream;
  friend DICOMOStream& operator<<(DICOMOStream& _os, const ExplicitDataElement &_val);

  uint32_t GetValueLength() { return ValueLengthField; }
  void SetValueLength(uint32_t vl) { ValueLengthField = vl; }

  VR::VRType GetVR() { return VRField; }
  void SetVR(VR::VRType vr) { VRField = vr; }

  uint32_t GetLength() { return ComputeLength(); }

  uint32_t GetLength() const { return ComputeLength(); }

protected:
  //DICOMIStream& Read(DICOMIStream &_os);
  DICOMOStream& Write(DICOMOStream &_os) const;

  uint32_t ComputeLength() const
    {
    assert( ValueLengthField != 0xFFFFFFFF ); //FIXME
    // Nice trick each time VR::GetLength() is 2 then Value Length is coded in 2
    //                                         4 then Value Length is coded in 4
    return DataElement::GetLength() + 2*VR::GetLength(VRField) + ValueLengthField;
    }

private:
  // Value Representation
  VR::VRType VRField;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const ExplicitDataElement &_val)
{
  _os << _val.TagField << " VR=" << _val.VRField;
  _os << ",VL=" << std::dec << _val.ValueLengthField
      << " ValueField=[" << _val.ValueField << "]";
  return _os;
}

} // end namespace gdcm

#endif //__gdcmExplicitDataElement_h
