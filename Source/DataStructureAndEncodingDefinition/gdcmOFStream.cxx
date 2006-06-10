#include "gdcmOFStream.h"
#include "gdcmByteSwap.txx"

#include <assert.h>

namespace gdcm
{

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

