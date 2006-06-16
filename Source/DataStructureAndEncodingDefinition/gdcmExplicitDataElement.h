
#ifndef __gdcmExplicitDataElement_h
#define __gdcmExplicitDataElement_h

#include "gdcmDataElement.h"
#include "gdcmVR.h"
#include "gdcmSwapCode.h"
#include "gdcmValue.h"

//#include <tr1/memory>

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
    DataElement(t,vl),VRField(vr),ValueField() { }
  ~ExplicitDataElement();

  friend std::ostream& operator<<(std::ostream& _os, const ExplicitDataElement &_val);

  VR const &GetVR() const { return VRField; }
  void SetVR(VR const &vr) { VRField = vr; }

  Value const &GetValue() const { return *ValueField; }
  void SetValue(Value const & vl) {
    //assert( ValueField == 0 );
    ValueField = const_cast<Value*>(&vl);
  }

  VL GetLength() const {
    assert( ValueLengthField != 0xFFFFFFFF ); //FIXME
    // Nice trick each time VR::GetLength() is 2 then Value Length is coded in 2
    //                                         4 then Value Length is coded in 4
    return TagField.GetLength() + 2*VRField.GetLength() + ValueLengthField;
  }

  IStream &Read(IStream& is);
  const OStream &Write(OStream& _os) const;

  ExplicitDataElement(ExplicitDataElement const & val):DataElement(val)
    {
    //assert( val.ValueField );
    VRField    = val.VRField;
    ValueField = val.ValueField;
    // FIXME: Invalidate old pointer
    //const_cast<ExplicitDataElement&>(val).ValueField = 0;
    }

private:
  // Value Representation
  VR VRField;
  //typedef std::tr1::shared_ptr<gdcm::Value> ValuePtr;
  Value *ValueField;
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

