
#ifndef __gdcmImplicitDataElement_h
#define __gdcmImplicitDataElement_h


#include "gdcmDataElement.h"

namespace gdcm
{
/**
 * \brief Class to represent a Data Element
 * Implicit / Explicit
 * \note bla
 */
class GDCM_EXPORT ImplicitDataElement : public DataElement
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
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const ImplicitDataElement &_val)
{
  _os << _val.TagField << " VL=" << std::dec << _val.ValueLengthField;
  return _os;
}

} // end namespace gdcm

#endif //__gdcmImplicitDataElement_h
