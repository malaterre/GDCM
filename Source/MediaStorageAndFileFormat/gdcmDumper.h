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
#ifndef __gdcmDumper_h
#define __gdcmDumper_h

#include "gdcmFile.h"

// Use it to simply dump value read from the file. No interpretation is done.
// But it is real fast ! Almost no overhead
namespace gdcm
{

// It's a sink there is no output
class GDCM_EXPORT Dumper
{
public:
  Dumper();
  ~Dumper();

  void SetFile(File const &f) { F = &f; }

  void Print(std::ostream& os);

protected:
  const File *F;
};

} // end namespace gdcm

#endif //__gdcmDumper_h
