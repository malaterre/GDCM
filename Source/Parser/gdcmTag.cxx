#include "gdcmTag.h"
#include "gdcmDICOMIStream.h"
#include "gdcmDICOMOStream.h"


namespace gdcm
{
/// \brief Writes the Tag into the stream
DICOMOStream& operator<<(DICOMOStream &_os, Tag &_val)
{
  _os.Write(_val);
  return _os;
}

/// \brief Reads the Tag from the stream
DICOMIStream& operator>>(DICOMIStream &_os, Tag &_val)
{
  _os.Read(_val);
  return _os;
}

} // end namespace gdcm
