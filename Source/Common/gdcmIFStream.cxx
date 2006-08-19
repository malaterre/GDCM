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
#include "gdcmIFStream.h"
#include "gdcmByteSwap.txx"

#include <fstream>
#include <assert.h>

namespace gdcm
{

IFStream::IFStream()
{
}

IFStream::IFStream(const char *filename)
{
  Open(filename);
}

IFStream::~IFStream()
{
  assert( !InternalIStream.is_open());
}

void IFStream::Open(const char *filename)
{
  FileName = filename;
  assert( !FileName.empty() );
  InternalIStream.open(FileName.c_str(),
    std::ios::in | std::ios::binary);
}

void IFStream::Close()
{
  InternalIStream.close();
}

IStream& IFStream::Seekg (std::streamoff off, std::ios::seekdir dir)
{
  InternalIStream.seekg(off, dir);
  return *this;
}

std::streampos IFStream::Tellg ( )
{
  return InternalIStream.tellg();
}

IStream& IFStream::Read(char *str, std::streamsize n)
{
#ifndef NDEBUG
  memset(str, 0, n); // DEBUG only
  bool eof = InternalIStream.eof();
  bool good = InternalIStream.good();
#endif
  InternalIStream.read(str, n);
#ifndef NDEBUG
  bool eof2 = InternalIStream.eof();
  bool good2 = InternalIStream.good();
  const std::streamsize count = InternalIStream.gcount();
  if( count != n )
    {
    assert( good && !good2 );
    assert( !eof && eof2 );
    assert( count == 0 );
    }
#endif
    
  return *this;
}

std::streamsize IFStream::Gcount ( ) const
{
#if defined(__GNUC__) && (__GNUC__ == 2) && (__GNUC_MINOR__ == 95)
  std::ifstream &f = const_cast<std::ifstream&>(InternalIStream);
  return f.gcount();
#else
  return InternalIStream.gcount();
#endif
}

} // end namespace gdcm

