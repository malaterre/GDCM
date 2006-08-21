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

#ifndef __gdcmBasicOffsetTable_h
#define __gdcmBasicOffsetTable_h

#include "gdcmDataElement.h"
#include "gdcmDataSet.h"
#include "gdcmSwapCode.h"

namespace gdcm
{
/**
 * \brief Class to represent an BasicOffsetTable
 * TODO: this is A fragment need to subclass from fragment
 */

class GDCM_EXPORT BasicOffsetTable : public DataElement
{
public:
  BasicOffsetTable(const Tag &t = Tag(0), uint32_t const &vl = 0) : DataElement(t, vl), Offsets(0) {}
  friend std::ostream &operator<<(std::ostream &os, const BasicOffsetTable &val);

  void Clear() {
    }

  IStream &Read(IStream &is) {
    // Superclass 
    const Tag itemStart(0xfffe, 0xe000);
    const Tag seqDelItem(0xfffe,0xe0dd);
    if( !TagField.Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    assert( TagField == itemStart );
    if( !ValueLengthField.Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    // Self
    Offsets = new ByteValue;
    Offsets->SetLength(ValueLengthField);
    if( !Offsets->Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    return is;
    }

  OStream &Write(OStream &os) const {
    // Superclass 
    const Tag itemStart(0xfffe, 0xe000);
    const Tag seqDelItem(0xfffe,0xe0dd);
    if( !TagField.Write(os) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    assert( TagField == itemStart );
    if( !ValueLengthField.Write(os) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    // Self
    if( !Offsets->Write(os) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    return os;
    }

  Value const &GetValue() const {
    return *Offsets;
  }

  VL GetLength() const {
    assert( !ValueLengthField.IsUndefined() );
    assert( !Offsets || Offsets->GetLength() == ValueLengthField );
    return TagField.GetLength() + ValueLengthField.GetLength() 
      + ValueLengthField;
  }

  //BasicOffsetTable(BasicOffsetTable const &val):DataElement(val)
  //  {
  //  NestedDataSet = val.NestedDataSet;
  //  }

private:
  typedef SmartPointer<ByteValue> ByteValuePtr;
  ByteValuePtr Offsets;
};
//-----------------------------------------------------------------------------
inline std::ostream &operator<<(std::ostream &os, const BasicOffsetTable &val)
{
  os << " BasicOffsetTable Length=" << val.ValueLengthField << std::endl;
  if( val.Offsets )
    {
    os << *(val.Offsets);
    }

  return os;
}


} // end namespace gdcm

#endif //__gdcmBasicOffsetTable_h
