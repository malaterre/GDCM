/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmOverlay_h
#define __gdcmOverlay_h

#include "gdcmTypes.h"
#include "gdcmObject.h"

namespace gdcm
{
  
class OverlayInternal;
class ByteValue;
class Overlay : public Object
{
public:
  Overlay();
  ~Overlay();
  void Print(std::ostream &) const {}

  void Decode(std::istream &is, std::ostream &os);

  Overlay(Overlay const &lut):Object(lut)
    {
    abort();
    }

private:
  OverlayInternal *Internal;
};

} // end namespace gdcm

#endif //__gdcmOverlay_h
