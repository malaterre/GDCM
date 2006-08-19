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
#include "gdcmOStream.h"
#include "gdcmByteSwap.txx"

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

OStream& OStream::Seekp (std::streamoff off, std::ios::seekdir dir)
{
  abort();
  return *this;
}

std::streampos OStream::Tellp ( )
{
  abort();
  return 0;
}
  //virtual bool operator ! ( ) const;
bool OStream::Eof()
{
  abort();
  return true;
}

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

OStream &OStream::Write(uint16_t const &vl)
{
  union { uint16_t vl; char vl_str[2]; } uvl;
  uvl.vl = vl;
  ByteSwap<uint16_t>::SwapFromSwapCodeIntoSystem(uvl.vl,
    GetSwapCode());
  // MR-SIEMENS-DICOM-WithOverlays-extracted-overlays.dcm
  //assert( uvl.vl != static_cast<uint16_t>(-1) ); // FIXME
  Write(uvl.vl_str,2);

  return *this;
}

} // end namespace gdcm
