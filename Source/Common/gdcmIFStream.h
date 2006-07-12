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

#ifndef __gdcmIFStream_h
#define __gdcmIFStream_h

#include "gdcmIStream.h"

#include <string>
#include <fstream>

namespace gdcm
{

/**
 * \brief Wrapper around ifstream
 * specialized for binary stream. Is able to read DICOM attribute
 * \note bla
 */

class GDCM_EXPORT IFStream : public IStream
{
public:
  IFStream();
  explicit IFStream(const char *filename);
  ~IFStream();

  operator void * ( ) const { return InternalIStream; }
  bool operator ! ( ) const { return !InternalIStream; }

  void Open(const char* filename);
  bool IsOpen() { return InternalIStream.is_open(); }
  void Close();

  IStream& Seekg (std::streamoff off, std::ios_base::seekdir dir);
  std::streampos Tellg ( );
  IStream& Read(char *str, std::streamsize n);
  bool Eof() { return InternalIStream.eof(); }

private:
  std::string FileName;
  std::ifstream InternalIStream;

  IFStream(IFStream const &);
  IFStream &operator= (IFStream const &);
};

}

#endif //__gdcmIFStream_h

