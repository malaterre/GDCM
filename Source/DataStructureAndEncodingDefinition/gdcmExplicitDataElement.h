
#ifndef __gdcmExplicitDataElement_h
#define __gdcmExplicitDataElement_h

#include "gdcmDataElement.h"

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
  ExplicitDataElement() { VRField = VR::INVALID; }

  friend std::ostream& operator<<(std::ostream& _os, const ExplicitDataElement &_val);

  VR::VRType GetVR() const { return VRField; }
  void SetVR(VR::VRType vr) { VRField = vr; }

  void Read(std::istream& _is);
  void Write(std::ostream& _os) const;

private:
  // Value Representation
  VR::VRType VRField;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const ExplicitDataElement &_val)
{
  DataElement &de = _val;
  _os << de;
  _os << _val.TagField << " VR=" << _val.VRField;
  return _os;
}

} // end namespace gdcm

#endif //__gdcmExplicitDataElement_h

