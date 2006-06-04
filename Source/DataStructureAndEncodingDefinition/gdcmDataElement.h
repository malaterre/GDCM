
#ifndef __gdcmDataElement_h
#define __gdcmDataElement_h

/**
 * \brief Class to represent a Data Element
 * Implicit / Explicit
 * \note
 * DATA ELEMENT: 
 * A unit of information as defined by a single entry in the data dictionary.
 * An encoded Information Object Definition (IOD) Attribute that is composed
 * of, at a minimum, three fields: a Data Element Tag, a Value Length, 
 * and a Value Field. For some specific Transfer Syntaxes, a Data Element
 * also contains a VR Field where the Value Representation of that Data 
 * Element is specified explicitly.
 * \see ExplicitDataElement ImplicitDataElement
 */

#include "gdcmTag.h"
#include "gdcmVL.h"

namespace gdcm
{
// Data Element
// Contains multiple fields:
// -> Tag
// -> Optional VR (Explicit Transfer Syntax)
// -> ValueLength
// -> Value
// TODO: This class SHOULD be pure virtual. I dont want a user
// to shoot himself in the foot.
class GDCM_EXPORT DataElement
{
public:
  DataElement(const Tag& t = Tag(0), const VL& vl = 0):TagField(t),ValueLengthField(vl) {}
  virtual ~DataElement() {}

  friend std::ostream& operator<<(std::ostream &_os, const DataElement &_val);

  const Tag& GetTag() const { return TagField; }
  void SetTag(const Tag &t) { TagField = t; }

  const VL& GetVL() const { return ValueLengthField; }
  void SetVL(const VL &vl) { ValueLengthField = vl; }

  bool IsUndefinedLength() const {
    return ValueLengthField.IsUndefined();
  }

  DataElement(const DataElement &_val)
    {
    if( this != &_val)
      {
      *this = _val;
      }
    }

  DataElement &operator=(const DataElement &_val)
    {
    TagField = _val.TagField;
    ValueLengthField = _val.ValueLengthField;
    return *this;
    }

  bool operator==(const DataElement &_de) const
    {
    return TagField == _de.TagField
      && ValueLengthField == _de.ValueLengthField;
    }

  IStream &Read(IStream &is) {
    if( TagField.Read(is) )
      {
      return ValueLengthField.Read(is);
      }
    return is;
    }

  const OStream &Write(OStream &os) const {
    if( TagField.Write(os) )
      {
      return ValueLengthField.Write(os);
      }
    return os;
    }

protected:
  Tag TagField;
  // This is the value read from the file, might be different from the length of Value Field
  VL ValueLengthField; // Can be 0xFFFFFFFF
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &os, const DataElement &val)
{
  os << "Tag: " << val.TagField << "\n";
  os << "Value Length: " << val.ValueLengthField << "\n"; 
  return os;
}

} // end namespace gdcm

#endif //__gdcmDataElement_h

