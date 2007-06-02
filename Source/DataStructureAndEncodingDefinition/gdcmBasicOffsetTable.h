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
#include "gdcmFragment.h"
#include "gdcmTag.h"
//#include "gdcmSwapCode.h"

namespace gdcm
{
/**
 * \brief Class to represent an BasicOffsetTable
 * TODO: this is A fragment need to subclass from fragment
 */

class GDCM_EXPORT BasicOffsetTable : public DataElement
{
  template <typename TSwap> friend class IOSerialize;
public:
  BasicOffsetTable(const Tag &t = Tag(0), uint32_t const &vl = 0) : DataElement(t, vl), Offsets(0) {}
  friend std::ostream &operator<<(std::ostream &os, const BasicOffsetTable &val);

  void Clear() {
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

  BasicOffsetTable(BasicOffsetTable const &val):DataElement(val)
    {
    }
  BasicOffsetTable &operator=(BasicOffsetTable const &val)
    {
    }

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
    const ByteValue &bv = *(val.Offsets);
    os << bv;
    }

  return os;
}


} // end namespace gdcm

#endif //__gdcmBasicOffsetTable_h
