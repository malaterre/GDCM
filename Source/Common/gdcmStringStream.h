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

#ifndef __gdcmStringStream_h
#define __gdcmStringStream_h

//#include "gdcmIOStream.h"
#include <sstream>

#define StringStream std::stringstream

namespace gdcm_old
{

/**
 * \brief Wrapper around ifstream
 * specialized for binary stream. Is able to read DICOM attribute
 * \note bla
 */

#if 0
class GDCM_EXPORT StringStream : public IOStream
{
public:
  explicit StringStream ();
  explicit StringStream (const std::string & str);
  ~StringStream() {}

  operator void * ( ) const { 
#ifdef _MSC_VER
    /* http://groups.google.com/group/microsoft.public.vc.stl/msg/81a009857c2facf5
     * Looks like a bug in how virtual base class is handled. It works with
     * istringstream and ostringstream, but not for stringstream. The
     * difference is stringstream is derived from ios twice, via istream and
     * ostream, as a virtual base class. It appears the compiler does not
     * realize that and fails because it doesn't know which copy of the base
     * class to call operator void*() on.
     * The bug appears to affect only implicitly invoked conversion operators.
     */
    return InternalSStream.operator void *();
#else
    return InternalSStream; 
#endif
  }

  IStream& Read(char* s, std::streamsize n);
  std::streamsize Gcount ( ) const;
  bool Eof();

  IStream& Get(char &c) {
    InternalSStream.get(c);
    return *this;
  }
  OStream& Write(const char* s, std::streamsize n) {
    InternalSStream.write(s, n);
    return *this;
  }

  //StringStream& operator<<(const char *a) {
  //  InternalSStream << a;
  //  return *this;
  //}
  std::string Str() const {
    assert( InternalSStream.good() );
    return InternalSStream.str();
  }
  void Str(std::string & s ) {
    // FIXME For some reason it is very important to reset the stringstream before
    // reusing it. See MR-MONO2-8-16x-heart.dcm for instance
    // I don't quite understand why it would be image dependant
    InternalSStream.clear();
    assert( InternalSStream.good() );
    InternalSStream.str(s);
    assert( InternalSStream.good() );
  }

  //operator std::stringstream () const { return InternalSStream; }
  
  IStream& operator>> (int& val ) {
    InternalSStream >> val;
    return *this;
  }
  IStream& operator>> (unsigned short& val ) {
    InternalSStream >> val;
    return *this;
  }

  IStream& Seekg (std::streamoff off, std::ios::seekdir dir);
  std::streampos Tellg ( );

protected:
  // The real internal class
  std::stringstream InternalSStream;
};

#endif
}

#endif //__gdcmStringStream_h

