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
