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
#ifndef __gdcmImageChangeTransferSyntax_h
#define __gdcmImageChangeTransferSyntax_h

#include "gdcmImageToImageFilter.h"
#include "gdcmTransferSyntax.h"

namespace gdcm
{


class GDCM_EXPORT ImageChangeTransferSyntax : public ImageToImageFilter
{
public:
  ImageChangeTransferSyntax() {}
  ~ImageChangeTransferSyntax() {}

  void SetTransferSyntax(const TransferSyntax &ts) { TS = ts; }
  const TransferSyntax &GetTransferSyntax() const { return TS; }

  bool Change();

private:
  TransferSyntax TS;
};

} // end namespace gdcm

#endif //__gdcmImageChangeTransferSyntax_h

