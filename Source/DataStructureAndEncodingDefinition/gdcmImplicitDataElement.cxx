#include "gdcmImplicitDataElement.h"

namespace gdcm
{

//-----------------------------------------------------------------------------
void ImplicitDataElement::Read(std::istream &_is)
{
  (void)_is;
}

//-----------------------------------------------------------------------------
void ImplicitDataElement::Write(std::ostream& _os) const
{
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  assert(0 && "Not Implemented");
  (void)_os;
}

} // end namespace gdcm
