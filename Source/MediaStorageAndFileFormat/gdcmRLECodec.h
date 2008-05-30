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
#ifndef __gdcmRLEcodec_h
#define __gdcmRLEcodec_h

#include "gdcmImageCodec.h"

namespace gdcm
{

class RLEInternals;
class RLECodec : public ImageCodec
{
public:
  RLECodec();
  ~RLECodec();
  bool CanDecode(TransferSyntax const &ts);
  bool Decode(DataElement const &is, DataElement &os);
  unsigned long GetBufferLength() const { return BufferLength; }
  void SetBufferLength(unsigned long l) { BufferLength = l; }

protected:
  bool Decode(std::istream &is, std::ostream &os);
public:

  void SetLength(unsigned long l)
    {
    Length = l;
    }
private:
  RLEInternals *Internals;
  unsigned long Length;
  unsigned long BufferLength;
};

} // end namespace gdcm

#endif //__gdcmRLEcodec_h
