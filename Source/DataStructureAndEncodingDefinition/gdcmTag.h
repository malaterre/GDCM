/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __gdcmTag_h
#define __gdcmTag_h

#include "gdcmTypes.h"

#include <iostream>
#include <iomanip>

namespace gdcm
{

/**
 * \brief Class to represent a DICOM Data Element (Attribute) Tag (Group, Element).
 * Basically an uint32_t which can also be expressed as two uint16_t (group and element)
 * \note
 * DATA ELEMENT TAG: 
 * A unique identifier for a Data Element composed of an ordered pair of 
 * numbers (a Group Number followed by an Element Number).
 * GROUP NUMBER: The first number in the ordered pair of numbers that makes
 * up a Data Element Tag.
 * ELEMENT NUMBER: The second number in the ordered pair of numbers that
 * makes up a Data Element Tag.
 */
class GDCM_EXPORT Tag
{
public:
  /// \brief Constructor with 2*uint16_t 
  Tag(uint16_t group, uint16_t element) {
    ElementTag.tags[0] = group; ElementTag.tags[1] = element;
  }
  /// \brief Constructor with 1*uint32_t  
  /// Prefer the cstor that takes two uint16_t
  Tag(uint32_t tag = 0) {
    SetElementTag(tag);
  } 

  friend std::ostream& operator<<(std::ostream &_os, const Tag &_val);

  /// \brief Returns the 'Group number' of the given Tag
  uint16_t GetGroup() const { return ElementTag.tags[0]; }
  /// \brief Returns the 'Element number' of the given Tag  
  uint16_t GetElement() const { return ElementTag.tags[1]; }
  /// \brief Sets the 'Group number' of the given Tag  
  void SetGroup(uint16_t group) { ElementTag.tags[0] = group; }
  /// \brief Sets the 'Element number' of the given Tag
  void SetElement(uint16_t element) { ElementTag.tags[1] = element; }
  /// \brief Sets the 'Group number' & 'Element number' of the given Tag
  void SetElementTag(uint16_t group, uint16_t element) {
    ElementTag.tags[0] = group; ElementTag.tags[1] = element;
  }

  /// \brief Returns the full tag value of the given Tag
  uint32_t GetElementTag() const { 
#ifndef GDCM_WORDS_BIGENDIAN	  
    return (ElementTag.tag<<16) | (ElementTag.tag>>16);
#else
    return ElementTag.tag;
#endif
  }
 
  /// \brief Sets the full tag value of the given Tag
  void SetElementTag(uint32_t tag) {
#ifndef GDCM_WORDS_BIGENDIAN
    tag = ( (tag<<16) | (tag>>16) );
#endif
    ElementTag.tag = tag;
  }

  // \brief Returns the Group or Element of the given Tag, depending on id (0/1)
  const uint16_t &operator[](const unsigned int &_id) const
    {
    assert(_id<2);
    return ElementTag.tags[_id];
    }
  // \brief Returns the Group or Element of the given Tag, depending on id (0/1)    
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

  // DICOM Standard expects the Data Element to be sorted by Tags
  // All other comparison can be constructed from this one and operator ==
  // FIXME FIXME FIXME TODO
  // the following is pretty dumb. Since we have control over who is group
  // and who is element, we should reverse them in little endian and big endian case
  // since what we really want is fast comparison and not garantee that group is in #0
  // ...
  bool operator<(const Tag &_val) const
    {
#ifndef GDCM_WORDS_BIGENDIAN
    if( ElementTag.tags[0] < _val.ElementTag.tags[0] )
      return true;
    if( ElementTag.tags[0] == _val.ElementTag.tags[0]
     && ElementTag.tags[1] <  _val.ElementTag.tags[1] )
      return true;
    return false;
#else
     // Plain comparison is enough!
     return ( ElementTag.tag < _val.ElementTag.tag );
#endif
   }      

  Tag(const Tag &_val)
    {
    ElementTag.tag = _val.ElementTag.tag;
    }
  // Should be always true
  uint32_t GetLength() const { return 4; }

  // STANDARD DATA ELEMENT: A Data Element defined in the DICOM Standard,
  // and therefore listed in the DICOM Data Element Dictionary in PS 3.6.
  // Is the Tag from the Public dict...well the implementation is buggy
  // it does not prove the element is indeed in the dict...
  bool IsPublic() const { return !(ElementTag.tags[0] % 2); }

  // PRIVATE DATA ELEMENT: Additional Data Element, defined by an 
  // implementor, to communicate information that is not contained in 
  // Standard Data Elements. Private Data elements have odd Group Numbers.
  bool IsPrivate() const { return !IsPublic(); }

  //-----------------------------------------------------------------------------
  template <typename TSwap>
  std::istream &Read(std::istream &is)
    {
    is.read(ElementTag.bytes, 4);
    TSwap::SwapArray(ElementTag.tags, 2);
    return is;
    }

  template <typename TSwap>
  const std::ostream &Write(std::ostream &os) const
    {
    uint16_t copy[2];
    copy[0]= ElementTag.tags[0];
    copy[1]= ElementTag.tags[1];
    TSwap::SwapArray(copy, 2);
    return os.write((char*)(&copy), 4);
    }

  // Private Creator Data Element
  Tag GetPrivateCreator() const
    {
    // See PS 3.5 - 7.8.1 PRIVATE DATA ELEMENT TAGS
    // eg: 0x1234,0x1425 -> 0x1234,0x0014
    assert( IsPrivate() );
    Tag r = *this;
    r.SetElement( GetElement() >> 8 );
    return r;
    }

  // Returns if tag is a Private Creator (xxxx,00yy), where xxxx is odd number
  bool IsPrivateCreator() const
    {
    return IsPrivate() && GetElement() > 0xFF;
    }

  // e.g 6002,3000 belong to groupXX: 6000,3000
  bool IsGroupXX(const Tag &t) const
    {
    if( t.GetElement() == GetElement() )
      {
      if( t.IsPrivate() ) return false;
      uint16_t group = (GetGroup() >> 8 ) << 8;
      return group == t.GetGroup();
      }
    return false;
    }

  // This is a highly user oriented function, the string should be formated as:
  // 1234,5678 to specify the tag (0x1234,0x5678)
  // The notation comes from the DICOM standard, and is handy to use from a command line
  // program
  void ReadFromCommaSeparatedString(const char *str);

private:
  union { uint32_t tag; uint16_t tags[2]; char bytes[4]; } ElementTag;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &_os, const Tag &_val)
{
  _os.setf( std::ios::right);
  _os << std::hex << '(' << std::setw( 4 ) << std::setfill( '0' )
    << _val[0] << ',' << std::setw( 4 ) << std::setfill( '0' )
    << _val[1] << ')' << std::setfill( ' ' ) << std::dec;
  return _os;
}

} // end namespace gdcm

#endif //__gdcmTag_h

