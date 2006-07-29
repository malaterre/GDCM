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
#include "gdcmRAWCodec.h"
#include "gdcmTS.h"
#include "gdcmOStream.h"
#include "gdcmIStream.h"
#include "gdcmByteSwap.txx"


namespace gdcm
{

class RAWInternals
{
public:
};

RAWCodec::RAWCodec()
{
  Internals = new RAWInternals;
}

RAWCodec::~RAWCodec()
{
  delete Internals;
}

bool RAWCodec::CanDecode(TS const &ts)
{
  return ts.GetCompressionType() == Compression::RAW;
}

bool RAWCodec::Decode(IStream &is, OStream &os)
{
  ImageCodec::Decode(is, os);
  return true;
}

} // end namespace gdcm
