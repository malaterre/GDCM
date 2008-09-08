/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __gdcmBasicOffsetTable_h
#define __gdcmBasicOffsetTable_h

#include "gdcmDataElement.h"
#include "gdcmTag.h"

namespace gdcm
{
/**
 * \brief Class to represent an BasicOffsetTable
 * TODO: this is A fragment need to subclass from fragment
 */

class GDCM_EXPORT BasicOffsetTable : public DataElement
{
//protected:
//  void SetTag(const Tag &t);
public:
  BasicOffsetTable(const Tag &t = Tag(0xfffe, 0xe000), VL const &vl = 0) : DataElement(t, vl) {}
  friend std::ostream &operator<<(std::ostream &os, const BasicOffsetTable &val);

  VL GetLength() const {
    assert( !ValueLengthField.IsUndefined() );
    assert( !ValueField || ValueField->GetLength() == ValueLengthField );
    return TagField.GetLength() + ValueLengthField.GetLength() 
      + ValueLengthField;
  }

  template <typename TSwap>
  std::istream &Read(std::istream &is) {
    // Superclass 
    const Tag itemStart(0xfffe, 0xe000);
    const Tag seqDelItem(0xfffe,0xe0dd);
    if( !TagField.Read<TSwap>(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    assert( TagField == itemStart );
    if( !ValueLengthField.Read<TSwap>(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    // Self
    SmartPointer<ByteValue> bv = new ByteValue;
    //ValueField = new ByteValue;
    bv->SetLength(ValueLengthField);
    if( !bv->Read<TSwap>(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    ValueField = bv;
    return is;
    }

  template <typename TSwap>
  std::ostream &Write(std::ostream &os) const {
    // Superclass 
    const Tag itemStart(0xfffe, 0xe000);
    const Tag seqDelItem(0xfffe,0xe0dd);
    if( !TagField.Write<TSwap>(os) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    assert( TagField == itemStart );
    if( !ValueLengthField.Write<TSwap>(os) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    if( ValueLengthField )
      {
      // Self
      const ByteValue *bv = dynamic_cast<const ByteValue*>(&*ValueField);
      assert( bv );
      //if( !ValueField->Write<TSwap>(os) )
      if( !bv->Write<TSwap>(os) )
        {
        assert(0 && "Should not happen");
        return os;
        }
      }
    return os;
    }

private:
};
//-----------------------------------------------------------------------------
inline std::ostream &operator<<(std::ostream &os, const BasicOffsetTable &val)
{
  os << " BasicOffsetTable Length=" << val.ValueLengthField << std::endl;
  if( val.ValueField )
    {
    const ByteValue *bv = val.GetByteValue();
    assert( bv );
    os << *bv;
    }

  return os;
}


} // end namespace gdcm

#endif //__gdcmBasicOffsetTable_h
