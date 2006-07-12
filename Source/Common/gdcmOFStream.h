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

#ifndef __gdcmOFStream_h
#define __gdcmOFStream_h

#include "gdcmOStream.h"

#include <string>
#include <fstream>

namespace gdcm
{

/**
 * \brief Wrapper around ofstream
 * specialized for binary stream. Is able to read DICOM attribute
 * \note bla
 */

class GDCM_EXPORT OFStream : public OStream
{
public:
  OFStream();
  explicit OFStream(const char *filename);
  ~OFStream();

  void Open(const char *filename);
  void Close();

private:
  std::string FileName;
  std::ofstream InternalOStream;

  OFStream(OFStream const &);
  OFStream &operator= (OFStream const &);
};

}

#endif //__gdcmOFStream_h

