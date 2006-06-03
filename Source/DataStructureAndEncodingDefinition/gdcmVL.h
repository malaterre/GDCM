#ifndef __gdcmVL_h
#define __gdcmVL_h

#include "gdcmTypes.h"
#include "gdcmSwapCode.h"

#include <iostream>

/* \brief Value Length
*/
namespace gdcm
{

class GDCM_EXPORT VL
{
public:
  VL(uint32_t vl = 0):ValueLength(vl) { }

  bool IsOdd() const {
    return ValueLength % 2;
  }
  bool IsUndefined() const {
    return ValueLength == 0xFFFFFFFF;
  }

  VL& operator++() {
    ValueLength++;
    return *this;
  }
  VL operator++(int) {
    uint32_t tmp(ValueLength);
    ValueLength++;
    return tmp;
  }

  operator uint32_t() const { return ValueLength; }

  friend std::ostream& operator<<(std::ostream& os, const VL& vl);
  //TODO
  //friend std::istream& operator>>(std::istream& is, VL& n);

  std::istream &Read(std::istream &is,
    SC::SwapCode const &sc = SC::LittleEndian)
    {
    (void)sc;
    return is.read((char*)(&ValueLength), 4);
    }
  const std::ostream &Write(std::ostream &os,
    SC::SwapCode const &sc = SC::LittleEndian) const
    {
    (void)sc;
    return os.write((char*)(&ValueLength), 4);
    }

private:
  uint32_t ValueLength;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const VL& val)
{
  os << val.ValueLength;
  return os;
}

} // end namespace gdcm

#endif //__gdcmVL_h
