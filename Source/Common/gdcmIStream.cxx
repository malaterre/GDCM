/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmIStream.h"
#include "gdcmByteSwap.txx"

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


IStream &IStream::Seekg (std::streamoff off, std::ios::seekdir dir)
{
  abort();
//  Rdbuf()->pubseekoff(off, dir, std::ios_base::in);
  return *this;
}

std::streampos IStream::Tellg ( )
{
  abort();
  return 0; //Rdbuf()->pubseekoff(0, std::ios_base::cur, std::ios_base::in);
}

IStream& IStream::Read(char *str, std::streamsize n)
{
  abort();
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

std::streamsize IStream::Gcount ( ) const
{
  abort();
  return 0;
}

IStream &IStream::Read(uint16_t &vl)
{
  union { uint16_t vl; char vl_str[2]; } uvl;
  Read(uvl.vl_str,2);
  ByteSwap<uint16_t>::SwapFromSwapCodeIntoSystem(uvl.vl,
    GetSwapCode());
  assert( uvl.vl != static_cast<uint16_t>(-1) );
  vl = uvl.vl;
  return *this;
}

IStream& IStream::Get (char& c )
{
  abort();
//  c = Rdbuf()->sbumpc();
  return *this;
}

bool IStream::Eof()
{
  abort();
  return false;
}

IStream& IStream::operator>> (int& val )
{
  abort();
  return *this;
}

IStream& IStream::operator>> (unsigned short& val )
{
  abort();
  return *this;
}

//bool IStream::operator ! ( ) const
//{
//  abort();
//  return false;
//}

} // end namespace gdcm

