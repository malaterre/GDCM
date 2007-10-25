/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
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

IStream& StringStream::Seekg (std::streamoff off, std::ios::seekdir dir)
{
  InternalSStream.seekg(off, dir);
  return *this;
}
std::streampos StringStream::Tellg ( )
{
  return InternalSStream.tellg();
}

std::streamsize StringStream::Gcount ( ) const
{
#if defined(__GNUC__) && (__GNUC__ == 2) && (__GNUC_MINOR__ == 95)
  std::stringstream &f = const_cast<std::stringstream&>(InternalSStream);
  return f.gcount();
#else
  return InternalSStream.gcount();
#endif
}

bool StringStream::Eof()
{
  return InternalSStream.eof();
}

} // end namespace gdcm
