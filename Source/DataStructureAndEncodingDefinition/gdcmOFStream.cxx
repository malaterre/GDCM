#include "gdcmOFStream.h"
#include "gdcmByteSwap.txx"

#include <assert.h>

namespace gdcm
{

OFStream::OFStream():OStream((new std::filebuf()))
{
}

void OFStream::SetFileName(const char* filename)
{
  FileName = filename;
}

void OFStream::Open()
{
  assert( !FileName.empty() );
  std::filebuf *fb = static_cast<std::filebuf*>(Rdbuf());
  fb->open(FileName.c_str(), std::ios::in | std::ios::binary);
}

void OFStream::Close()
{
  std::filebuf *fb = static_cast<std::filebuf*>(Rdbuf());
  fb->close();
}

OFStream::OFStream(const char *filename):
  OStream((new std::filebuf())->open(
    filename, std::ios::out | std::ios::binary))
{
}

OFStream::~OFStream()
{
  std::filebuf *fb = static_cast<std::filebuf*>(Rdbuf());
  Rdbuf(0);
  delete fb;
}

} // end namespace gdcm

