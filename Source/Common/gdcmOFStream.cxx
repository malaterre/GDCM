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
#include "gdcmOFStream.h"
#include "gdcmByteSwap.txx"

#include <fstream>
#include <assert.h>

namespace gdcm
{

OFStream::OFStream()
{
}

OFStream::OFStream(const char *filename)
{
  Open(filename);
}

OFStream::~OFStream()
{
  assert( !InternalOStream.is_open());
}

void OFStream::Open(const char *filename)
{
  FileName = filename;
  assert( !FileName.empty() );
  InternalOStream.open(FileName.c_str(),
    std::ios::out | std::ios::binary);
}

void OFStream::Close()
{
  InternalOStream.close();
}

} // end namespace gdcm

