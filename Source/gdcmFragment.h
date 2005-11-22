
#ifndef __gdcmFragment_h
#define __gdcmFragment_h

/**
 * \brief Class to represent a Fragment of Pixel Data
 * \note bla
 */

#include "gdcmType.h"
#include <iostream>
#include <iomanip>

namespace gdcm
{
// Pixel Data Fragment
class Fragment
{
public:
  Fragment() { }

  friend std::ostream& operator<<(std::ostream& _os, const Fragment &_val);
  //friend DICOMIStream& operator>>(DICOMIStream& _os, Fragment &_val);
  //friend DICOMOStream& operator<<(DICOMOStream& _os, Fragment &_val);

  uint16_t GetGroup() const { return ElementFragment.tags[0]; }
  uint16_t GetElement() const { return ElementFragment.tags[1]; }
  void SetGroup(uint16_t group) { ElementFragment.tags[0] = group; }
  void SetElement(uint16_t element) { ElementFragment.tags[1] = element; }

  uint32_t GetElementFragment() const { return ElementFragment.tag; }
  //void SetElementFragment(uint16_t group, uint16_t element) { ElementFragment.tags[0] = group; ElementFragment.tags[1] = element; }
  void SetElementFragment(uint32_t tag) { ElementFragment.tag = tag; }

  const uint16_t &operator[](const unsigned int &_id) const
    {
    assert(_id<2);
    return ElementFragment.tags[_id];
    }
  const uint16_t &operator[](const unsigned int &_id)
    {
    assert(_id<2);
    return ElementFragment.tags[_id];
    }

  Fragment &operator=(const Fragment &_val)
    {
    ElementFragment.tag = _val.ElementFragment.tag;
    return *this;
    }

  bool operator==(const Fragment &_val) const
    {
    return ElementFragment.tag == _val.ElementFragment.tag;
    }
  bool operator!=(const Fragment &_val) const
    {
    return ElementFragment.tag != _val.ElementFragment.tag;
    }
  // DICOM Standart expect the Data Element to be sorted by Fragments
  // All other comparison can be constructed from this one and operator ==
  bool operator<(const Fragment &_val) const
    {
    if( ElementFragment.tags[0] < _val.ElementFragment.tags[0] )
      return true;
    if( ElementFragment.tags[0] == _val.ElementFragment.tags[0]
     && ElementFragment.tags[1] <  _val.ElementFragment.tags[1] )
      return true;
    return false;
    }

  Fragment(const Fragment &_val)
    {
    ElementFragment.tag = _val.ElementFragment.tag;
    }
  // Should be always true
  uint32_t GetLength() { return 8; }

private:
  //uint16_t ElementFragment[2]; // Group, Element
  union { uint32_t tag; uint16_t tags[2]; } ElementFragment;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const Fragment &_val)
{
  _os.setf( std::ios::right);
  _os << std::hex << std::setw( 4 ) << std::setfill( '0' )
    << _val.ElementFragment.tags[0] << ',' << std::setw( 4 ) << std::setfill( '0' )
    << _val.ElementFragment.tags[1] << std::setfill( ' ' ) << std::dec;
  return _os;
}

} // end namespace gdcm

#endif //__gdcmFragment_h
