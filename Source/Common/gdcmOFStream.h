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

#ifndef __gdcmOFStream_h
#define __gdcmOFStream_h

//#include "gdcmOStream.h"

#include <string>
#include <fstream>

#define OFStream std::ofstream

namespace gdcm_old
{

/**
 * \brief Wrapper around ofstream
 * specialized for binary stream. Is able to read DICOM attribute
 * \note bla
 */

#if 0
class GDCM_EXPORT OFStream : public OStream
{
public:
  OFStream();
  explicit OFStream(const char *filename);
  ~OFStream();

  operator void * ( ) const { return InternalOStream; }
  bool operator ! ( ) const { return !InternalOStream; }

  void Open(const char *filename);
  bool IsOpen() { return InternalOStream.is_open(); }
  void Close();

  OStream& Seekp (std::streamoff off, std::ios::seekdir dir);
  std::streampos Tellp ( );
  OStream& Write(const char *str, std::streamsize n);
  bool Eof() { return InternalOStream.eof(); }

private:
  std::string FileName;
  std::ofstream InternalOStream;

  OFStream(OFStream const &);
  OFStream &operator= (OFStream const &);
};

#endif
}

#endif //__gdcmOFStream_h

