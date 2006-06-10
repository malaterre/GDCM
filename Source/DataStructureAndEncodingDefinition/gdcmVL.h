#ifndef __gdcmVL_h
#define __gdcmVL_h

#include "gdcmTypes.h"
#include "gdcmSwapCode.h"

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

  VL& operator++() {
    ++ValueLength;
    return *this;
  }
  VL operator++(int) {
    uint32_t tmp(ValueLength);
    ++ValueLength;
    return tmp;
  }

  operator uint32_t() const { return ValueLength; }

  friend std::ostream& operator<<(std::ostream& os, const VL& vl);
  //TODO
  //friend std::istream& operator>>(std::istream& is, VL& n);

  IStream &Read(IStream &is)
    {
    char *p = (char*)(&ValueLength);
    is.SetWidth(4);
    return is >> p;
    }
  const OStream &Write(OStream &os) const
    {
    //return os.Write((char*)(&ValueLength), 4);
    return os;
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
