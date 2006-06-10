#include "gdcmOStream.h"

namespace gdcm
{

OStream::OStream()
{
}

OStream::~OStream()
{
}

#if 0
OStream &OStream::operator<< (char &c)
{
  return *this;
}

OStream &OStream::operator<< (unsigned char &c)
{
  return *this; 
}

OStream &OStream::operator<< (signed char &c)
{
  return *this;
}

OStream &OStream::operator<< (double &d)
{
  return *this;
}

OStream &OStream::operator<< (float &f)
{
  return *this;
}

OStream &OStream::operator<< (int &i)
{
  return *this;
}

OStream &OStream::operator<< (long &l)
{
  return *this;
}

OStream &OStream::operator<< (short &s)
{
  return *this;
}

OStream &OStream::operator<< (unsigned int &i)
{
  return *this; 
}

OStream &OStream::operator<< (unsigned long &l)
{ 
  return *this; 
}

OStream &OStream::operator<< (unsigned short &s)
{ 
  return *this; 
}

OStream &OStream::operator<< (const char *str)
{
  // TODO: width or strlen...
  size_t len = strlen(str) + 1;

  return *this;
}
#endif

OStream& OStream::Write(const char *str, std::streamsize n)
{
//  try
//    {
//  Rdbuf()->sputn(str, n);
//    }
//  catch(...)
//    {
//    abort();
//    }
  return *this;
}

} // end namespace gdcm
