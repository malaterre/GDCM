
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
#include "gdcmDICOMIStream.h"
#include "gdcmDICOMOStream.h"

namespace gdcm
{
// Data Element
// Contains multiple fields:
// -> Tag (not store here since used as key)
// -> Optional VR
// -> ValueLength
// -> Value
// -> Store Offset, to further printing  ?
class GDCM_EXPORT DataElement
{
public:
  DataElement() {}
  virtual ~DataElement() {}

  friend std::ostream& operator<<(std::ostream &_os, const DataElement &_val);
  friend DICOMIStream& operator>>(DICOMIStream &_os, DataElement &_val);
  friend DICOMOStream& operator<<(DICOMOStream &_os, const DataElement &_val);

  const Tag& GetTag() const { return TagField; }
  void SetTag(const Tag &t) { TagField = t; }

  const Value &GetValue() const { return ValueField; }

  DataElement(const DataElement&_val)
    {
    if( this != &_val)
      {
      *this = _val;
      }
    }

  DataElement &operator=(const DataElement &_val)
    {
    TagField = _val.TagField;
    ValueField = _val.ValueField;
    return *this;
    }

  uint32_t GetLength() const
    {
    return TagField.GetLength();
    }

protected:
  Tag TagField;
  Value ValueField;
  // Value could be NULL if we don't read it, therefore we need an offset
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &_os, const DataElement &_val)
{
  _os << /*_val.TagField <<*/ " VF=" << _val.ValueField;
  return _os;
}
//-----------------------------------------------------------------------------
inline DICOMIStream& operator>>(DICOMIStream &_os, DataElement &_val)
{
  // Read Tag
  assert( !_os.eof() ); // FIXME
  if( !_os.Read(_val.TagField) ) return _os;
  return _os;
}

//-----------------------------------------------------------------------------
inline DICOMOStream& operator<<(DICOMOStream &_os, const DataElement &_val)
{
  // Write Tag
  _os.Write(_val.TagField);
  return _os;
}

} // end namespace gdcm

#endif //__gdcmDataElement_h
