
#ifndef __gdcmImplicitDataElement_h
#define __gdcmImplicitDataElement_h

#include "gdcmDataElement.h"

namespace gdcm
{
/**
 * \brief Class to represent an *Implicit VR* Data Element
 * \note bla
 */
class Value;
class GDCM_EXPORT ImplicitDataElement : public DataElement
{
public:
  ImplicitDataElement(const Tag& t = Tag(0), uint32_t const &vl = 0) : DataElement(t,vl),ValueField(0) { }

  friend std::ostream& operator<<(std::ostream& _os, const ImplicitDataElement &_val);

  std::istream &Read(std::istream& _os);
  const std::ostream &Write(std::ostream& _os) const;

private:
  Value* ValueField;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const ImplicitDataElement &_val)
{
  const DataElement &de = _val;
  _os << de;
  return _os;
}

} // end namespace gdcm

#endif //__gdcmImplicitDataElement_h
