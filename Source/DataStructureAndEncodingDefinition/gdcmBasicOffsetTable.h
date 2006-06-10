
#ifndef __gdcmBasicOffsetTable_h
#define __gdcmBasicOffsetTable_h

#include "gdcmDataElement.h"
#include "gdcmDataSet.h"
#include "gdcmSwapCode.h"

namespace gdcm
{
/**
 * \brief Class to represent an BasicOffsetTable
 */

class GDCM_EXPORT BasicOffsetTable : public DataElement
{
public:
  BasicOffsetTable(const Tag& t = Tag(0), uint32_t const &vl = 0) : DataElement(t, vl) {}
  friend std::ostream& operator<<(std::ostream &os, const BasicOffsetTable&val);

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
  ByteValue Offsets;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const BasicOffsetTable &val)
{
  os << " BasicOffsetTable Length=" << val.ValueLengthField << std::endl;
  os << val.Offsets;

  return os;
}


} // end namespace gdcm

#endif //__gdcmBasicOffsetTable_h
