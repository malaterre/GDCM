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

#ifndef __gdcmIStream_h
#define __gdcmIStream_h

#include "gdcmIOS.h"

//#include <fstream>

namespace gdcm
{

/**
 * \brief Wrapper around ifstream
 * specialized for binary stream. Is able to read DICOM attribute
 * \note bla
 */

class GDCM_EXPORT IStream : virtual public IOS
{

public:
  IStream();
  ~IStream();

  virtual IStream& Seekg (std::streamoff off, std::ios_base::seekdir dir);
  virtual std::streampos Tellg ( );
  //virtual bool operator ! ( ) const;

  virtual IStream& Read(char *str, std::streamsize n);
  virtual std::streamsize Gcount ( ) const;
  virtual IStream& Get (char& c );
  virtual bool Eof();

  IStream &Read(uint16_t &vl);

  virtual IStream& operator>> (int& val );
  virtual IStream& operator>> (unsigned short& val );

private:
  IStream(IStream const &);
  IStream &operator= (IStream const &);
};

}

#endif //__gdcmIStream_h

