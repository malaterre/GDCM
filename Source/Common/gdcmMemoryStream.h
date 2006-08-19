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

#ifndef __gdcmMemoryStream_h
#define __gdcmMemoryStream_h

#include "gdcmIOStream.h"
#include <sstream>

namespace gdcm
{

/**
 * \brief Wrapper around ifstream
 * specialized for binary stream. Is able to read DICOM attribute
 * \note bla
 */

class GDCM_EXPORT MemoryStream : public IOStream
{
public:
  explicit MemoryStream ():Pointer(0),Length(0),GPos(0) {}
  ~MemoryStream() {}

  operator void * ( ) const { return (void*)Pointer; }

  IStream& Read(char* s, std::streamsize n);
  std::streamsize Gcount ( ) const;
//  OStream& WriteBuffer(const char* s, std::streamsize n);

  IStream& Get(char &c) {
    assert( GPos < Length );
    c = Pointer[GPos];
    return *this;
  }

  IStream& Seekg (std::streamoff off, std::ios::seekdir dir);
  std::streampos Tellg ( );

protected:
private:
  const char *Pointer;
  std::streamsize Length;
  std::streampos GPos;
};

}

#endif //__gdcmMemoryStream_h

