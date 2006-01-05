#include "gdcmDataElement.h"

//-----------------------------------------------------------------------------
inline std::ostream& DataElement::Print(std::ostream &_os)
{
  _os << _val.TagField << " VL=" << _val.ValueLengthField;
  return _os;
}
//-----------------------------------------------------------------------------
inline DICOMIStream& Read(DICOMIStream &_os)
{
  // Read Tag
  assert( !_os.eof() ); // FIXME
  if( !_os.Read(_val.TagField) ) return _os;
  return _os;
}

//-----------------------------------------------------------------------------
inline DICOMOStream& Write(DICOMOStream &_os)
{
  // Write Tag
  _os.Write(_val.TagField);
  return _os;
}

