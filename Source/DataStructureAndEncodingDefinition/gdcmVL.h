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
#ifndef __gdcmVL_h
#define __gdcmVL_h

#include "gdcmTypes.h"
//#include "gdcmSwapCode.h"
//#include "gdcmByteSwap.txx"

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

  bool IsUndefined() const {
    return ValueLength == 0xFFFFFFFF;
  }

  bool IsOdd() const {
    return !IsUndefined() && ValueLength % 2;
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
	  //abort(); // VL cannot know it's length...well in implicit yes...
    return 4;
  }

  friend std::ostream& operator<<(std::ostream& os, const VL& vl);
  //TODO
  //friend std::istream& operator>>(std::istream& is, VL& n);

  template <typename TSwap>
  IStream &Read(IStream &is)
    {
    is.read((char*)(&ValueLength), sizeof(uint32_t));
    TSwap::SwapArray(&ValueLength,1);
    return is;
    }

  template <typename TSwap>
  IStream &Read16(IStream &is)
    {
    uint16_t copy;
    is.read((char*)(&copy), sizeof(uint16_t));
    TSwap::SwapArray(&copy,1);
    ValueLength = copy;
    assert( ValueLength <=  65535 /*UINT16_MAX*/ ); // ?? doh !
    return is;
    }

  template <typename TSwap>
  const OStream &Write(OStream &os) const
    {
    uint32_t copy = ValueLength;
#ifndef GDCM_WRITE_ODD_LENGTH
    if( IsOdd() )
      {
      ++copy;
      }
#endif
    TSwap::SwapArray(&copy,1);
    return os.write((char*)(&copy), sizeof(uint32_t));
    }

  template <typename TSwap>
  const OStream &Write16(OStream &os) const
    {
    assert( ValueLength <=   65535 /*UINT16_MAX*/ );
    uint16_t copy = ValueLength;
#ifndef GDCM_WRITE_ODD_LENGTH
    if( IsOdd() )
      {
      ++copy;
      }
#endif
    TSwap::SwapArray(&copy,1);
    return os.write((char*)(&copy), sizeof(uint16_t));
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
