
#ifndef __gdcmImplicitDataElement_h
#define __gdcmImplicitDataElement_h

/**
 * \brief Class to represent a Data Element
 * Implicit / Explicit
 * \note bla
 */

#include "gdcmDataElement.h"

namespace gdcm
{
// Data Element (Implicit)
class ImplicitDataElement : public DataElement
{
public:
  ImplicitDataElement() { ValueLengthField = 0; }

  friend std::ostream& operator<<(std::ostream& _os, const ImplicitDataElement &_val);
  friend DICOMIStream& operator>>(DICOMIStream& _os, ImplicitDataElement &_val);
  friend DICOMOStream& operator<<(DICOMOStream& _os, const ImplicitDataElement &_val);

  uint32_t GetValueLength() const { return ValueLengthField; }
  void SetValueLength(uint32_t vl) { ValueLengthField = vl; }

//  ImplicitDataElement(const ImplicitDataElement &_val)
//    {
//    }

  ImplicitDataElement &operator=(const ImplicitDataElement &_val)
    {
    (void)_val;
    abort();
    }

  uint32_t GetLength() const
    {
    //assert( ValueLengthField != 0xFFFFFFFF ); //FIXME
    return DataElement::GetLength() + sizeof(ValueLengthField) + ValueLengthField;
    }

private:
  // This is the value read from the file, might be different from the lenght of Value Field
  uint32_t ValueLengthField; // Can be 0xFFFFFFF
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const ImplicitDataElement &_val)
{
  _os << _val.TagField << " VL=" /* << "VL= " << std::dec << _val.ValueLengthField*/;
  const DataElement &de = _val;
  _os << " " << de;
  return _os;
}

} // end namespace gdcm

#endif //__gdcmImplicitDataElement_h
