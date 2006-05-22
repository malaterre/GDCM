
#ifndef __gdcmImplicitDataElement_h
#define __gdcmImplicitDataElement_h

#include "gdcmDataElement.h"

namespace gdcm
{
/**
 * \brief Class to represent an *Implicit VR* Data Element
 * \note bla
 */
class GDCM_EXPORT ImplicitDataElement : public DataElement
{
public:
  ImplicitDataElement() : DataElement() {}

  friend std::ostream& operator<<(std::ostream& _os, const ImplicitDataElement &_val);

  void Read(std::istream& _os);
  void Write(std::ostream& _os) const;

private:
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
