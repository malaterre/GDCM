#include "gdcmTag.h"
#include "gdcmDICOMIStream.h"
#include "gdcmDICOMOStream.h"


namespace gdcm
{
DICOMOStream& operator<<(DICOMOStream& _os, Tag &_val)
{
  _os.Write(_val);
  return _os;
}

DICOMIStream& operator>>(DICOMIStream& _os, Tag &_val)
{
  _os.Read(_val);
  return _os;
}

} // end namespace gdcm
