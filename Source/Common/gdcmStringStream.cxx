#include "gdcmStringStream.h"

namespace gdcm
{
StringStream::StringStream()
{
}

IStream& StringStream::Read(char* str, std::streamsize n)
{
#ifndef NDEBUG
  memset(str, 0, n); // DEBUG only
  bool eof = InternalSStream.eof();
  bool good = InternalSStream.good();
#endif
  InternalSStream.read(str,n);
#ifndef NDEBUG
  bool eof2 = InternalSStream.eof();
  bool good2 = InternalSStream.good();
  const std::streamsize count = InternalSStream.gcount();
  if( count != n )
    {
    assert( good && !good2 );
    assert( !eof && eof2 );
    assert( count == 0 );
    }
#endif
  return *this;
}

StringStream::StringStream(const std::string &str)
{
  InternalSStream.str(str);
}

IStream& StringStream::Seekg (std::streamoff off, std::ios_base::seekdir dir)
{
  InternalSStream.seekg(off, dir);
  return *this;
}
std::streampos StringStream::Tellg ( )
{
  return InternalSStream.tellg();
}

} // end namespace gdcm
