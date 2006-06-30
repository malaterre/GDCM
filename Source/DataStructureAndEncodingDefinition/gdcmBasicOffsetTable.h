
#ifndef __gdcmBasicOffsetTable_h
#define __gdcmBasicOffsetTable_h

#include "gdcmDataElement.h"
#include "gdcmDataSet.h"
#include "gdcmSwapCode.h"

namespace gdcm
{
/**
 * \brief Class to represent an BasicOffsetTable
 * TODO: this is A fragment need to subclass from fragment
 */

class GDCM_EXPORT BasicOffsetTable : public DataElement
{
public:
  BasicOffsetTable(const Tag &t = Tag(0), uint32_t const &vl = 0) : DataElement(t, vl) {}
  friend std::ostream &operator<<(std::ostream &os, const BasicOffsetTable &val);

  void Clear() {
    }

  IStream &Read(IStream &is) {
    // Superclass 
    const Tag itemStart(0xfffe, 0xe000);
    const Tag seqDelItem(0xfffe,0xe0dd);
    if( !TagField.Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    assert( TagField == itemStart );
    if( !ValueLengthField.Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    // Self
    Offsets.SetLength(ValueLengthField);
    if( !Offsets.Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    return is;
    }

  OStream &Write(OStream &os) const {
    abort();
    return os;
    }

  Value const &GetValue() const {
    return Offsets;
  }

private:
  ByteValue Offsets;
};
//-----------------------------------------------------------------------------
inline std::ostream &operator<<(std::ostream &os, const BasicOffsetTable &val)
{
  os << " BasicOffsetTable Length=" << val.ValueLengthField << std::endl;
  os << val.Offsets;

  return os;
}


} // end namespace gdcm

#endif //__gdcmBasicOffsetTable_h
