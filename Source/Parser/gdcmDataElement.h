
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

#include "gdcmType.h"
#include "gdcmTag.h"
#include "gdcmValue.h"
#include "gdcmDICOMOStream.h"

namespace gdcm
{
// Data Element
// Contains multiple fields:
// -> Tag
// -> Optional VR (Explicit Transfer Syntax)
// -> ValueLength
// -> Value
class GDCM_EXPORT DataElement
{
public:
  DataElement() { ValueLengthField = 0; }
  virtual ~DataElement() {}

  friend std::ostream& operator<<(std::ostream &_os, const DataElement &_val);
  //friend DICOMIStream& operator>>(DICOMIStream &_os, DataElement &_val);
  friend class DICOMIStream;
  friend DICOMOStream& operator<<(DICOMOStream &_os, const DataElement &_val);

  const Tag& GetTag() const { return TagField; }
  void SetTag(const Tag &t) { TagField = t; }

  const Value &GetValue() const { return ValueField; }
//  virtual uint32_t GetLength();
//  virtual uint32_t GetLength();

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
  //DICOMIStream& Read(DICOMIStream &) { abort(); };

  Tag TagField;
  Value ValueField;
  // Value could be NULL if we don't read it, therefore we need an offset
  // This is the value read from the file, might be different from the length of Value Field
  uint32_t ValueLengthField; // Can be 0xFFFFFFFF
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &_os, const DataElement &_val)
{
  _os << _val.TagField << " VLgt=" << _val.ValueLengthField ; 
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
