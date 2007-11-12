/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
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
#include "gdcmVR.h"
#include "gdcmByteValue.h"
#include "gdcmSmartPointer.h"

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
 *
 * Design:
 * # A DataElement in GDCM always store VL (Value Length) on a 32 bits integer even when VL is 16 bits
 * # A DataElement always store the VR even for Implicit TS, in which case VR is defaulted to VR::INVALID
 * # For Item start/end (See 0xfffe tags), Value is NULL
 *
 * \see ExplicitDataElement ImplicitDataElement
 */

class GDCM_EXPORT DataElement
{
public:
  DataElement(const Tag& t = Tag(0), const VL& vl = 0, const VR &vr = VR::INVALID):TagField(t),ValueLengthField(vl),VRField(vr),ValueField(0) {}

  friend std::ostream& operator<<(std::ostream &_os, const DataElement &_val);

  // Set/Get Tag
  const Tag& GetTag() const { return TagField; }
  void SetTag(const Tag &t) { TagField = t; }

  // Set/Get VL
  const VL& GetVL() const { return ValueLengthField; }
  void SetVL(const VL &vl) { ValueLengthField = vl; }

  // Set/Get VR
  VR const &GetVR() const { return VRField; }
  void SetVR(VR const &vr) { VRField = vr; }

  // Set/Get Value (bytes array, SQ of items, SQ of fragments):
  Value const &GetValue() const { return *ValueField; }
  void SetValue(Value const & vl) {
    //assert( ValueField == 0 );
    ValueField = &vl;
  }
  bool IsValueEmpty() const { return ValueField == 0; }

  // Helper:
  void SetByteValue(const char *array, VL length)
    {
    ByteValue *bv = new ByteValue(array,length);
    SetVL( length );
    SetValue( *bv );
    }

  // Helper:
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

  DataElement &operator=(const DataElement &de)
    {
    TagField = de.TagField;
    ValueLengthField = de.ValueLengthField;
    VRField = de.VRField;
    ValueField = de.ValueField; // Pointer copy
    return *this;
    }

  bool operator==(const DataElement &de) const
    {
    return TagField == de.TagField
      && ValueLengthField == de.ValueLengthField
      && VRField == de.VRField
      && ValueField == de.ValueField;
    }

  // The following fonctionalities are dependant on:
  // # The Transfer Syntax: Explicit or Implicit
  // # The Byte encoding: Little Endian / Big Endian

  /*
   * The following was inspired by a C++ idiom: Curiously Recurring Template Pattern
   * Ref: http://en.wikipedia.org/wiki/Curiously_Recurring_Template_Pattern
   * The typename TDE is typically a derived class *without* any data
   * while TSwap is a simple template parameter to achieve byteswapping (and allow factorization of
   * highly identical code)
   */
  template <typename TDE>
  VL GetLength() const {
    return static_cast<const TDE*>(this)->GetLength();
  }

  template <typename TDE, typename TSwap>
  std::istream &Read(std::istream &is) {
    return static_cast<TDE*>(this)->template Read<TSwap>(is);
  }

  template <typename TDE, typename TSwap>
  const std::ostream &Write(std::ostream &os) const {
    return static_cast<const TDE*>(this)->template Write<TSwap>(os);
  }

protected:
  Tag TagField;
  // This is the value read from the file, might be different from the length of Value Field
  VL ValueLengthField; // Can be 0xFFFFFFFF

  // Value Representation
  VR VRField;
  //typedef std::tr1::shared_ptr<gdcm::Value> ValuePtr;
  typedef SmartPointer<Value> ValuePtr;
  ValuePtr ValueField;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &os, const DataElement &val)
{
  os << "Tag: " << val.TagField;
  if( val.VRField != VR::INVALID ) // FIXME
    os << "\tVR=" << val.VRField;
  os << "\tVL: " << val.ValueLengthField;
  if( val.ValueField )
    {
    val.ValueField->Print( os << "\t" );
    }
  return os;
}

} // end namespace gdcm

#endif //__gdcmDataElement_h

