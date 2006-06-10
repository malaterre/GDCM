#include "gdcmIStream.h"

namespace gdcm
{

IStream::IStream()
{
}

IStream::~IStream()
{
}

#if 0
IStream &IStream::operator>> (char &c)
{
  c = Rdbuf()->sbumpc();
  return *this;
}

IStream &IStream::operator>> (signed char &c)
{
  c = Rdbuf()->sbumpc();
  return *this;
}
  
IStream &IStream::operator>> (unsigned char &c)
{
  c = Rdbuf()->sbumpc();
  return *this;
}
  
IStream &IStream::operator>> (float &f)
{
  Rdbuf()->sgetn(reinterpret_cast<char*>(&f), sizeof(float));
  return *this;
}
  
IStream &IStream::operator>> (double &d)
{
  Rdbuf()->sgetn(reinterpret_cast<char*>(&d), sizeof(double));
  return *this;
}
  
IStream &IStream::operator>> (short &s)
{
  Rdbuf()->sgetn(reinterpret_cast<char*>(&s), sizeof(short));
  return *this;
}
  
IStream &IStream::operator>> (unsigned short &us)
{
  Rdbuf()->sgetn(reinterpret_cast<char*>(&us), sizeof(unsigned short));
  return *this;
}
  
IStream &IStream::operator>> (int &i)
{
  Rdbuf()->sgetn(reinterpret_cast<char*>(&i), sizeof(int));
  return *this;
}
  
IStream &IStream::operator>> (unsigned int &ui)
{
  Rdbuf()->sgetn(reinterpret_cast<char*>(&ui), sizeof(unsigned int));
  return *this;
}
  
IStream &IStream::operator>> (long &l)
{
  Rdbuf()->sgetn(reinterpret_cast<char*>(&l), sizeof(long));
  return *this;
}
  
IStream &IStream::operator>> (unsigned long &ul)
{
  Rdbuf()->sgetn(reinterpret_cast<char*>(&ul), sizeof(unsigned long));
  return *this;
}

IStream& IStream::operator>> (char *str)
{
  assert(GetWidth() != 0);

  std::streamsize wide = GetWidth();
  Rdbuf()->sgetn(str, wide);

  return *this;
}
#endif


IStream &IStream::Seekg (std::streamoff off, std::ios_base::seekdir dir)
{
//  Rdbuf()->pubseekoff(off, dir, std::ios_base::in);
  return *this;
}

std::streampos IStream::Tellg ( )
{
  return 0; //Rdbuf()->pubseekoff(0, std::ios_base::cur, std::ios_base::in);
}

IStream& IStream::Read(char *str, std::streamsize n)
{
//  try
//    {
//  Rdbuf()->sgetn(str, n);
//    }
//  catch(...)
//    {
//    abort();
//    }
  return *this;
}

IStream& IStream::Get (char& c )
{
//  c = Rdbuf()->sbumpc();
  return *this;
}

} // end namespace gdcm
