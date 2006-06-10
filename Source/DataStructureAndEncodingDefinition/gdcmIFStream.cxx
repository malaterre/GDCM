#include "gdcmIFStream.h"
#include "gdcmByteSwap.txx"

#include <fstream> // filebuf ??
#include <assert.h>

namespace gdcm
{

// virtual inheritence is a pain, one need to make sure IOS has a 
// default cstor
IFStream::IFStream():IStream((new std::filebuf()))
{
  Init(Rdbuf());
}

IFStream::IFStream(const char *filename):
  IStream((new std::filebuf())->open(
      filename, std::ios::in | std::ios::binary))
{
  FileName = filename;
  Init(Rdbuf());
}

IFStream::~IFStream()
{
  std::filebuf *fb = static_cast<std::filebuf*>(Rdbuf());
  Rdbuf(0);
  delete fb;
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

} // end namespace gdcm

