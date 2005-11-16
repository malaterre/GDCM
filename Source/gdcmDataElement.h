
#ifndef __gdcmDataElement_h
#define __gdcmDataElement_h

/**
 * \brief Class to represent a Data Element
 * Implicit / Explicit
 * \note bla
 * \sea ExplicitDataElement ImplicitDataElement
 */

#include "gdcmType.h"
#include "gdcmTag.h"
#include "gdcmValue.h"
#include "gdcmIStream.h"

namespace gdcm
{
// Data Element
// Contains multiple fields:
// -> Tag (not store here since used as key)
// -> Optional VR
// -> ValueLength
// -> Value
class DataElement
{
public:
  DataElement() {}
  virtual ~DataElement() {}

  friend std::ostream& operator<<(std::ostream& _os, const DataElement &_val);
  friend gdcm::IStream& operator>>(gdcm::IStream& _os, DataElement &_val);

protected:
  Value ValueField;
  // Value could be NULL if we don't read it, therefore we need an offset
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const DataElement &_val)
{
  _os << "VF=" << _val.ValueField;
  return _os;
}
//-----------------------------------------------------------------------------
inline gdcm::IStream& operator>>(gdcm::IStream& _os, DataElement &_val)
{
  //FIXME... can we do the writting here instead of subclass ?
  (void)_val;
  assert( 0 );
  return _os;
}

} // end namespace gdcm

#endif //__gdcmDataElement_h
