
#ifndef __gdcmFragment_h
#define __gdcmFragment_h

#include "gdcmDataElement.h"
#include "gdcmByteValue.h"

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

  Fragment(const Fragment &val):DataElement(val)
    {
    FragmentValue = val.FragmentValue;
    }
  Fragment &operator=(Fragment const & val)
    {
    FragmentValue = val.FragmentValue;
    return *this;
    }

  IStream &Read(IStream &is)
    {
    // Superclass 
    if( !TagField.Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    if( !ValueLengthField.Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    // Self
    FragmentValue.SetLength(ValueLengthField);
    if( !FragmentValue.Read(is) )
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

private:
  ByteValue FragmentValue;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const Fragment &val)
{
  os << "Tag: " << val.TagField;
  os << "\tVL: " << val.ValueLengthField;
  os << "\t" << val.FragmentValue;

  return os;
}


} // end namespace gdcm

#endif //__gdcmFragment_h
