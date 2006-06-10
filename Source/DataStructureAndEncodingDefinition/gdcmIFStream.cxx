#include "gdcmIFStream.h"
#include "gdcmByteSwap.txx"

#include <fstream>
#include <assert.h>

namespace gdcm
{

IFStream::IFStream()
{
  Rdbuf(InternalIStream.rdbuf());
}

IFStream::IFStream(const char *filename)
{
  Rdbuf(InternalIStream.rdbuf());
  Open(filename);
}

IFStream::~IFStream()
{
  assert( !InternalIStream.is_open());
}

void IFStream::Open(const char *filename)
{
  FileName = filename;
  assert( !FileName.empty() );
  InternalIStream.open(FileName.c_str(),
    std::ios::in | std::ios::binary);
}

void IFStream::Close()
{
  InternalIStream.close();
}

} // end namespace gdcm

