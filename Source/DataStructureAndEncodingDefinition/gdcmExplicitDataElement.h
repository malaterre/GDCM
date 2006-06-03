
#ifndef __gdcmExplicitDataElement_h
#define __gdcmExplicitDataElement_h

#include "gdcmDataElement.h"
#include "gdcmVR.h"
#include "gdcmSwapCode.h"

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
  ExplicitDataElement(const Tag& t = Tag(0), uint32_t const &vl = 0,
                      const VR& vr = VR::INVALID ) : 
    DataElement(t,vl),VRField(vr),ValueField(0) { }
  ~ExplicitDataElement();

  friend std::ostream& operator<<(std::ostream& _os, const ExplicitDataElement &_val);

  VR const &GetVR() const { return VRField; }
  void SetVR(VR const &vr) { VRField = vr; }

  std::istream &Read(std::istream& is,
    SwapCode const &sc = SwapCode::LittleEndian);
  const std::ostream &Write(std::ostream& _os,
    SwapCode const &sc = SwapCode::LittleEndian) const;

private:
  // Value Representation
  VR VRField;
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

