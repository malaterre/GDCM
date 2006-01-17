#include "gdcmImplicitDataElement.h"
#include "gdcmDict.h"

namespace gdcm
{
//-----------------------------------------------------------------------------
DICOMOStream& operator<<(DICOMOStream &_os, const ImplicitDataElement &_val)
{
  return _val.Write(_os);
}

DICOMOStream& ImplicitDataElement::Write(DICOMOStream& _os) const
{
  //const DataElement &de = 
  //_os << de;
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  assert(0 && "Not Implemented");
  return _os;
}

//-----------------------------------------------------------------------------
//DICOMIStream& operator>>(DICOMIStream &_os, ImplicitDataElement &_val)
//{
//  return _val.Read(_os);
//}


} // end namespace gdcm
