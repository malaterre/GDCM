#include "gdcmTag.h"


DICOMOStream& operator<<(DICOMOStream& _os, Tag &_val)
{
  _os.Read(_val);
}

DICOMIStream& operator>>(DICOMIStream& _os, Tag &_val)
{
  _os.Write(_val);
}

