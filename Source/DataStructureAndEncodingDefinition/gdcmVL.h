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
#ifndef __gdcmVL_h
#define __gdcmVL_h

#include "gdcmTypes.h"
#include "gdcmSwapCode.h"
#include "gdcmByteSwap.txx"

#include "gdcmIStream.h"
#include "gdcmOStream.h"

#include <iostream>

/* \brief Value Length
 * \warning this is a 4bytes value ! Do not try to use it for 2bytes value
 * length
*/
namespace gdcm
{

class GDCM_EXPORT VL
{
public:
  VL(uint32_t vl = 0) : ValueLength(vl) { }

  bool IsOdd() const {
    return ValueLength % 2;
  }
  bool IsUndefined() const {
    return ValueLength == 0xFFFFFFFF;
  }

  VL& operator+=(VL const &vl) {
    ValueLength += vl.ValueLength;
    return *this;
  }
  VL& operator++() {
    ++ValueLength;
    return *this;
  }
  VL operator++(int) {
    uint32_t tmp(ValueLength);
    ++ValueLength;
    return tmp;
  }

  operator uint32_t () const { return ValueLength; }

  VL GetLength() const {
    return 4;
  }

  friend std::ostream& operator<<(std::ostream& os, const VL& vl);
  //TODO
  //friend std::istream& operator>>(std::istream& is, VL& n);

  IStream &Read(IStream &is)
    {
    is.Read((char*)(&ValueLength), 4);
    ByteSwap<uint32_t>::SwapFromSwapCodeIntoSystem(ValueLength,
      is.GetSwapCode());
    return is;
    }

  template<typename T>
  const OStream &WriteT(OStream &os) const
    {
    T copy = ValueLength;
#ifndef GDCM_WRITE_ODD_LENGTH
    if( !IsUndefined() && IsOdd() )
      {
      ++copy;
      }
#endif
    ByteSwap<T>::SwapFromSwapCodeIntoSystem(copy,
      os.GetSwapCode());
    return os.Write((char*)(&copy), sizeof(T));
    }

  const OStream &Write(OStream &os) const
    {
    return WriteT<uint32_t>(os);
    }

  const OStream &Write16(OStream &os) const
    {
    assert( ValueLength <= 0xffff );
    return WriteT<uint16_t>(os);
    }

private:
  uint32_t ValueLength;
};
//----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const VL& val)
{
  os << std::hex << val.ValueLength;
  return os;
}

} // end namespace gdcm

#endif //__gdcmVL_h
