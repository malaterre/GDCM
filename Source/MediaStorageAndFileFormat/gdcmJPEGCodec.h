/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmJPEGcodec_h
#define __gdcmJPEGcodec_h

#include "gdcmImageCodec.h"

namespace gdcm
{

/**
 * \brief Class to do JPEG
 * \note
 */
class PixelFormat;
class JPEGCodec : public ImageCodec
{
public:
  JPEGCodec();
  ~JPEGCodec();
  bool CanDecode(TransferSyntax const &ts);
  bool CanCode(TransferSyntax const &ts);
  bool Decode(DataElement const &is, DataElement &os);
  void SetPixelFormat(PixelFormat const &pf);

  // Compress into JPEG
  bool Code(DataElement const &is, DataElement &os);

protected:
  bool Decode(std::istream &is, std::ostream &os);
  bool Code(std::istream &is, std::ostream &os);

protected:
  // Internal method called by SetPixelFormat
  // Instantiate the right jpeg codec (8, 12 or 16)
  void SetBitSample(int bit);

protected:
  int BitSample;

private:
  JPEGCodec *Internal;
};

} // end namespace gdcm

#endif //__gdcmJPEGcodec_h
