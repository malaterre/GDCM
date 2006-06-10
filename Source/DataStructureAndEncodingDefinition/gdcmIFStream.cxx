#include "gdcmIFStream.h"
#include "gdcmByteSwap.txx"

#include <assert.h>

namespace gdcm
{

IFStream::IFStream():IStream((new std::filebuf()))
{
}

void IFStream::SetFileName(const char* filename)
{
  FileName = filename;
}

void IFStream::Open()
{
  assert( !FileName.empty() );
  std::filebuf *fb = static_cast<std::filebuf*>(Rdbuf());
  fb->open(FileName.c_str(), std::ios::in | std::ios::binary);
}

void IFStream::Close()
{
  std::filebuf *fb = static_cast<std::filebuf*>(Rdbuf());
  fb->close();
}

IFStream::IFStream(const char *filename):
  IStream((new std::filebuf())->open(
      filename, std::ios::in | std::ios::binary))
{
  FileName = filename;
}

IFStream::~IFStream()
{
  std::filebuf *fb = static_cast<std::filebuf*>(Rdbuf());
  Rdbuf(0);
  delete fb;
}

} // end namespace gdcm

