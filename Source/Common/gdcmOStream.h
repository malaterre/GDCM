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

//  OStream &operator<< (char &c);
//  OStream &operator<< (signed char &c);
//  OStream &operator<< (unsigned char &c);
//
//  OStream &operator<< (float &f);
//  OStream &operator<< (double &d);
//
//  OStream &operator<< (short &s);
//  OStream &operator<< (unsigned short &s);
//  OStream &operator<< (int &i);
//  OStream &operator<< (unsigned int &i);
//  OStream &operator<< (long &l);
//  OStream &operator<< (unsigned long &l);
//
//  OStream &operator<< (const char *str);

  virtual OStream& Write(const char *str, std::streamsize n);

private:
  OStream(OStream const &);
  OStream &operator= (OStream const &);
};

}

#endif //__gdcmIStream_h

