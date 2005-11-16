
#ifndef __gdcmDataElement_h
#define __gdcmDataElement_h

/**
 * \brief Class to represent a Data Element
 * Implicit / Explicit
 * \note bla
 */

#include "gdcmType.h"
#include "gdcmTag.h"
#include "gdcmValueField.h"

namespace gdcm
{
// Data Element
class DataElement
{
public:
  DataElement() { ValueLength = 0; }

  friend std::ostream& operator<<(std::ostream& _os, const DataElement &_val);

//  VRValueLenght GetVRValueLength() const { return

//  DataElement &operator=(const DataElement &_val)
//    {
//    return *this;
//    }

//  bool operator==(const DataElement &_val) const
//    {
//    //return ElementTag.tag == _val.ElementTag.tag;
//    }
//  bool operator!=(const DataElement &_val) const
//    {
//    //return ElementTag.tag != _val.ElementTag.tag;
//    }

//  DataElement(const DataElement &_val)
//    {
//    //ElementTag.tag = _val.ElementTag.tag;
//    }

private:
  ValueField Value;
  // Value could be NULL if we don't read it, therefore we need an offset
  // This is the value read from the file, might be different from the lenght of Value Field
  uint32_t ValueLength; // Can be 0xFFFFFFF
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const DataElement &_val)
{
  (void)_val;
  return _os;
}

} // end namespace gdcm

#endif //__gdcmDataElement_h
