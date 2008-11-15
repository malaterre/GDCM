/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmJPEGLScodec_h
#define __gdcmJPEGLScodec_h

#include "gdcmImageCodec.h"

namespace gdcm
{
  
class JPEGLSInternals;
/**
 * \brief JPEG-LS
 * \note codec that implement the JPEG-LS compression
 * this is an implement of ImageCodec for JPEG-LS
 */
class GDCM_EXPORT JPEGLSCodec : public ImageCodec
{
public:
  JPEGLSCodec();
  ~JPEGLSCodec();
  bool CanDecode(TransferSyntax const &ts) const;
  bool CanCode(TransferSyntax const &ts) const;

  unsigned long GetBufferLength() const { return BufferLength; }
  void SetBufferLength(unsigned long l) { BufferLength = l; }

  bool Decode(DataElement const &is, DataElement &os);
  bool Code(DataElement const &in, DataElement &out);

  bool GetHeaderInfo(std::istream &is, TransferSyntax &ts);

private:
  unsigned long BufferLength;
};

} // end namespace gdcm

#endif //__gdcmJPEGLScodec_h
