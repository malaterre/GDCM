#include "gdcmOFStream.h"
#include "gdcmByteSwap.txx"

#include <fstream>
#include <assert.h>

namespace gdcm
{

OFStream::OFStream()
{
}

OFStream::OFStream(const char *filename)
{
  Open(filename);
}

OFStream::~OFStream()
{
  assert( !InternalOStream.is_open());
}

void OFStream::Open(const char *filename)
{
  FileName = filename;
  assert( !FileName.empty() );
  InternalOStream.open(FileName.c_str(),
    std::ios::out | std::ios::binary);
}

void OFStream::Close()
{
  InternalOStream.close();
}

} // end namespace gdcm

