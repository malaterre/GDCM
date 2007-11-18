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
#ifndef __gdcmCoder_h
#define __gdcmCoder_h

#include "gdcmTypes.h"

namespace gdcm
{

class TransferSyntax;
class Coder
{
public:
  virtual ~Coder() {}
  virtual bool CanCode(TransferSyntax const &) { return false; }
  virtual bool Code(std::istream &is, std::ostream &os) { return false; }
};

} // end namespace gdcm

#endif //__gdcmCoder_h
