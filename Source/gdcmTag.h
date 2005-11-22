
#ifndef __gdcmTag_h
#define __gdcmTag_h

/**
 * \brief Class to represent a Data Element Tag (Group, Element).
 * Basically an uint32_t or expressad as two uint16_t (group and element)
 * \note bla
 */

#include "gdcmType.h"
//#include "gdcmDICOMOStream.h"
//#include "gdcmDICOMIStream.h"
#include <iostream>
#include <iomanip>

namespace gdcm
{
// Data Element Tag
class Tag
{
  friend class DICOMIStream;
  friend class DICOMOStream;
public:
  Tag() { ElementTag.tag = 0; }
  Tag(uint32_t tag) { ElementTag.tag = tag; }
  Tag(uint16_t group, uint16_t element) { ElementTag.tags[0] = group; ElementTag.tags[1] = element; }

  friend std::ostream& operator<<(std::ostream& _os, const Tag &_val);
  //friend DICOMIStream& operator>>(DICOMIStream& _os, Tag &_val);
  //friend DICOMOStream& operator<<(DICOMOStream& _os, Tag &_val);

  uint16_t GetGroup() const { return ElementTag.tags[0]; }
  uint16_t GetElement() const { return ElementTag.tags[1]; }
  void SetGroup(uint16_t group) { ElementTag.tags[0] = group; }
  void SetElement(uint16_t element) { ElementTag.tags[1] = element; }

  uint32_t GetElementTag() const { return ElementTag.tag; }
  //void SetElementTag(uint16_t group, uint16_t element) { ElementTag.tags[0] = group; ElementTag.tags[1] = element; }
  void SetElementTag(uint32_t tag) { ElementTag.tag = tag; }

  const uint16_t &operator[](const unsigned int &_id) const
    {
    assert(_id<2);
    return ElementTag.tags[_id];
    }
  const uint16_t &operator[](const unsigned int &_id)
    {
    assert(_id<2);
    return ElementTag.tags[_id];
    }

  Tag &operator=(const Tag &_val)
    {
    ElementTag.tag = _val.ElementTag.tag;
    return *this;
    }

  bool operator==(const Tag &_val) const
    {
    return ElementTag.tag == _val.ElementTag.tag;
    }
  bool operator!=(const Tag &_val) const
    {
    return ElementTag.tag != _val.ElementTag.tag;
    }
  // DICOM Standart expect the Data Element to be sorted by Tags
  // All other comparison can be constructed from this one and operator ==
  bool operator<(const Tag &_val) const
    {
    if( ElementTag.tags[0] < _val.ElementTag.tags[0] )
      return true;
    if( ElementTag.tags[0] == _val.ElementTag.tags[0]
     && ElementTag.tags[1] <  _val.ElementTag.tags[1] )
      return true;
    return false;
    }

  Tag(const Tag &_val)
    {
    ElementTag.tag = _val.ElementTag.tag;
    }
  // Should be always true
  uint32_t GetLength() const { return 8; }

private:
  //uint16_t ElementTag[2]; // Group, Element
  union { uint32_t tag; uint16_t tags[2]; } ElementTag;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const Tag &_val)
{
  _os.setf( std::ios::right);
  _os << std::hex << std::setw( 4 ) << std::setfill( '0' )
    << _val.ElementTag.tags[0] << ',' << std::setw( 4 ) << std::setfill( '0' )
    << _val.ElementTag.tags[1] << std::setfill( ' ' ) << std::dec;
  return _os;
}

} // end namespace gdcm

#endif //__gdcmTag_h
