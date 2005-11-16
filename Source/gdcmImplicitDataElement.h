
#ifndef __gdcmImplicitDataElement_h
#define __gdcmImplicitDataElement_h

/**
 * \brief Class to represent a Data Element
 * Implicit / Explicit
 * \note bla
 */

#include "gdcmDataElement.h"
#include "gdcmVR.h"

namespace gdcm
{
// Data Element (Implicit)
class ImplicitDataElement : public DataElement
{
public:
  ImplicitDataElement() { ValueLengthField = 0; }

  friend std::ostream& operator<<(std::ostream& _os, const ImplicitDataElement &_val);

  uint32_t GetValueLength() { return ValueLengthField; }
  void SetValueLength(uint32_t vl) { ValueLengthField = vl; }

private:
  // This is the value read from the file, might be different from the lenght of Value Field
  uint32_t ValueLengthField; // Can be 0xFFFFFFF
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const ImplicitDataElement &_val)
{
  _os << "VL=" << std::dec << _val.ValueLengthField;
  const DataElement &de = _val;
  _os << " " << de;
  return _os;
}

} // end namespace gdcm

#endif //__gdcmImplicitDataElement_h
