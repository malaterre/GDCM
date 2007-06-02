/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __gdcmDataElement_h
#define __gdcmDataElement_h

#include "gdcmTag.h"
#include "gdcmVL.h"

namespace gdcm
{
// Data Element
// Contains multiple fields:
// -> Tag
// -> Optional VR (Explicit Transfer Syntax)
// -> ValueLength
// -> Value
// TODO: This class SHOULD be pure virtual. I dont want a user
// to shoot himself in the foot.
//class Value;
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

class GDCM_EXPORT DataElement
{
  template <typename TSwap> friend class IOSerialize;
public:
  DataElement(const Tag& t = Tag(0), const VL& vl = 0):TagField(t),ValueLengthField(vl) {}
//  virtual ~DataElement() {}

  friend std::ostream& operator<<(std::ostream &_os, const DataElement &_val);

  const Tag& GetTag() const { return TagField; }
  void SetTag(const Tag &t) { TagField = t; }

  const VL& GetVL() const { return ValueLengthField; }
  void SetVL(const VL &vl) { ValueLengthField = vl; }

//  virtual VL GetLength() const {
//    abort();
//    return 0;
//  }

  bool IsUndefinedLength() const {
    return ValueLengthField.IsUndefined();
  }

  DataElement(const DataElement &_val)
    {
    if( this != &_val)
      {
      *this = _val;
      }
    }

  DataElement &operator=(const DataElement &_val)
    {
    TagField = _val.TagField;
    ValueLengthField = _val.ValueLengthField;
    return *this;
    }

  bool operator==(const DataElement &_de) const
    {
    return TagField == _de.TagField
      && ValueLengthField == _de.ValueLengthField;
    }

//  template <typename TSwap>
//  IStream &Read(IStream &is) {
//    if( !TagField.Read<TSwap>(is) )
//      {
//      abort();
//      }
//    if( !ValueLengthField.Read<TSwap>(is) )
//      {
//      abort();
//      }
//    return is;
//    }
//
//  template <typename TSwap>
//  const OStream &Write(OStream &os) const {
//    if( TagField.Write<TSwap>(os) )
//      {
//      return ValueLengthField.Write<TSwap>(os);
//      }
//    return os;
//    }

  //virtual Value const & GetValue() const = 0;
  
protected:
  Tag TagField;
  // This is the value read from the file, might be different from the length of Value Field
  VL ValueLengthField; // Can be 0xFFFFFFFF
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &os, const DataElement &val)
{
  os << "Tag: " << val.TagField;
  os << "\tVL: " << val.ValueLengthField;
  return os;
}

} // end namespace gdcm

#endif //__gdcmDataElement_h

