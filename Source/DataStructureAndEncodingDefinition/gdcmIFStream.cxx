#include "gdcmIFStream.h"
#include "gdcmByteSwap.txx"

#include <assert.h>

namespace gdcm
{

IFStream::IFStream():IStream(NULL)
{
}

void IFStream::SetFileName(const char* filename)
{
  FileName = filename;
}

void IFStream::Open()
{
}

void IFStream::Close()
{
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

