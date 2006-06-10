#include "gdcmIStream.h"

namespace gdcm
{

IStream::IStream(std::streambuf *sb):IOS(sb)
{
}

IStream::~IStream()
{
}

IStream &IStream::operator>> (char &c)
{
  return *this;
}

IStream &IStream::operator>> (signed char &c)
{
  return *this;
}
  
IStream &IStream::operator>> (unsigned char &c)
{
  return *this;
}
  
IStream &IStream::operator>> (float &f)
{
  return *this;
}
  
IStream &IStream::operator>> (double &d)
{
  return *this;
}
  
IStream &IStream::operator>> (short &s)
{
  return *this;
}
  
IStream &IStream::operator>> (unsigned short &s)
{
  return *this;
}
  
IStream &IStream::operator>> (int &i)
{
  return *this;
}
  
IStream &IStream::operator>> (unsigned int &i)
{
  return *this;
}
  
IStream &IStream::operator>> (long &l)
{
  return *this;
}
  
IStream &IStream::operator>> (unsigned long &l)
{
  return *this;
}

IStream& IStream::operator>> (char *str)
{
  assert(GetWidth() != 0);

  size_t len = GetWidth();

  return *this;
}


IStream &IStream::Seekg (std::streamoff off, std::ios_base::seekdir dir)
{
  abort();
  return *this;
}

std::streampos IStream::Tellg ( )
{
  return 0;
}

// DEPRECATED:
IStream& IStream::Read(char *str, std::streamsize n)
{
  abort();
  return *this;
}

IStream& IStream::Get (char& c )
{
  abort();
}

} // end namespace gdcm
