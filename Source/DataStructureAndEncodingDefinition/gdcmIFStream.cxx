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

IStream& IFStream::Seekg (std::streamoff off, std::ios_base::seekdir dir)
{
  InternalIStream.seekg(off, dir);
  return *this;
}

std::streampos IFStream::Tellg ( )
{
  return InternalIStream.tellg();
}

IStream& IFStream::Read(char *str, std::streamsize n)
{
  InternalIStream.read(str, n);
  return *this;
}

} // end namespace gdcm

