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

#ifndef __gdcmOStream_h
#define __gdcmOStream_h

#include "gdcmIOS.h"

namespace gdcm
{

/**
 * \brief Wrapper around ostream
 * \note bla
 */

class GDCM_EXPORT OStream : virtual public IOS
{
public:
  OStream();
  ~OStream();

  virtual OStream& Seekp (std::streamoff off, std::ios::seekdir dir);
  virtual std::streampos Tellp ( );
  //virtual bool operator ! ( ) const;

  virtual OStream& Write(const char *str, std::streamsize n);
  virtual bool Eof();

  OStream &Write(uint16_t const &vl);

private:
  OStream(OStream const &);
  OStream &operator= (OStream const &);
};

}

#endif //__gdcmIStream_h

