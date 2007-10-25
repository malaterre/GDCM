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

#ifndef __gdcmFragment_h
#define __gdcmFragment_h

#include "gdcmDataElement.h"
#include "gdcmSmartPointer.h"
#include "gdcmByteValue.h"

namespace gdcm
{
/**
 * \brief Class to represent an Fragment
 */

class GDCM_EXPORT Fragment : public DataElement
{
  template <typename TSwap> friend class IOSerialize;
public:
  Fragment(const Tag &t = Tag(0), uint32_t const &vl = 0) : DataElement(t, vl) , FragmentValue(0) { }
  friend std::ostream &operator<<(std::ostream &os, const Fragment &val);

  void Clear() {
    FragmentValue->Clear();
    }

//  template <typename TSwap>
//  IStream &Read(IStream &is);
//
//  template <typename TSwap>
//  OStream &Write(OStream &os) const;

  Value const &GetValue() const {
    return *FragmentValue;
  }

  VL GetLength() const {
    assert( !ValueLengthField.IsUndefined() );
    assert( !FragmentValue || FragmentValue->GetLength() == ValueLengthField );
    return TagField.GetLength() + ValueLengthField.GetLength() 
      + ValueLengthField;
  }

  Fragment(const Fragment &val):DataElement(val)
    {
    FragmentValue = val.FragmentValue;
    }
  Fragment &operator=(Fragment const &val)
    {
    FragmentValue = val.FragmentValue;
    return *this;
    }

  template <typename TSwap>
  IStream &Read(IStream &is)
    {
    // Superclass
    const Tag itemStart(0xfffe, 0xe000);
    const Tag seqDelItem(0xfffe,0xe0dd);
    if( !TagField.Read<TSwap>(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
    if( TagField != itemStart && TagField != seqDelItem )
      {
      // gdcm-JPEG-LossLess3a.dcm
      std::streampos pos = is.tellg();
      is.seekg( 0, std::ios::end );
      std::streampos end = is.tellg();
      assert( (long)(end-pos) == 4 );
      gdcmWarningMacro( "Broken file: " << (long)(end-pos)
        << " bytes were skipped at the end of file. Use at own risk." );
      // Pretend to end properly...
      TagField = Tag(0xfffe,0xe0dd);
      ValueLengthField = 0;
      // Make sure to clear the FragmentValue
      FragmentValue = new ByteValue;
      FragmentValue->SetLength( ValueLengthField );
      return is;
      }
#endif
    if( !Read(is,ValueLengthField) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    // Self
    ByteValue *bv = new ByteValue;
    bv->SetLength(ValueLengthField);
    if( !Read(is,*bv) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    FragmentValue = bv;
    return is;
    }


  template <typename TSwap>
  OStream &Write(OStream &os) const
  {
    const Tag itemStart(0xfffe, 0xe000);
    const Tag seqDelItem(0xfffe,0xe0dd);
    if( !Write(os,TagField) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    assert( TagField == itemStart
         || TagField == seqDelItem );
    if( !Write(os,ValueLengthField) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    // Self
    if( !Write(os,*(FragmentValue)) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    return os;
    }

 
private:
  typedef SmartPointer<ByteValue> ByteValuePtr;
  ByteValuePtr FragmentValue;
};
//-----------------------------------------------------------------------------
inline std::ostream &operator<<(std::ostream &os, const Fragment &val)
{
  os << "Tag: " << val.TagField;
  os << "\tVL: " << val.ValueLengthField;
  os << "\t" << *(val.FragmentValue);

  return os;
}


} // end namespace gdcm

#endif //__gdcmFragment_h
