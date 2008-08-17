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
#ifndef __gdcmPVRGcodec_h
#define __gdcmPVRGcodec_h

#include "gdcmImageCodec.h"

namespace gdcm
{
  
class PVRGInternals;
class PVRGCodec : public ImageCodec
{
public:
  PVRGCodec();
  ~PVRGCodec();
  bool CanDecode(TransferSyntax const &ts) const;
  bool CanCode(TransferSyntax const &ts) const;

  bool Decode(DataElement const &is, DataElement &os);
  bool Code(DataElement const &in, DataElement &out);

private:
};

} // end namespace gdcm

#endif //__gdcmPVRGcodec_h
