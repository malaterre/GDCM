
#ifndef __gdcmExplicitDataElement_h
#define __gdcmExplicitDataElement_h

#include "gdcmDataElement.h"
#include "gdcmVR.h"
#include "gdcmSwapCode.h"
#include "gdcmValue.h"

namespace gdcm
{
// Data Element (Explicit)
/**
 * \brief Class to represent an *Explivit VR* Data Element
 * \note bla
 */
//class Value; // FIXME
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

  Value const &GetValue() const { return *ValueField; }
  void SetValue(Value const & vl) { ValueField = const_cast<Value*>(&vl); }

  IStream &Read(IStream& is);
  const OStream &Write(OStream& _os) const;

private:
  // Value Representation
  VR VRField;
  Value* ValueField;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const ExplicitDataElement & val)
{
  os << "Tag: " << val.TagField;
  os << "\tVR=" << val.VRField;
  os << "\tVL: " << val.ValueLengthField;
  if( val.ValueField )
    {
    val.ValueField->Print( os << "\t" );
    }
  return os;
}

} // end namespace gdcm

#endif //__gdcmExplicitDataElement_h

