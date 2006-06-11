
#ifndef __gdcmImplicitDataElement_h
#define __gdcmImplicitDataElement_h

#include "gdcmDataElement.h"
#include "gdcmByteValue.h"

namespace gdcm
{
/**
 * \brief Class to represent an *Implicit VR* Data Element
 * \note bla
 */
class Value;
class GDCM_EXPORT ImplicitDataElement : public DataElement
{
public:
  ImplicitDataElement(const Tag& t = Tag(0), uint32_t const &vl = 0) : DataElement(t,vl),ValueField(0) {}
  ~ImplicitDataElement();

  friend std::ostream& operator<<(std::ostream& _os, const ImplicitDataElement &_val);

  Value const & GetValue() const { return *ValueField; }
  void SetValue(Value const & vl) { ValueField = const_cast<Value*>(&vl); }

  VL GetLength() const
    {
    assert( !ValueLengthField.IsUndefined() ); //FIXME
    return TagField.GetLength() + ValueLengthField.GetLength() + ValueLengthField;
    }

  IStream &Read(IStream& is);
  const OStream &Write(OStream& os) const;

private:
  Value* ValueField;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const ImplicitDataElement &val)
{
  const DataElement &de = val;
  os << de;
  if( val.ValueField )
    {
    const Value& v = *(val.ValueField);
    // could not get operator<< to work on references (no dynamic type)
    v.Print(os << "\t");
    }
  return os;
}

} // end namespace gdcm

#endif //__gdcmImplicitDataElement_h
