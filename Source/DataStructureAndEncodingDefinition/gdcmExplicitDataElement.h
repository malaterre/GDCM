
#ifndef __gdcmExplicitDataElement_h
#define __gdcmExplicitDataElement_h

#include "gdcmDataElement.h"
#include "gdcmVR.h"

namespace gdcm
{
// Data Element (Explicit)
/**
 * \brief Class to represent an *Explivit VR* Data Element
 * \note bla
 */
class Value;
class GDCM_EXPORT ExplicitDataElement : public DataElement
{
public:
  ExplicitDataElement(const Tag& t = Tag(0), uint32_t const &vl = 0, const VR::VRType &vr = VR::INVALID) : DataElement(t,vl),VRField(vr) { }

  friend std::ostream& operator<<(std::ostream& _os, const ExplicitDataElement &_val);

  VR::VRType GetVR() const { return VRField; }
  void SetVR(VR::VRType const &vr) { VRField = vr; }

  void Read(std::istream& _is);
  void Write(std::ostream& _os) const;

private:
  // Value Representation
  VR::VRType VRField;
  Value* ValueField;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const ExplicitDataElement &_val)
{
  const DataElement &de = _val;
  _os << de;
  _os << _val.TagField << " VR=" << _val.VRField;
  return _os;
}

} // end namespace gdcm

#endif //__gdcmExplicitDataElement_h

