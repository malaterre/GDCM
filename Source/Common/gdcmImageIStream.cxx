#include "gdcmImageIStream.h"
#include "gdcmIStream.h"

namespace gdcm
{
ImageIStream::ImageIStream():Stream(0)
{
}

ImageIStream::~ImageIStream()
{
}

bool ImageIStream::GetBuffer(char *buffer) const
{
  unsigned long len = GetBufferLength();
  if( Stream->Read(buffer, len) )
    {
    return true;
    }

  // Clearly mark buffer as invalid:
  buffer = 0;
  return false;
}

} // end namespace gdcm
