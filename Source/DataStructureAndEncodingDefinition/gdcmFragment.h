
#ifndef __gdcmFragment_h
#define __gdcmFragment_h

#include "gdcmDataElement.h"
#include "gdcmDataSet.h"
#include "gdcmSwapCode.h"

namespace gdcm
{
/**
 * \brief Class to represent an Fragment
 */

class GDCM_EXPORT Fragment : public DataElement
{
public:
  Fragment(const Tag& t = Tag(0), uint32_t const &vl = 0) : DataElement(t, vl) {}
  friend std::ostream& operator<<(std::ostream &os, const Fragment&val);

  void Clear() {
    }

  IStream &Read(IStream &is) {
    abort();
    return is;
    }

  OStream &Write(OStream &os) const {
    abort();
    return os;
    }

private:
  ByteValue FragmentValue;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const Fragment &val)
{
  os << val.FragmentValue;

  return os;
}


} // end namespace gdcm

#endif //__gdcmFragment_h
